#include <Arduino.h>
#include <WiFi.h>
#include "src/SevSeg/SevSeg.h"
#include "Bitmap.h"
#include "Secret.h"
#include "WebServer.h"
#include "DateTime.h"
#include "Weather.h"

// LED
#define LED_PIN 2 // On board LED.
#define LED_BRIGHTNESS 64

// SveSeg
SevSeg sevseg;
const byte hardwareConfig = P_TRANSISTORS;
const byte numDigits = 9;
const byte digitPins[] = {15, 16, 18, 21, 12, 22, 27, 25, 32};
const byte segmentPins[] = {14, 33, 26, 13, 19, 17, 4, 23};
const bool resistorsOnSegments = false;
const bool updateWithDelays = false;

// Multi Core
TaskHandle_t Core0Task[1];
TaskHandle_t Core1Task[1];

// Display Mode
enum DisplayMode {ipAddress, currentDate, currentTime, currentTemp, highTemp, lowTemp, customText, screenTest};
DisplayMode modeCycle[] = {currentDate, currentTime, currentTemp, highTemp, lowTemp};
DisplayMode currentMode = ipAddress;
int currentModeIndex = 0;
bool showLoadingAnimation = true;

// Modules
WebServer webServer = WebServer();
DateTime dateTime = DateTime();
Weather weather = Weather();

// Loading Animation
const long loadingAnimtaionInterval = 100;
unsigned long loadingAnimationTimeStamp = 0;
int loadingAnimationIndex = 0;

// Screen test animation.
const int screenTestInterval = 1000;
unsigned long screenTestTimeStamp = 0;
int screenTestingAnimationIndex = 0;

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
  xTaskCreatePinnedToCore(Core0a, "Core0a", 1024*8, NULL, 1, &Core0Task[0], 0); 
  xTaskCreatePinnedToCore(Core1a, "Core1a", 1024*4, NULL, 1, &Core1Task[0], 1); 
}

void loop() {
  vTaskDelete(nullptr); // Remove loop from tasks. Use FreeRTOS tasks instead.
}

void Core0a(void *args) {
  while (1) {
    delay(1); // Wait for watchdog.
    core0Loop();
  }
}

void Core1a(void *args) {
  while (1) {
    core1Loop();
  }
}

