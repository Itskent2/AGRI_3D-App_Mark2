#pragma once
#include "SystemEnums.h"
#include <Arduino.h>
#include <stdarg.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include "agri3d_config.h"

/**
 * @brief Centralized logger for AGRI-3D.
 * Supports granular tags and log levels for Flutter filtering.
 * Uses 3-byte binary headers over WebSocket.
 */

extern SemaphoreHandle_t logMutex;

/**
 * @brief Initialize the logging mutex.
 */
void loggerInit();

/**
 * @brief Send a raw binary frame to all connected clients.
 */
extern void broadcastBinaryFrame(uint8_t* payload, size_t len);

/**
 * @brief Main binary logging function. Thread-safe via logMutex.
 */
inline void AgriLogBinary(LogSubsystem subsystem, LogLevel level, LogDetail detail, const char* format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    size_t msgLen = strlen(buffer);
    if (msgLen > 250) msgLen = 250; // Cap to fit in frame

    // Build binary frame for logMessage (0x08)
    // Frame: [0x5A, 0x08, payloadLen] + [metaA, metaB, strLen] + [string...]
    uint8_t payloadLen = 3 + msgLen;
    uint8_t frame[255];
    
    frame[0] = 0x5A; // Sync
    frame[1] = 0x08; // MSG_LOG
    frame[2] = payloadLen;
    
    // Meta A: Source (2 bits) | Subsystem (5 bits) | Reserved (1 bit)
    // Source = ESP32 (1)
    frame[3] = ((1 & 0x03) << 6) | ((subsystem & 0x1F) << 1);
    
    // Meta B: Detail (4 bits) | Level (2 bits) | Reserved (2 bits)
    frame[4] = ((detail & 0x0F) << 4) | ((level & 0x03) << 2);
    
    // String Length
    frame[5] = msgLen;

    // String Data
    memcpy(&frame[6], buffer, msgLen);

    if (logMutex != NULL) {
        if (xSemaphoreTake(logMutex, pdMS_TO_TICKS(100)) == pdTRUE) {
#if !USB_BRIDGE_TEST
            // Also print to Serial for debugging
            Serial.printf("[ESP32][%d][%d] %s\n", subsystem, level, buffer);
#endif
            xSemaphoreGive(logMutex);
        } else {
#if !USB_BRIDGE_TEST
            Serial.print("[LOCK_FAIL] ");
            Serial.println(buffer);
#endif
        }
    } else {
#if !USB_BRIDGE_TEST
        Serial.printf("[BOOT][%d][%d] %s\n", subsystem, level, buffer);
#endif
    }
    
    broadcastBinaryFrame(frame, 3 + payloadLen);
}

/**
 * @brief Map legacy LogTag to new LogSubsystem.
 */
inline LogSubsystem mapTagToSubsystem(LogTag tag) {
    switch (tag) {
        case TAG_SYSTEM:  return SUB_SYSTEM;
        case TAG_NET:     return SUB_NET;
        case TAG_GRBL:    return SUB_GRBL;
        case TAG_CAM:     return SUB_SCAN; // Map CAM to SCAN
        case TAG_AI:      return SUB_AI;
        case TAG_ROUTINE: return SUB_SYSTEM;
        case TAG_SCAN:    return SUB_SCAN;
        case TAG_WEED:    return SUB_AI; // Map WEED to AI
        case TAG_ENV:     return SUB_ENV;
        case TAG_FERT:    return SUB_FERT;
        case TAG_SD:      return SUB_SD;
        case TAG_SENSORS: return SUB_ENV; // Default mapping
        case TAG_CMD:     return SUB_NET;
        case TAG_STATE:   return SUB_SYSTEM;
        default:          return SUB_SYSTEM;
    }
}

/**
 * @brief Legacy compatible logger.
 */
#define AgriLog(tag, level, fmt, ...) AgriLogBinary(mapTagToSubsystem(tag), level, DET_NONE, fmt, ##__VA_ARGS__)
