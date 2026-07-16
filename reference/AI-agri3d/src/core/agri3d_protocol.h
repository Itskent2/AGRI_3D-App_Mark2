/**
 * @file agri3d_protocol.h
 * @brief AGRI-3D Binary WebSocket Frame Protocol — Single Source of Truth (ESP32 side).
 *
 * ═══════════════════════════════════════════════════════════════════════════════
 * PROTOCOL OVERVIEW
 * ═══════════════════════════════════════════════════════════════════════════════
 *
 * All binary frames (both ESP32→Flutter and Flutter→ESP32) share the same
 * 8-byte fixed header:
 *
 *   Offset  Size  Field
 *   ──────  ────  ──────────────────────────────────────────────────────────
 *     0      1    MAGIC       = 0xA3  (identifies an AGRI-3D binary frame)
 *     1      1    VERSION     = 0x01  (protocol version — bump on breaking changes)
 *     2      1    MSG_TYPE    (see AgriMsgType enum below)
 *     3      1    RESERVED    (send 0x00 — reserved for future frame flags)
 *     4–5    2    PAYLOAD_LEN (uint16 LE — byte count of payload, NOT including header)
 *     6–7    2    CRC16       (Modbus CRC16 over bytes [0..5] + all payload bytes)
 *     8+     N    Payload     (fixed-width struct per MSG_TYPE, see structs below)
 *
 * BYTE ORDER: All multi-byte fields are LITTLE-ENDIAN (native to ESP32 Xtensa).
 *
 * CRC16: Modbus polynomial (0xA001). Covers every byte in the frame EXCEPT
 *        the two CRC bytes themselves (offsets 6–7).
 *        CRC is the LAST thing written when packing and the FIRST thing checked
 *        when parsing. Frames with a bad CRC are silently dropped.
 *
 * ═══════════════════════════════════════════════════════════════════════════════
 * MSG_TYPE RANGES
 * ═══════════════════════════════════════════════════════════════════════════════
 *
 *   0x01–0x1F  ESP32 → Flutter  (telemetry, events)
 *   0x80–0x9F  Flutter → ESP32  (commands)
 *
 * ═══════════════════════════════════════════════════════════════════════════════
 * PLANT MAP CONSTRAINTS
 * ═══════════════════════════════════════════════════════════════════════════════
 *
 *   AGRI3D_PLANT_NAME_MAX = 16  (15 usable ASCII chars + null terminator)
 *   AGRI3D_PLANT_MAX      = 30  (physical bed capacity)
 *
 *   Each plant record is exactly AGRI3D_PLANT_RECORD_SIZE bytes (60 bytes).
 *   The full plant map (30 plants) fits in a single binary frame ≤ 1809 bytes.
 *
 * ═══════════════════════════════════════════════════════════════════════════════
 * FIXED-POINT ENCODING
 * ═══════════════════════════════════════════════════════════════════════════════
 *
 *   Gantry positions (X/Y/Z) are float32 for mm-accurate moves.
 *   NPK sensor values are int16 fixed-point to save space:
 *     N, P, K          → int16 × 10   (e.g. 850  → 85.0 mg/kg)
 *     moisture         → int16 × 10   (e.g. 453  → 45.3 %)
 *     pH               → int16 × 100  (e.g. 680  → 6.80)
 *     temperature      → int16 × 10   (e.g. 285  → 28.5 °C, signed for sub-zero)
 *     EC               → int16 × 1    (µS/cm integer, no scaling)
 *     NPK in plant rec → int16 × 10
 *
 * ═══════════════════════════════════════════════════════════════════════════════
 * HOW TO ADD A NEW MESSAGE TYPE
 * ═══════════════════════════════════════════════════════════════════════════════
 *
 *   ESP32 side (this file):
 *     1. Add entry to AgriMsgType enum.
 *     2. Define a packed struct AgriPkt_XxxYyy below.
 *     3. Add a packXxxYyy() helper function declaration.
 *     4. Implement in agri3d_protocol.cpp.
 *
 *   Dart side (agri3d_protocol.dart):
 *     1. Add to AgriMsgType enum.
 *     2. Add decode case in AgriFrame.decode().
 *     3. Add a decodeXxxYyy() method.
 *
 * ═══════════════════════════════════════════════════════════════════════════════
 */

#pragma once
#include <Arduino.h>

// ── Protocol Constants ────────────────────────────────────────────────────────

/** Magic byte — first byte of every binary frame. */
static constexpr uint8_t AGRI_MAGIC   = 0xA3;

