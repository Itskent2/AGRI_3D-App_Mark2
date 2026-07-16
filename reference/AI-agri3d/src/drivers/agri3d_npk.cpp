/**
 * @file agri3d_npk.cpp
 * @brief NPK sensor polling, NVS history, and Flutter heatmap broadcast.
 *
 * Sensor wiring: RS485 half-duplex, DERE pin controls TX/RX direction.
 *   DERE HIGH → transmit (send Modbus query)
 *   DERE LOW  → receive  (read sensor response)
 */

#include "agri3d_npk.h"
#include "agri3d_config.h"
#include "agri3d_state.h"
#include "agri3d_network.h"
#include "agri3d_grbl.h"
#include "agri3d_logger.h"
#include "agri3d_protocol.h"
#include "agri3d_sd.h"
#include <SD_MMC.h>
#include <Preferences.h>
#include <time.h>

// ── Hardware ──────────────────────────────────────────────────────────────────
HardwareSerial NpkSerial(2);

// Standard Modbus RTU query for 7-in-1 soil sensor (function 03, reg 0x0000, count 7)
static const uint8_t NPK_QUERY[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x07, 0x04, 0x08 };
static const int     NPK_RESP_LEN = 19; // 01 03 0E (14 bytes data) CRC_L CRC_H

// ── Grid dimensions (match Flutter plot_model.dart) ───────────────────────────
// Edit these if Flutter's gridCols / gridRows change.
static const int HEATMAP_COLS = 5;
static const int HEATMAP_ROWS = 3;

// ── NVS ───────────────────────────────────────────────────────────────────────
struct __attribute__((packed)) NvsNpkEntry {
    int16_t  n;
    int16_t  p;
    int16_t  k;
    int16_t  moisture;
    int16_t  ec;
    int16_t  ph;
    int16_t  temp;
    uint32_t ts;
    float    x;
    float    y;
};
static Preferences _prefs;
static const char* NVS_NPK_NS = "npk_hist";

// ── Globals ───────────────────────────────────────────────────────────────────
SoilReading latestSoil;
static unsigned long _lastPollMs = 0;

// ============================================================================
// INTERNAL HELPERS
// ============================================================================



/** Map gantry mm position → heatmap grid cell index. */
static int mmToGridX(float mm) {
    if (!machineDim.valid || machineDim.maxX <= 0) return 0;
    float step = machineDim.maxX / max(HEATMAP_COLS - 1, 1);
    return (int)constrain(round(mm / step), 0, HEATMAP_COLS - 1);
}

static int mmToGridY(float mm) {
    if (!machineDim.valid || machineDim.maxY <= 0) return 0;
    float step = machineDim.maxY / max(HEATMAP_ROWS - 1, 1);
    return (int)constrain(round(mm / step), 0, HEATMAP_ROWS - 1);
}

