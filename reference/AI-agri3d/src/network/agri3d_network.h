/**
 * @file agri3d_network.h
 * @brief WiFi management, AP fallback, mDNS, UDP discovery, and WebSocket server.
 *
 * Connection policy:
 *  1. At boot, try each network in the knownNetworks[] list in order.
 *  2. If all fail → start AP hotspot so the user can still connect directly.
 *  3. A background FreeRTOS task keeps retrying known networks every
 *     WIFI_RETRY_INTERVAL_MS while the ESP32 is in AP mode.
 *  4. When a station connection succeeds, the AP is taken down cleanly.
 *
 * Singleton policy (WS_SINGLETON = true):
 *  Only one WebSocket client is allowed at a time. A second connection
 *  attempt receives an error message and is immediately closed.
 */

#pragma once
#include <Arduino.h>
#include <WebSocketsServer.h>

class AgriWebSocketsServer : public WebSocketsServer {
public:
    AgriWebSocketsServer(uint16_t port) : WebSocketsServer(port) {}
    
    size_t getAvailableWriteSpace(uint8_t num) {
        if (num < WEBSOCKETS_SERVER_CLIENT_MAX) {
            const WSclient_t * client = &_clients[num];
            if (client && client->status == WSC_CONNECTED && client->tcp) {
                return client->tcp->availableForWrite();
            }
        }
        return 0;
    }
};

extern AgriWebSocketsServer rawWebSocket;
extern SemaphoreHandle_t wsMutex;

class ThreadSafeWebSocket {
public:
    void waitTxBufferReady(uint8_t num, size_t threshold = 512, uint32_t timeoutMs = 150) {
        uint32_t start = millis();
        while (true) {
            bool connected = false;
            size_t space = 0;
            if (wsMutex) {
                if (xSemaphoreTakeRecursive(wsMutex, portMAX_DELAY) == pdTRUE) {
                    connected = rawWebSocket.clientIsConnected(num);
                    if (connected) {
                        space = rawWebSocket.getAvailableWriteSpace(num);
                    }
                    xSemaphoreGiveRecursive(wsMutex);
                }
            } else {
                break;
            }
            if (!connected || space >= threshold || (millis() - start >= timeoutMs)) {
                break;
            }
            vTaskDelay(pdMS_TO_TICKS(5));
        }
    }

    void sendTXT(uint8_t num, const String & payload) {
        if (wsMutex && xSemaphoreTakeRecursive(wsMutex, portMAX_DELAY) == pdTRUE) {
            rawWebSocket.sendTXT(num, payload.c_str());
            xSemaphoreGiveRecursive(wsMutex);
        }
    }
    void sendTXT(uint8_t num, const char * payload) {
        if (wsMutex && xSemaphoreTakeRecursive(wsMutex, portMAX_DELAY) == pdTRUE) {
            rawWebSocket.sendTXT(num, payload);
            xSemaphoreGiveRecursive(wsMutex);
        }
    }
    bool sendBIN(uint8_t num, const uint8_t * payload, size_t length) {
        bool res = false;
        if (wsMutex && xSemaphoreTakeRecursive(wsMutex, portMAX_DELAY) == pdTRUE) {
            res = rawWebSocket.sendBIN(num, payload, length);
            xSemaphoreGiveRecursive(wsMutex);
        }
        return res;
    }
    void broadcastTXT(const String & payload) {
        if (wsMutex && xSemaphoreTakeRecursive(wsMutex, portMAX_DELAY) == pdTRUE) {
            rawWebSocket.broadcastTXT(payload.c_str());
            xSemaphoreGiveRecursive(wsMutex);
        }
    }
    void broadcastTXT(const char * payload) {
        if (wsMutex && xSemaphoreTakeRecursive(wsMutex, portMAX_DELAY) == pdTRUE) {
            rawWebSocket.broadcastTXT(payload);
            xSemaphoreGiveRecursive(wsMutex);
        }
    }
    void broadcastBIN(const uint8_t * payload, size_t length) {
        if (wsMutex && xSemaphoreTakeRecursive(wsMutex, portMAX_DELAY) == pdTRUE) {
            rawWebSocket.broadcastBIN(payload, length);
            xSemaphoreGiveRecursive(wsMutex);
        }
    }
    void disconnect(uint8_t num) {
        if (wsMutex && xSemaphoreTakeRecursive(wsMutex, portMAX_DELAY) == pdTRUE) {
            rawWebSocket.disconnect(num);
            xSemaphoreGiveRecursive(wsMutex);
        }
    }
    void begin() {
        rawWebSocket.begin();
    }
    void loop() {
        if (wsMutex && xSemaphoreTakeRecursive(wsMutex, portMAX_DELAY) == pdTRUE) {
            rawWebSocket.loop();
            xSemaphoreGiveRecursive(wsMutex);
        }
    }
    template <typename T>
    void onEvent(T cb) {
        rawWebSocket.onEvent(cb);
    }
};

extern ThreadSafeWebSocket webSocket;

/** The currently-connected singleton client number (-1 = none). */
extern int8_t activeClientNum;
extern TaskHandle_t networkTaskHandle;

/**
 * @brief Try to connect to each known WiFi network in order.
 *        Falls back to AP mode if all fail.
 *        Called once from setup().
 */
void networkInit();

/** Broadcast the UDP discovery beacon (called internally by networkLoop). */
void sendDiscoveryBeacon();

/** Start AP hotspot fallback. */
void startAPMode();

/** Stop AP mode (called when a station connection succeeds in background). */
void stopAPMode();

/** @return true while the ESP32 is running as an AP (hotspot). */
bool isAPMode();

/**
 * @brief Drain log messages queued by Core-1 tasks and broadcast them.
 *        MUST be called only from Core 0 (the network loop task).
 */
void drainLogQueue();