/** Protocol version — increment on any breaking frame-format change. */
static constexpr uint8_t AGRI_VERSION = 0x01;

/** Size of the fixed frame header in bytes. */
static constexpr uint8_t AGRI_HEADER_LEN = 8;

/** Maximum plant name length including null terminator (15 usable chars). */
static constexpr uint8_t AGRI3D_PLANT_NAME_MAX = 16;

/** Physical bed capacity — max plants in a single PLANT_MAP frame. */
static constexpr uint8_t AGRI3D_PLANT_MAX = 30;

/** Size of one packed plant record in bytes. */
static constexpr uint8_t AGRI3D_PLANT_RECORD_SIZE = 60;

// ── Message Type Enum ─────────────────────────────────────────────────────────

/**
 * @brief All binary message types for both directions.
 *
 * Range 0x01–0x1F: ESP32 → Flutter (telemetry / events)
 * Range 0x80–0x9F: Flutter → ESP32 (commands)
 */
enum AgriMsgType : uint8_t {
    // ── ESP32 → Flutter (Telemetry) ──────────────────────────────────────────
    AGRI_MSG_STATE_UPDATE    = 0x01, ///< Full system state snapshot (20-byte payload)
    AGRI_MSG_POSITION_UPDATE = 0x02, ///< Gantry X/Y/Z only (12-byte payload)
    AGRI_MSG_NPK_READING     = 0x03, ///< Single NPK + env reading (28-byte payload)
    AGRI_MSG_PONG            = 0x04, ///< Heartbeat reply (8-byte payload)
    AGRI_MSG_JOB_PROGRESS    = 0x05, ///< Operation progress % (3-byte payload)
    AGRI_MSG_CMD_ACK         = 0x06, ///< Command acknowledge (2-byte payload)
    AGRI_MSG_PLANT_MAP       = 0x07, ///< Full plant registry (variable, ≤1809 bytes)
    AGRI_MSG_LOG             = 0x08, ///< Log message (3-byte meta header + string)
    AGRI_MSG_DIMS            = 0x09, ///< Machine dims (12 bytes: float X/Y/Z)
    AGRI_MSG_NPK_CHUNK       = 0x0A, ///< Chunk of NPK history readings
    AGRI_MSG_NPK_CHUNK_END   = 0x0B, ///< End of NPK history chunking
    AGRI_MSG_SD_INFO         = 0x0D, ///< SD gcode file info (hasFile, size)

    // ── Flutter → ESP32 (Commands) ────────────────────────────────────────────
    AGRI_CMD_PING            = 0x80, ///< Latency ping (4-byte payload: uint32 ping_no)
    AGRI_CMD_AUTH            = 0x81, ///< HMAC auth response (32-byte payload: hash bytes)
    AGRI_CMD_START_STREAM    = 0x82, ///< Begin JPEG live stream (0-byte payload)
    AGRI_CMD_STOP_STREAM     = 0x83, ///< Stop live stream (0-byte payload)
    AGRI_CMD_SET_FPM         = 0x84, ///< Set frames per minute (2-byte payload: uint16)
    AGRI_CMD_SET_RES         = 0x85, ///< Set camera resolution (1-byte payload: uint8)
    AGRI_CMD_HOME_X          = 0x86, ///< Home X axis (0-byte payload)
    AGRI_CMD_HOME_Y          = 0x87, ///< Home Y axis (0-byte payload)
    AGRI_CMD_UNLOCK          = 0x88, ///< GRBL alarm unlock $clr (0-byte payload)
    AGRI_CMD_ESTOP           = 0x89, ///< Emergency stop Ctrl-X (0-byte payload)
    AGRI_CMD_GET_STATE       = 0x8A, ///< Request full state broadcast (0-byte payload)
    AGRI_CMD_GET_NPK         = 0x8B, ///< Trigger immediate NPK reading (0-byte payload)
    AGRI_CMD_WATER           = 0x8C, ///< Water at position (20-byte payload: 5× float32)
    AGRI_CMD_FERTILIZE       = 0x8D, ///< Fertilize at position (20-byte payload: 5× float32)
    AGRI_CMD_GET_PLANT_MAP   = 0x8E, ///< Request plant registry (0-byte payload)
    AGRI_CMD_CLEAR_PLANTS    = 0x8F, ///< Clear all plants (0-byte payload)
    AGRI_CMD_DELETE_PLANT    = 0x90, ///< Delete one plant (2-byte payload: uint16 idx)
    AGRI_CMD_DIP_ALL         = 0x91, ///< NPK dip all plants (0-byte payload)
    AGRI_CMD_AUTO_FARM       = 0x92, ///< Start autonomous farming (0-byte payload)
    AGRI_CMD_REBOOT          = 0x93, ///< Reboot ESP32 (0-byte payload)
    AGRI_CMD_GET_DIMS        = 0x94, ///< Request machine dimensions (0-byte payload)
    AGRI_CMD_SET_CAM_OFFSET  = 0x95, ///< Set camera offset mm (4-byte payload: float32)
    AGRI_CMD_SET_WATER_RATE  = 0x96, ///< Set water flow rate (4-byte payload: float32)
    AGRI_CMD_SET_FERT_RATE   = 0x97, ///< Set fertiliser flow rate (4-byte payload: float32)
    AGRI_CMD_NPK_HISTORY     = 0x98, ///< Request history for grid cell (2-byte: gx, gy)
    AGRI_CMD_SCAN_NPK        = 0x99, ///< NPK grid scan (8-byte payload: float32 x, y)
    AGRI_CMD_CLEAR_CRASH     = 0x9A, ///< Clear NVS crash record (0-byte payload)
    AGRI_CMD_RUN_FARMING_CYCLE = 0x9B, ///< Full farming cycle (8-byte: float32 zSensor, zCam)
    AGRI_CMD_REGISTER_PLANT  = 0x9C, ///< Register/Update plant (AGRI3D_PLANT_RECORD_SIZE bytes)
};