static void getTodayStr(char* buf, size_t len) {
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    snprintf(buf, len, "%04d%02d%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
}

static void getNvsKey(char* buf, size_t len, int gx, int gy) {
    char date[12];
    getTodayStr(date, sizeof(date));
    snprintf(buf, len, "%s_G%02d_%02d", date, gx, gy);
}

/** Save one reading to NVS. Overwrites any existing entry for same cell+day. */
static void saveToNVS(const SoilReading& r) {
    char key[24];
    getNvsKey(key, sizeof(key), r.gridX, r.gridY);
    
    NvsNpkEntry entry;
    entry.n = (int16_t)(r.n * 10);
    entry.p = (int16_t)(r.p * 10);
    entry.k = (int16_t)(r.k * 10);
    entry.moisture = (int16_t)(r.moisture * 10);
    entry.ec = (int16_t)r.ec;
    entry.ph = (int16_t)(r.ph * 100);
    entry.temp = (int16_t)(r.tempC * 10);
    entry.ts = (uint32_t)r.timestamp;
    entry.x = r.x;
    entry.y = r.y;

    _prefs.begin(NVS_NPK_NS, false);
    _prefs.putBytes(key, &entry, sizeof(entry));
    _prefs.end();
}

// ============================================================================
// BROADCAST FUNCTIONS
// ============================================================================

/**
 * @brief Broadcast a live NPK reading as a single binary NPK_READING frame.
 *
 * Previously sent FOUR separate JSON frames per reading:
 *   {"evt":"NPK", ...}   ~180 bytes
 *   {"evt":"NPK_N", ...}  ~38 bytes
 *   {"evt":"NPK_P", ...}  ~38 bytes
 *   {"evt":"NPK_K", ...}  ~38 bytes
 *   Total: ~294 bytes across 4 WebSocket frames
 *
 * Now sends ONE binary frame of 36 bytes (8 header + 28 payload).
 * The Dart AgriFrame.decode() extracts all fields and updates both the
 * plot model and heatmap data in a single pass.
 *
 * Fixed-point encoding (all int16):
 *   N/P/K, moisture: × 10  (divide by 10.0 in Dart)
 *   pH:              × 100 (divide by 100.0 in Dart)
 *   temp:            × 10  signed (handles sub-zero temperatures)
 *   EC:              × 1   (raw µS/cm, no scale)
 */
static void broadcastNpkLive(const SoilReading& r) {
    if (sysState.getFlutter() == FLUTTER_DISCONNECTED) return;

    AgriPkt_NpkReading pkt;
    pkt.timestamp = (uint32_t)r.timestamp;
    pkt.x         = r.x;
    pkt.y         = r.y;
    pkt.n         = (int16_t)(r.n        * 10.0f);
    pkt.p         = (int16_t)(r.p        * 10.0f);
    pkt.k         = (int16_t)(r.k        * 10.0f);
    pkt.moisture  = (int16_t)(r.moisture * 10.0f);
    pkt.ec        = (int16_t)(r.ec);
    pkt.ph        = (int16_t)(r.ph       * 100.0f);
    pkt.temp      = (int16_t)(r.tempC    * 10.0f);
    pkt.gridX     = (uint8_t)r.gridX;
    pkt.gridY     = (uint8_t)r.gridY;

    uint8_t frameBuf[AGRI_HEADER_LEN + sizeof(AgriPkt_NpkReading)];
    uint16_t frameLen = agriPackNpkReading(pkt, frameBuf);
    webSocket.broadcastBIN(frameBuf, frameLen);

    AgriLog(TAG_SENSORS, LEVEL_INFO,
            "Grid(%d,%d) N=%.1f P=%.1f K=%.1f [binary %u bytes, was ~294 bytes x4 JSON]",
            r.gridX, r.gridY, r.n, r.p, r.k, frameLen);
}

// ============================================================================
// SENSOR READ
// ============================================================================

bool npkReadNow() {
    // ── Send Modbus query ──────────────────────────────────────────────────
    digitalWrite(NPK_DERE, HIGH);
    delayMicroseconds(100);
    NpkSerial.write(NPK_QUERY, sizeof(NPK_QUERY));
    NpkSerial.flush();
    digitalWrite(NPK_DERE, LOW);

    // ── Wait for response ──────────────────────────────────────────────────
    unsigned long t = millis();
    while (!NpkSerial.available()) {
        if (millis() - t > 2000) {
            AgriLog(TAG_SENSORS, LEVEL_WARN, "Timeout — no response from sensor");
            return false;
        }
        delay(10);
    }

    // Read all bytes with a timeout gap of 50ms
    uint8_t buf[128];
    int len = 0;
    unsigned long lastByteTime = millis();
    
    while (len < 128) {
        if (NpkSerial.available()) {
            buf[len++] = NpkSerial.read();
            lastByteTime = millis();
        } else {
            if (millis() - lastByteTime > 50) {
                break; // End of packet
            }
            delay(2);
        }
    }

    // FORGIVING PARSER: Look for Modbus function code 03 and length 0E (14)
    for (int i = 0; i < len - 16; i++) {
        if (buf[i] == 0x03 && buf[i+1] == 0x0E) {
            AgriLog(TAG_SENSORS, LEVEL_INFO, "Found valid Modbus pattern in response.");
            
            // Extract data
            float moisture = (float)((buf[i+2] << 8) | buf[i+3]) / 10.0f;
            int16_t tempRaw = (int16_t)((buf[i+4] << 8) | buf[i+5]);
            float tempC = (float)tempRaw / 10.0f;
            float ec = (float)((buf[i+6] << 8) | buf[i+7]);
            float ph = (float)((buf[i+8] << 8) | buf[i+9]) / 10.0f;
            float n = (float)((buf[i+10] << 8) | buf[i+11]);
            float p = (float)((buf[i+12] << 8) | buf[i+13]);
            float k = (float)((buf[i+14] << 8) | buf[i+15]);

            // ── Build reading with current gantry position ─────────────────────────
            SoilReading r;
            r.moisture  = moisture;
            r.tempC     = tempC;
            r.ec        = ec;
            r.ph        = ph;
            r.n         = n;
            r.p         = p;
            r.k         = k;
            r.x         = sysState.getX();
            r.y         = sysState.getY();
            r.gridX     = mmToGridX(sysState.getX());
            r.gridY     = mmToGridY(sysState.getY());
            r.timestamp = time(nullptr);
            r.valid     = true;

            latestSoil = r;

            saveToNVS(r);

            // ── Save to SD Card ───────────────────────────────────────────────────
#if HW_SD_CONNECTED
            File file = SD_MMC.open("/soil_data.csv", FILE_APPEND);
            if (file) {
                if (file.size() == 0) {
                    file.println("Timestamp,X,Y,GridX,GridY,Moisture,TempC,EC,pH,N,P,K");
                }
                file.printf("%ld,%.1f,%.1f,%d,%d,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",
                            (long)r.timestamp, r.x, r.y, r.gridX, r.gridY,
                            r.moisture, r.tempC, r.ec, r.ph, r.n, r.p, r.k);
                file.close();
                AgriLog(TAG_SENSORS, LEVEL_INFO, "Saved reading to SD card");
            } else {
                AgriLog(TAG_SENSORS, LEVEL_WARN, "Failed to open soil_data.csv on SD");
            }
#endif

            broadcastNpkLive(r);
            return true;
        }
    }

    AgriLog(TAG_SENSORS, LEVEL_ERR, "Could not find valid Modbus pattern in response");
    return false;
}


// ============================================================================
// HISTORY QUERIES
// ============================================================================

void npkSendHistory(uint8_t clientNum, int gridX, int gridY) {
    char key[24];
    getNvsKey(key, sizeof(key), gridX, gridY);

    _prefs.begin(NVS_NPK_NS, true);
    NvsNpkEntry entry;
    size_t len = _prefs.getBytesLength(key);
    bool hasData = false;
    if (len == sizeof(NvsNpkEntry)) {
        _prefs.getBytes(key, &entry, sizeof(entry));
        hasData = true;
    }
    _prefs.end();

    if (!hasData) {
        uint8_t buf[AGRI_HEADER_LEN];
        webSocket.sendBIN(clientNum, buf, agriPackFrame(AGRI_MSG_NPK_CHUNK_END, nullptr, 0, buf));
        return;
    }

    AgriPkt_NpkReading r;
    r.timestamp = entry.ts;
    r.x = entry.x;
    r.y = entry.y;
    r.n = entry.n;
    r.p = entry.p;
    r.k = entry.k;
    r.moisture = entry.moisture;
    r.ec = entry.ec;
    r.ph = entry.ph;
    r.temp = entry.temp;
    r.gridX = gridX;
    r.gridY = gridY;

    uint8_t payloadBuf[1 + sizeof(AgriPkt_NpkReading)];
    payloadBuf[0] = 1;
    memcpy(payloadBuf + 1, &r, sizeof(AgriPkt_NpkReading));
    
    uint8_t frameBuf[AGRI_HEADER_LEN + sizeof(payloadBuf)];
    webSocket.sendBIN(clientNum, frameBuf, agriPackFrame(AGRI_MSG_NPK_CHUNK, payloadBuf, sizeof(payloadBuf), frameBuf));

    uint8_t endBuf[AGRI_HEADER_LEN];
    webSocket.sendBIN(clientNum, endBuf, agriPackFrame(AGRI_MSG_NPK_CHUNK_END, nullptr, 0, endBuf));
}

void npkSendFullHistory(uint8_t clientNum) {
    _prefs.begin(NVS_NPK_NS, true);
    
    const int CHUNK_SIZE = 10;
    AgriPkt_NpkReading chunk[CHUNK_SIZE];
    int count = 0;

    for (int r = 0; r < HEATMAP_ROWS; r++) {
        for (int c = 0; c < HEATMAP_COLS; c++) {
            char key[24];
            getNvsKey(key, sizeof(key), c, r);
            
            if (_prefs.isKey(key)) {
                size_t len = _prefs.getBytesLength(key);
                if (len == sizeof(NvsNpkEntry)) {
                NvsNpkEntry entry;
                _prefs.getBytes(key, &entry, sizeof(entry));
                
                AgriPkt_NpkReading& pk = chunk[count];
                pk.timestamp = entry.ts;
                pk.x = entry.x;
                pk.y = entry.y;
                pk.n = entry.n;
                pk.p = entry.p;
                pk.k = entry.k;
                pk.moisture = entry.moisture;
                pk.ec = entry.ec;
                pk.ph = entry.ph;
                pk.temp = entry.temp;
                pk.gridX = c;
                pk.gridY = r;

                count++;

                if (count >= CHUNK_SIZE) {
                    uint8_t payloadBuf[1 + sizeof(AgriPkt_NpkReading) * CHUNK_SIZE];
                    payloadBuf[0] = count;
                    memcpy(payloadBuf + 1, chunk, sizeof(AgriPkt_NpkReading) * count);
                    
                    uint8_t frameBuf[AGRI_HEADER_LEN + sizeof(payloadBuf)];
                    webSocket.sendBIN(clientNum, frameBuf, agriPackFrame(AGRI_MSG_NPK_CHUNK, payloadBuf, sizeof(payloadBuf), frameBuf));
                    webSocket.waitTxBufferReady(clientNum);
                    count = 0;
                }
                }
            }
        }
    }
    _prefs.end();

    if (count > 0) {
        uint8_t payloadBuf[1 + sizeof(AgriPkt_NpkReading) * 10];
        payloadBuf[0] = count;
        memcpy(payloadBuf + 1, chunk, sizeof(AgriPkt_NpkReading) * count);
        
        uint8_t frameBuf[AGRI_HEADER_LEN + sizeof(payloadBuf)];
        webSocket.sendBIN(clientNum, frameBuf, agriPackFrame(AGRI_MSG_NPK_CHUNK, payloadBuf, 1 + sizeof(AgriPkt_NpkReading) * count, frameBuf));
        webSocket.waitTxBufferReady(clientNum);
    }

    uint8_t endBuf[AGRI_HEADER_LEN];
    webSocket.sendBIN(clientNum, endBuf, agriPackFrame(AGRI_MSG_NPK_CHUNK_END, nullptr, 0, endBuf));
}

// ============================================================================
// PUBLIC API
// ============================================================================

void npkInit() {
    pinMode(NPK_DERE, OUTPUT);
    digitalWrite(NPK_DERE, LOW);  // Default to receive mode
    NpkSerial.begin(NPK_BAUD, SERIAL_8N1, NPK_RX_PIN, NPK_TX_PIN);
    AgriLog(TAG_SENSORS, LEVEL_INFO, "Sensor initialised (RS485 UART2)");
}

void npkLoop() {
#if !HW_NPK_CONNECTED
    return;  // Sensor not wired yet
#endif
    if (millis() - _lastPollMs < NPK_POLL_INTERVAL_MS) return;
    _lastPollMs = millis();

    // Don't poll during alarm recovery
    if (sysState.getOperation() == OP_ALARM_RECOVERY) return;

    npkReadNow();
}
