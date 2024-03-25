#include "core0Loop.h"
#include "core1Loop.h"
#include <WiFi.h>

// Multi Core
TaskHandle_t Core0Task[1];
TaskHandle_t Core1Task[1];

void core0a(void *args) {
  while (1) {
    delay(1); // Wait for watchdog.
    core0Loop();
  }
}

void core1a(void *args) {
  while (1) {
    core1Loop();
  }
}

void setup() {
  Serial.begin(115200);

  // LED
  ledcSetup(0, 4096, 8);
  ledcAttachPin(LED_PIN, 0);

  // WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // SevSeg
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays);
  sevseg.setBrightness(120);

  // Multi Core
  xTaskCreatePinnedToCore(core0a, "Core0a", 1024*8, NULL, 1, &Core0Task[0], 0);
  xTaskCreatePinnedToCore(core1a, "Core1a", 1024*4, NULL, 1, &Core1Task[0], 1);

  // Filament Power Signal
  pinMode(5, OUTPUT);
  analogWrite(5, 128);
}

void loop() {
  vTaskDelete(nullptr); // Remove loop from tasks. Use FreeRTOS tasks instead.
}