// ── Flags byte (STATE_UPDATE byte 5) ─────────────────────────────────────────

/** Bit positions inside the STATE_UPDATE flags byte. */
static constexpr uint8_t AGRI_FLAG_STREAMING  = (1 << 0); ///< Live stream active
static constexpr uint8_t AGRI_FLAG_CAMERA     = (1 << 1); ///< Camera available
static constexpr uint8_t AGRI_FLAG_SCAN_READY = (1 << 2); ///< SD scan ready to upload
// Bits 3–7 are RESERVED for future boolean flags (e.g. isRaining, isAutonomous)

// ── Plant flags word (PlantRecord bytes 2–3) ──────────────────────────────────

static constexpr uint16_t AGRI_PLANT_FLAG_CONFIRMED = (1 << 0); ///< Plant confirmed by user
static constexpr uint16_t AGRI_PLANT_FLAG_ACTIVE    = (1 << 1); ///< Plant slot active
// Bits 2–15 RESERVED

// ── Packed Payload Structs ────────────────────────────────────────────────────
// All structs use __attribute__((packed)) so the compiler inserts no padding
// between fields. This guarantees byte offsets match the protocol spec exactly.

/**
 * @brief STATE_UPDATE payload — 20 bytes.
 *
 * Carries the full system state snapshot. Sent whenever any state field
 * changes (with a 50 ms debounce to batch rapid changes).
 *
 * Enum values match SystemEnums.h exactly — the Dart side mirrors them.
 */
struct __attribute__((packed)) AgriPkt_StateUpdate {
    uint8_t  wifi;        ///< WifiState      (0=disconnected 1=connecting 2=connected)
    uint8_t  nano;        ///< NanoState      (0=unknown 1=connected 2=unresponsive)
    uint8_t  grbl;        ///< GrblState      (0-8, see SystemEnums.h)
    uint8_t  operation;   ///< OperationState (0-10, see SystemEnums.h)
    uint8_t  environment; ///< EnvironmentState (0-3)
    uint8_t  flags;       ///< Boolean flags  (see AGRI_FLAG_* constants above)
    uint8_t  resolution;  ///< framesize_t cast to uint8
    uint8_t  reserved;    ///< Send 0x00 — reserved for future use
    float    x;           ///< Gantry X mm (float32 LE)
    float    y;           ///< Gantry Y mm (float32 LE)
    float    z;           ///< Gantry Z mm (float32 LE)
};
static_assert(sizeof(AgriPkt_StateUpdate) == 20, "AgriPkt_StateUpdate must be 20 bytes");

/**
 * @brief POSITION_UPDATE payload — 12 bytes.
 *
 * Lightweight position-only frame for high-frequency position updates
 * (e.g. during active moves). Avoids sending the full STATE_UPDATE payload.
 */
struct __attribute__((packed)) AgriPkt_PositionUpdate {
    float x; ///< Gantry X mm (float32 LE)
    float y; ///< Gantry Y mm (float32 LE)
    float z; ///< Gantry Z mm (float32 LE)
};
static_assert(sizeof(AgriPkt_PositionUpdate) == 12, "AgriPkt_PositionUpdate must be 12 bytes");

