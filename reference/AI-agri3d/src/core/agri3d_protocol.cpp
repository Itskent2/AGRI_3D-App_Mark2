/**
 * @file agri3d_protocol.cpp
 * @brief AGRI-3D Binary Frame Protocol — Implementation.
 *
 * See agri3d_protocol.h for full protocol documentation.
 *
 * This file provides:
 *   - agriCrc16()        — Modbus CRC16 (reused from agri3d_npk.cpp pattern)
 *   - agriPackFrame()    — Generic frame packer
 *   - agriParseFrame()   — Generic frame parser / validator
 *   - agriPackXxx()      — Per-message-type convenience packers
 */

#include "agri3d_protocol.h"
#include "agri3d_logger.h"

// ============================================================================
// CRC16 — MODBUS
// ============================================================================

/**
 * Modbus CRC16 using polynomial 0xA001 (reflected form of 0x8005).
 *
 * This is the same algorithm used by the NPK RS485 Modbus sensor in
 * agri3d_npk.cpp::calculateCRC(). Using the same algorithm across the
 * whole codebase avoids two different CRC implementations.
 *
 * Performance: ~50 ns per byte on ESP32 at 240 MHz — negligible for our
 * frame sizes (max ~1800 bytes → ~90 µs worst-case).
 */
uint16_t agriCrc16(const uint8_t* data, uint16_t len) {
    uint16_t crc = 0xFFFF;
    for (uint16_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

// ============================================================================
// GENERIC FRAME PACK / PARSE
// ============================================================================

/**
 * Frame layout written by agriPackFrame():
 *
 *   [0]     MAGIC   = 0xA3
 *   [1]     VERSION = 0x01
 *   [2]     msgType
 *   [3]     0x00    (reserved)
 *   [4–5]   payloadLen (uint16 LE)
 *   [6–7]   CRC16 of bytes [0..5] + payload (uint16 LE)
 *   [8..]   payload bytes
 *
 * CRC is computed over: header bytes 0–5 AND all payload bytes.
 * The CRC field itself (offsets 6–7) is excluded from the CRC computation.
 */
uint16_t agriPackFrame(AgriMsgType msgType,
                       const void* payload,
                       uint16_t payloadLen,
                       uint8_t* outBuf) {
    // ── Fill header ──────────────────────────────────────────────────────────
    outBuf[0] = AGRI_MAGIC;
    outBuf[1] = AGRI_VERSION;
    outBuf[2] = (uint8_t)msgType;
    outBuf[3] = 0x00; // reserved
    outBuf[4] = (uint8_t)(payloadLen & 0xFF);        // payload_len low byte
    outBuf[5] = (uint8_t)((payloadLen >> 8) & 0xFF); // payload_len high byte

    // ── Copy payload ─────────────────────────────────────────────────────────
    if (payload != nullptr && payloadLen > 0) {
        memcpy(outBuf + AGRI_HEADER_LEN, payload, payloadLen);
    }

    // ── Compute CRC over header[0..5] + payload ──────────────────────────────
    // We build a contiguous region: first 6 header bytes then payload.
    // Since they ARE already contiguous in outBuf (header at 0..5, payload
    // at 8..N), we must compute in two passes (skip the CRC slot at 6–7).
    uint16_t crc = 0xFFFF;
    // Pass 1: header bytes 0–5
    for (int i = 0; i < 6; i++) {
        crc ^= outBuf[i];
        for (int j = 0; j < 8; j++) {
            crc = (crc & 1) ? (crc >> 1) ^ 0xA001 : crc >> 1;
        }
    }
    // Pass 2: payload bytes 8..
    for (uint16_t i = 0; i < payloadLen; i++) {
        crc ^= outBuf[AGRI_HEADER_LEN + i];
        for (int j = 0; j < 8; j++) {
            crc = (crc & 1) ? (crc >> 1) ^ 0xA001 : crc >> 1;
        }
    }

    // ── Write CRC into bytes 6–7 (little-endian) ─────────────────────────────
    outBuf[6] = (uint8_t)(crc & 0xFF);
    outBuf[7] = (uint8_t)((crc >> 8) & 0xFF);

    return AGRI_HEADER_LEN + payloadLen;
}

/**
 * Parses and validates an incoming binary WebSocket frame.
 *
 * Validation steps (fail-fast, in order):
 *   1. Minimum length: must be ≥ AGRI_HEADER_LEN (8 bytes)
 *   2. Magic byte: outBuf[0] must equal 0xA3
 *   3. Version:    outBuf[1] must equal 0x01 (reject future versions gracefully)
 *   4. Length:     PAYLOAD_LEN field must match actual received byte count
 *   5. CRC16:      recompute and compare
 *
 * If all checks pass, the payload is memcpy'd into frame.payload.raw
 * (or the specific union member) and frame.msgType is set.
 */
bool agriParseFrame(const uint8_t* buf, size_t len, AgriRxFrame& frame) {
    // 1. Minimum size
    if (len < AGRI_HEADER_LEN) return false;

    // 2. Magic
    if (buf[0] != AGRI_MAGIC) return false;

    // 3. Version
    if (buf[1] != AGRI_VERSION) {
        AgriLog(TAG_NET, LEVEL_WARN,
                "Binary frame version mismatch: got 0x%02X, expected 0x%02X",
                buf[1], AGRI_VERSION);
        return false;
    }

    // 4. Payload length
    uint16_t payloadLen = (uint16_t)buf[4] | ((uint16_t)buf[5] << 8);
    if ((size_t)(AGRI_HEADER_LEN + payloadLen) != len) {
        AgriLog(TAG_NET, LEVEL_WARN,
                "Binary frame length mismatch: header says %u payload bytes, got %u total",
                payloadLen, (unsigned)len);
        return false;
    }

    // 5. CRC — recompute over header[0..5] + payload, compare to stored [6–7]
    uint16_t storedCrc = (uint16_t)buf[6] | ((uint16_t)buf[7] << 8);
    uint16_t calcCrc   = 0xFFFF;
    for (int i = 0; i < 6; i++) {
        calcCrc ^= buf[i];
        for (int j = 0; j < 8; j++) calcCrc = (calcCrc & 1) ? (calcCrc >> 1) ^ 0xA001 : calcCrc >> 1;
    }
    for (uint16_t i = 0; i < payloadLen; i++) {
        calcCrc ^= buf[AGRI_HEADER_LEN + i];
        for (int j = 0; j < 8; j++) calcCrc = (calcCrc & 1) ? (calcCrc >> 1) ^ 0xA001 : calcCrc >> 1;
    }
    if (calcCrc != storedCrc) {
        AgriLog(TAG_NET, LEVEL_WARN,
                "Binary frame CRC mismatch: got 0x%04X, expected 0x%04X — frame dropped",
                storedCrc, calcCrc);
        return false;
    }

    // ── All checks passed — populate output struct ────────────────────────────
    frame.msgType    = (AgriMsgType)buf[2];
    frame.payloadLen = payloadLen;

    if (payloadLen > 0 && payloadLen <= sizeof(frame.payload)) {
        memcpy(&frame.payload, buf + AGRI_HEADER_LEN, payloadLen);
    }

    return true;
}

// ============================================================================
// CONVENIENCE PACKERS
// ============================================================================

uint16_t agriPackStateUpdate(const AgriPkt_StateUpdate& pkt, uint8_t* outBuf) {
    return agriPackFrame(AGRI_MSG_STATE_UPDATE, &pkt, sizeof(pkt), outBuf);
}

uint16_t agriPackPositionUpdate(const AgriPkt_PositionUpdate& pkt, uint8_t* outBuf) {
    return agriPackFrame(AGRI_MSG_POSITION_UPDATE, &pkt, sizeof(pkt), outBuf);
}

uint16_t agriPackNpkReading(const AgriPkt_NpkReading& pkt, uint8_t* outBuf) {
    return agriPackFrame(AGRI_MSG_NPK_READING, &pkt, sizeof(pkt), outBuf);
}

uint16_t agriPackPong(const AgriPkt_Pong& pkt, uint8_t* outBuf) {
    return agriPackFrame(AGRI_MSG_PONG, &pkt, sizeof(pkt), outBuf);
}

uint16_t agriPackJobProgress(const AgriPkt_JobProgress& pkt, uint8_t* outBuf) {
    return agriPackFrame(AGRI_MSG_JOB_PROGRESS, &pkt, sizeof(pkt), outBuf);
}

uint16_t agriPackCmdAck(const AgriPkt_CmdAck& pkt, uint8_t* outBuf) {
    return agriPackFrame(AGRI_MSG_CMD_ACK, &pkt, sizeof(pkt), outBuf);
}

uint16_t agriPackDims(const AgriPkt_Dims& pkt, uint8_t* outBuf) {
    return agriPackFrame(AGRI_MSG_DIMS, &pkt, sizeof(pkt), outBuf);
}

uint16_t agriPackPlantMap(const AgriPlantRecord* records, uint8_t count, uint8_t* outBuf) {
    // Plant map payload: [uint8 count] + [count × AgriPlantRecord]
    // Build into a temporary buffer on the stack (max size: 1 + 30×60 = 1801 bytes).
    // Using a local VLA would be non-standard; use a fixed max-size array instead.
    static uint8_t plantPayload[1 + AGRI3D_PLANT_MAX * AGRI3D_PLANT_RECORD_SIZE];

    uint8_t safeCount = (count > AGRI3D_PLANT_MAX) ? AGRI3D_PLANT_MAX : count;
    plantPayload[0] = safeCount;
    if (safeCount > 0) {
        memcpy(plantPayload + 1, records, safeCount * AGRI3D_PLANT_RECORD_SIZE);
    }

    uint16_t payloadLen = 1 + safeCount * AGRI3D_PLANT_RECORD_SIZE;
    return agriPackFrame(AGRI_MSG_PLANT_MAP, plantPayload, payloadLen, outBuf);
}
