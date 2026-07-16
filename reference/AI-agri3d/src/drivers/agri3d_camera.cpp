/**
 * @file agri3d_camera.cpp
 * @brief Camera init, FPM stream task, and captureFrameAtPosition()
 * implementation.
 */

#include "agri3d_camera.h"
#include "agri3d_config.h"
#include "agri3d_grbl.h"
#include "agri3d_network.h"
#include "agri3d_sd.h"
#include "agri3d_state.h"
#include "../core/agri3d_logger.h"
#include "../core/agri3d_ai.h"
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <math.h>
#include <time.h>

// Forward declaration for task
void streamTask(void *pvParameters);

WiFiServer mjpegServer(WS_STREAM_PORT);
WiFiClient* activeMjpegClient = nullptr;

// ============================================================================
// CAMERA INITIALISATION
// ============================================================================

bool cameraInit() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = CAM_Y2;
  config.pin_d1 = CAM_Y3;
  config.pin_d2 = CAM_Y4;
  config.pin_d3 = CAM_Y5;
  config.pin_d4 = CAM_Y6;
  config.pin_d5 = CAM_Y7;
  config.pin_d6 = CAM_Y8;
  config.pin_d7 = CAM_Y9;
  config.pin_xclk = CAM_XCLK;
  config.pin_pclk = CAM_PCLK;
  config.pin_vsync = CAM_VSYNC;
  config.pin_href = CAM_HREF;
  config.pin_sccb_sda = CAM_SIOD;
  config.pin_sccb_scl = CAM_SIOC;
  config.pin_pwdn = CAM_PWDN;
  config.pin_reset = CAM_RESET;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // UXGA (1600×1200) — highest quality for plant-map stills
  // Requires PSRAM to be enabled in board settings
  if (psramFound()) {
    // Override: Use QVGA (320x240) to feed the 240x240 AI model 
    // while keeping file sizes small (~4KB-6KB) for the 1900ms Wi-Fi latency.
    config.frame_size = FRAMESIZE_QVGA; 
    config.jpeg_quality = 12; // 0-63, lower = higher quality
    config.fb_count = 2;      // Double buffer for smoother stream
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.grab_mode = CAMERA_GRAB_LATEST;
  } else {
    // Allocate buffers for QVGA if no PSRAM to prevent DRAM exhaustion
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
    config.fb_location = CAMERA_FB_IN_DRAM;
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    AgriLog(TAG_CAM, LEVEL_WARN, "No PSRAM — initializing with QVGA buffers");
  }

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    AgriLog(TAG_CAM, LEVEL_ERR, "Init failed (0x%x)", err);
    return false;
  }

  // Fine-tune sensor settings for agricultural (outdoor) scenes
  sensor_t *s = esp_camera_sensor_get();
  if (s) {
    // Set to the actual desired resolution after initialization
    s->set_framesize(s, sysState.getResolution());
    
    s->set_brightness(s, 0); // -2 to 2
    s->set_contrast(s, 0);   // -2 to 2
    s->set_saturation(s, 1); // Boost green for vegetation
    s->set_sharpness(s, 1);
    s->set_whitebal(s, 1);      // Auto white balance on
    s->set_awb_gain(s, 1);      // AWB gain on
    s->set_exposure_ctrl(s, 1); // Auto exposure on
    s->set_aec2(s, 1);          // Better AEC algorithm
  }

  AgriLog(TAG_CAM, LEVEL_SUCCESS, "Camera OK (UXGA JPEG)");

  // Launch stream task on Core 1 to offload it from the network/grbl loop on Core 0
  xTaskCreatePinnedToCore(streamTask, "streamTask", 8192, nullptr, 2, nullptr,
                          1);
  return true;
}

// ============================================================================
// FPM STREAM TASK
// ============================================================================

void streamTask(void * /*pvParameters*/) {
  static unsigned long _lastAiRunMs = 0;
  const uint32_t AI_INTERVAL_MS = 3000;

  mjpegServer.begin();

  while (true) {
    WiFiClient client = mjpegServer.accept();
    if (client) {
      activeMjpegClient = &client;
      AgriLog(TAG_CAM, LEVEL_INFO, "MJPEG Client connected");
      
      client.print("HTTP/1.1 200 OK\r\n");
      client.print("Content-Type: multipart/x-mixed-replace; boundary=frame\r\n");
      client.print("Access-Control-Allow-Origin: *\r\n");
      client.print("\r\n");
      
      while (client.connected()) {
        if (sysState.isStreaming() && isCameraAvailable()) {
          sysState.setStreamTaskBusy(true);
          
          camera_fb_t *fb = esp_camera_fb_get();
          if (!fb) {
            sysState.setStreamTaskBusy(false);
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
          }

          // ── RUN AI INFERENCE ──
          unsigned long nowMs = millis();
          if (aiIsReady() && (nowMs - _lastAiRunMs) >= AI_INTERVAL_MS) {
              _lastAiRunMs = nowMs;
              AiResult res = aiAnalyzeJpeg(fb->buf, fb->len, fb->width, fb->height);
              
              StaticJsonDocument<512> doc;
              doc["evt"] = "AI_DETECTIONS";
              JsonArray detections = doc.createNestedArray("detections");
              for (int i = 0; i < res.totalDetections; i++) {
                  JsonObject det = detections.createNestedObject();
                  det["label"] = res.detections[i].label;
                  det["conf"]  = res.detections[i].confidence;
                  det["x"]     = res.detections[i].x;
                  det["y"]     = res.detections[i].y;
                  det["w"]     = res.detections[i].width;
                  det["h"]     = res.detections[i].height;
              }
              String out;
              serializeJson(doc, out);
              if (activeClientNum != -1) {
                  webSocket.sendTXT(activeClientNum, out); // Send via Control socket
              }
          }

          // ── MJPEG FRAME ──
          client.print("--frame\r\n");
          client.print("Content-Type: image/jpeg\r\n");
          client.print("Content-Length: ");
          client.print(fb->len);
          client.print("\r\n\r\n");

          // Chunked write
          size_t to_send = fb->len;
          uint8_t *buf = fb->buf;
          while (to_send > 0 && client.connected()) {
              size_t chunk = (to_send > 4096) ? 4096 : to_send;
              client.write(buf, chunk);
              to_send -= chunk;
              buf += chunk;
              vTaskDelay(pdMS_TO_TICKS(1)); // Yield to LwIP
          }
          client.print("\r\n");
          
          esp_camera_fb_return(fb);
          sysState.setStreamTaskBusy(false);

          uint32_t delayMs = 60000UL / (uint32_t)sysState.getFpm();
          vTaskDelay(pdMS_TO_TICKS(delayMs));
        } else {
          vTaskDelay(pdMS_TO_TICKS(STREAM_IDLE_DELAY));
        }
      }
      activeMjpegClient = nullptr;
      client.stop();
      AgriLog(TAG_CAM, LEVEL_INFO, "MJPEG Client disconnected");
    } else {
      vTaskDelay(pdMS_TO_TICKS(STREAM_IDLE_DELAY));
    }
  }
}