/**
 * @brief NPK_READING payload — 28 bytes.
 *
 * Replaces the four separate JSON broadcasts (NPK, NPK_N, NPK_P, NPK_K)
 * that agri3d_npk.cpp previously sent per reading.
 *
 * Fixed-point encoding (see file header for scale factors):
 *   n, p, k       → int16 × 10   (divide by 10.0 in Dart)
 *   moisture      → int16 × 10
 *   ec            → int16 × 1    (raw µS/cm)
 *   ph            → int16 × 100  (divide by 100.0 in Dart)
 *   temp          → int16 × 10   signed — handles negative temperatures
 */
struct __attribute__((packed)) AgriPkt_NpkReading {
    uint32_t timestamp;  ///< Unix epoch seconds
    float    x;          ///< Gantry X mm at time of reading
    float    y;          ///< Gantry Y mm at time of reading
    int16_t  n;          ///< Nitrogen   × 10  (mg/kg)
    int16_t  p;          ///< Phosphorus × 10  (mg/kg)
    int16_t  k;          ///< Potassium  × 10  (mg/kg)
    int16_t  moisture;   ///< Moisture   × 10  (%)
    int16_t  ec;         ///< Electrical conductivity (µS/cm)
    int16_t  ph;         ///< pH         × 100
    int16_t  temp;       ///< Temperature× 10  (°C, signed)
    uint8_t  gridX;      ///< Heatmap grid column (0–HEATMAP_COLS-1)
    uint8_t  gridY;      ///< Heatmap grid row    (0–HEATMAP_ROWS-1)
};
static_assert(sizeof(AgriPkt_NpkReading) == 28, "AgriPkt_NpkReading must be 28 bytes");

/**
 * @brief PONG payload — 8 bytes.
 *
 * Reply to AGRI_CMD_PING. Flutter uses millis() to measure round-trip latency.
 * ping_no is echoed from the CMD_PING payload so Flutter can match request→reply.
 */
struct __attribute__((packed)) AgriPkt_Pong {
    uint32_t millisNow; ///< ESP32 millis() at time of PONG
    uint32_t pingNo;    ///< Echo of ping_no from CMD_PING
};
static_assert(sizeof(AgriPkt_Pong) == 8, "AgriPkt_Pong must be 8 bytes");

/**
 * @brief JOB_PROGRESS payload — 3 bytes.
 *
 * Replaces {"evt":"SD_PROGRESS","pct":N} and similar progress JSON.
 * progress is fixed-point × 100 (e.g. 4500 = 45.00%).
 */
struct __attribute__((packed)) AgriPkt_JobProgress {
    uint8_t  operation;  ///< OperationState enum value
    uint16_t progress;   ///< Progress × 100 (0–10000 = 0.00%–100.00%)
};
static_assert(sizeof(AgriPkt_JobProgress) == 3, "AgriPkt_JobProgress must be 3 bytes");

/**
 * @brief CMD_ACK payload — 2 bytes.
 *
 * Sent by ESP32 to acknowledge a received binary command.
 * result = 0 → OK, 1 → BUSY, 2 → ERROR.
 */
struct __attribute__((packed)) AgriPkt_CmdAck {
    uint8_t cmdType; ///< AgriMsgType of the command being acknowledged
    uint8_t result;  ///< 0=OK  1=BUSY  2=ERROR
};
static_assert(sizeof(AgriPkt_CmdAck) == 2, "AgriPkt_CmdAck must be 2 bytes");

struct __attribute__((packed)) AgriPkt_Dims {
    float maxX;
    float maxY;
    float maxZ;
    uint8_t valid;
};
static_assert(sizeof(AgriPkt_Dims) == 13, "AgriPkt_Dims must be 13 bytes");


/**
 * @brief Single plant record within a PLANT_MAP frame — 60 bytes.
 *
 * All plant records are exactly this size. The plant map frame payload starts
 * with a uint8 plant_count, followed by plant_count of these records.
 *
 * name[] is null-padded ASCII. Max 15 usable characters + null terminator.
 * Dart decodes with: String.fromCharCodes(bytes.where((b) => b != 0)).
 *
 * plant_flags bit layout:
 *   bit 0 = confirmed by user
 *   bit 1 = active slot
 *   bit 2–15 = RESERVED
 *
 * NPK values (npkN/P/K, targetN/P/K) are int16 × 10.
 * Divide by 10.0 in Dart to get mg/kg.
 */
struct __attribute__((packed)) AgriPkt_SdInfo {
    uint8_t  hasFile;
    uint32_t fileSize;
};
static_assert(sizeof(AgriPkt_SdInfo) == 5, "AgriPkt_SdInfo must be 5 bytes");

struct __attribute__((packed)) AgriPlantRecord {
    uint16_t id;                            ///< Plant index (matches Plot.id in Dart)
    uint16_t plantFlags;                    ///< AGRI_PLANT_FLAG_* bits
    char     name[AGRI3D_PLANT_NAME_MAX];   ///< Null-padded ASCII name (16 bytes)
    float    x;                             ///< X position mm
    float    y;                             ///< Y position mm
    float    dx;                            ///< Custom dip X offset mm
    float    dy;                            ///< Custom dip Y offset mm
    float    diameter;                      ///< Rosette diameter mm
    uint8_t  cropType;                      ///< CropType enum value
    uint8_t  reserved1;                     ///< Send 0x00
    uint32_t ts;                            ///< Registration timestamp (unix seconds)
    int16_t  npkN;                          ///< Current N × 10 (mg/kg)
    int16_t  npkP;                          ///< Current P × 10
    int16_t  npkK;                          ///< Current K × 10
    int16_t  targetN;                       ///< Target N × 10
    int16_t  targetP;                       ///< Target P × 10
    int16_t  targetK;                       ///< Target K × 10
    uint16_t reserved2;                     ///< Send 0x0000
};
static_assert(sizeof(AgriPlantRecord) == 60, "AgriPlantRecord must be 60 bytes");

// ── Flutter→ESP32 Command Payload Structs ────────────────────────────────────

/**
 * @brief CMD_PING payload — 4 bytes.
 * pingNo is echoed back in the PONG response so Flutter can match pairs.
 */
struct __attribute__((packed)) AgriCmd_Ping {
    uint32_t pingNo; ///< Incrementing ping counter
};

/**
 * @brief CMD_AUTH payload — 32 bytes.
 * HMAC-SHA256 digest bytes (raw, not hex-encoded).
 */
struct __attribute__((packed)) AgriCmd_Auth {
    uint8_t hmac[32]; ///< HMAC-SHA256 of the challenge nonce
};

/**
 * @brief CMD_WATER / CMD_FERTILIZE payload — 20 bytes.
 * If ox/oy are 0.0, the ESP32 uses the current gantry position as origin.
 */
struct __attribute__((packed)) AgriCmd_Dispense {
    float x;  ///< Target X mm
    float y;  ///< Target Y mm
    float ml; ///< Volume to dispense (mL)
    float ox; ///< Origin X offset mm (0.0 = use current position)
    float oy; ///< Origin Y offset mm
};

/**
 * @brief CMD_DELETE_PLANT payload — 2 bytes.
 */
struct __attribute__((packed)) AgriCmd_DeletePlant {
    uint16_t idx; ///< Plant index to delete
};

/**
 * @brief CMD_NPK_HISTORY payload — 2 bytes.
 */
struct __attribute__((packed)) AgriCmd_NpkHistory {
    uint8_t gridX; ///< Heatmap grid column
    uint8_t gridY; ///< Heatmap grid row
};

/**
 * @brief CMD_SCAN_NPK payload — 8 bytes.
 */
struct __attribute__((packed)) AgriCmd_ScanNpk {
    float startX; ///< Scan origin X mm
    float startY; ///< Scan origin Y mm
};

/**
 * @brief CMD_RUN_FARMING_CYCLE payload — 8 bytes.
 */
struct __attribute__((packed)) AgriCmd_FarmingCycle {
    float zSensorHeight; ///< Z height for NPK dip (mm)
    float zCameraHeight; ///< Z height for camera capture (mm)
};

/**
 * @brief CMD_SET_FPM payload — 2 bytes.
 */
struct __attribute__((packed)) AgriCmd_SetFpm {
    uint16_t fpm; ///< Frames per minute (1–600)
};

/**
 * @brief Parsed incoming frame — filled by parseFrame().
 *
 * Provides typed access to the command payload without casting void*.
 * The union means only one payload field is valid at a time (the one
 * matching msgType). Always check msgType before reading a union member.
 */