// ============================================================================
// CORE CAPTURE HELPER
// ============================================================================

bool captureFrameAtPosition(uint8_t clientNum, int idx, int total,
                            float targetX, float targetY) {
  // 1. Move to position
  char gcode[48];
  // Apply camera Y-offset: camera lens is offset from the gantry centre along Y.
  // targetX/Y is the logical plant position; moveX/Y is the physical gantry position.
  float moveX = targetX;                          // X axis: no offset
  float moveY = targetY + sysState.getCamOffset(); // Y axis: camera offset applied
  snprintf(gcode, sizeof(gcode), "G0 X%.2f Y%.2f F%d", moveX, moveY,
           GRBL_DEFAULT_FEEDRATE);
  enqueueGrblCommand(gcode);
  
  if (!waitForGrblIdle(SCAN_MOVE_TIMEOUT_MS)) return false;

  // 2. Request a high-quality frame
  // We tell Core 0 to stop streaming and give us a dedicated shot
  sysState.setStreaming(false);
  delay(200); // Wait for stream task to yield

  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
      return false;
  }

  // 3. Metadata & SD Save
  time_t now = time(nullptr);
  char dateStr[12], timeStr[10];
  struct tm *tm_ = localtime(&now);
  snprintf(dateStr, sizeof(dateStr), "%04d-%02d-%02d", tm_->tm_year + 1900, tm_->tm_mon + 1, tm_->tm_mday);
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", tm_->tm_hour, tm_->tm_min, tm_->tm_sec);

  char sdPath[96] = {0};
#if HW_SD_CONNECTED
  sdSaveImage(fb->buf, fb->len, SD_IMG_PLANTMAP, 'f', idx, targetX, targetY, now, sdPath);
#endif

  // 4. Handoff to Core 0 for transmission
  if (sysState.getFlutter() == FLUTTER_CONNECTED) {
    StaticJsonDocument<256> meta;
    meta["evt"] = "FRAME_META";
    meta["idx"] = idx;
    meta["total"] = total;
    // Metadata should reflect the logical plant position (without camera offset)
    meta["x"] = targetX;
    meta["y"] = targetY;
    meta["sdPath"] = sdPath;
    String metaStr; serializeJson(meta, metaStr);
    webSocket.sendTXT(clientNum, metaStr);

    // Send binary JPEG payload over the unified control socket
    if (activeClientNum != -1) {
        webSocket.sendBIN(activeClientNum, fb->buf, fb->len);
    } else {
        AgriLog(TAG_CAM, LEVEL_WARN, "Client disconnected; dropping image frame.");
    }
    esp_camera_fb_return(fb);

  } else {
    esp_camera_fb_return(fb);
  }


  AgriLog(TAG_CAM, LEVEL_INFO, "Frame %d: %s %s (%.1f,%.1f) %uB%s", idx, dateStr,
                timeStr, targetX, targetY, fb->len,
                sdPath[0] ? " [SD]" : "");

  return true;
}


  // =========================================================================
  // TODO(Luna): AI Hook — uncomment when ready
  // After esp_camera_fb_get(), before return:
  //   aiProcessFrame(fb->buf, fb->len, sysState.getX(), sysState.getY());
// =========================================================================

void cameraSanityCheck() {
    // If the system has been in an "invalid" state for too long
    static unsigned long lastSuccess = millis();
    camera_fb_t* fb = esp_camera_fb_get();
    if (fb != NULL) {
        lastSuccess = millis();
        esp_camera_fb_return(fb);
    }
    
    if (millis() - lastSuccess > 10000) { 
        AgriLog(TAG_CAM, LEVEL_ERR, "[WATCHDOG] Camera unresponsive for 10s. Attempting reset...");
        esp_camera_deinit();
        delay(100);
        cameraInit(); // Re-init
        lastSuccess = millis();
    }
}

bool sendStreamBIN(const uint8_t *payload, size_t length) {
    if (activeClientNum != -1) {
        return webSocket.sendBIN(activeClientNum, payload, length);
    }
    return false;
}