struct AgriRxFrame {
    AgriMsgType msgType;     ///< Validated message type
    uint16_t    payloadLen;  ///< Payload length (bytes)
    union {
        AgriCmd_Ping          ping;
        AgriCmd_Auth          auth;
        AgriCmd_Dispense      dispense;      ///< Used for WATER and FERTILIZE
        AgriCmd_DeletePlant   deletePlant;
        AgriCmd_NpkHistory    npkHistory;
        AgriCmd_ScanNpk       scanNpk;
        AgriCmd_FarmingCycle  farmingCycle;
        AgriCmd_SetFpm        setFpm;
        uint8_t               raw[32];       ///< Single-value commands (SET_RES, SET_CAM_OFFSET, etc.)
    } payload;
};

// ── Function Declarations ─────────────────────────────────────────────────────

/**
 * @brief CRC16-Modbus checksum.
 *
 * Same algorithm used by the NPK RS485 Modbus sensor — already battle-tested
 * in agri3d_npk.cpp. Reused here as the protocol-level integrity check.
 *
 * @param data  Pointer to byte buffer
 * @param len   Number of bytes to process
 * @return      16-bit CRC (little-endian when written to the frame)
 */
uint16_t agriCrc16(const uint8_t* data, uint16_t len);

/**
 * @brief Pack a binary frame into outBuf[].
 *
 * Writes the 8-byte header (magic, version, msgType, reserved, payloadLen,
 * CRC16) followed by the payload bytes. The CRC covers bytes [0..5] plus
 * all payload bytes — computed last and written into offsets 6–7.
 *
 * @param msgType    Frame type (AgriMsgType enum)
 * @param payload    Pointer to packed payload struct (may be nullptr if len==0)
 * @param payloadLen Byte count of payload (0 for zero-payload commands)
 * @param outBuf     Destination buffer — must be ≥ (AGRI_HEADER_LEN + payloadLen) bytes
 * @return           Total frame length in bytes (header + payload)
 */
uint16_t agriPackFrame(AgriMsgType msgType,
                       const void* payload,
                       uint16_t payloadLen,
                       uint8_t* outBuf);

/**
 * @brief Parse and validate an incoming binary frame.
 *
 * Checks magic byte, version, CRC16, and payload length before populating
 * the AgriRxFrame struct. Returns false on any validation failure — the
 * caller should silently discard the frame.
 *
 * @param buf    Raw bytes received over WebSocket (WStype_BIN)
 * @param len    Number of bytes received
 * @param frame  Output struct populated on success
 * @return       true if the frame is valid and frame is populated
 */
bool agriParseFrame(const uint8_t* buf, size_t len, AgriRxFrame& frame);

// ── Convenience Pack Helpers ──────────────────────────────────────────────────
// These helpers allocate the correct buffer size on the stack, fill the
// payload struct, call agriPackFrame(), and return the total frame length.
// Pass the returned buffer directly to webSocket.sendBIN().

/** Pack a STATE_UPDATE frame. Returns total frame length. */
uint16_t agriPackStateUpdate(const AgriPkt_StateUpdate& pkt, uint8_t* outBuf);

/** Pack a POSITION_UPDATE frame. Returns total frame length. */
uint16_t agriPackPositionUpdate(const AgriPkt_PositionUpdate& pkt, uint8_t* outBuf);

/** Pack an NPK_READING frame. Returns total frame length. */
uint16_t agriPackNpkReading(const AgriPkt_NpkReading& pkt, uint8_t* outBuf);

/** Pack a PONG frame. Returns total frame length. */
uint16_t agriPackPong(const AgriPkt_Pong& pkt, uint8_t* outBuf);

/** Pack a JOB_PROGRESS frame. Returns total frame length. */
uint16_t agriPackJobProgress(const AgriPkt_JobProgress& pkt, uint8_t* outBuf);

/** Pack a CMD_ACK frame. Returns total frame length. */
uint16_t agriPackCmdAck(const AgriPkt_CmdAck& pkt, uint8_t* outBuf);

/** Pack a DIMS frame. Returns total frame length. */
uint16_t agriPackDims(const AgriPkt_Dims& pkt, uint8_t* outBuf);


/**
 * @brief Pack a PLANT_MAP frame.
 *
 * @param records    Array of AgriPlantRecord (up to AGRI3D_PLANT_MAX)
 * @param count      Number of valid records (0–AGRI3D_PLANT_MAX)
 * @param outBuf     Destination buffer — must be ≥ (AGRI_HEADER_LEN + 1 + count*60) bytes
 * @return           Total frame length
 */
uint16_t agriPackPlantMap(const AgriPlantRecord* records, uint8_t count, uint8_t* outBuf);
