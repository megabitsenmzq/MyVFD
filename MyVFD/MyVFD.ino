#include <WiFi.h>
#include "src/SevSeg/SevSeg.h"
#include "Bitmap.h"
#include "Secret.h"
#include "LED.h"
#include "DateTime.h"

// Wifi
extern char* wifiSSID;
extern char* wifiPassword;

// SveSeg
SevSeg sevseg;
const byte hardwareConfig = P_TRANSISTORS;
const byte numDigits = 9;
const byte digitPins[] = {15, 16, 18, 21, 12, 22, 27, 25, 32};
const byte segmentPins[] = {14, 33, 26, 13, 19, 17, 4, 23};

// Multi Core
TaskHandle_t Core0Task[1];
TaskHandle_t Core1Task[1];

// Display Mode
enum DisplayMode {ipAddress, currentDate, currentTime, blank};
DisplayMode modecycle[] = {currentDate, currentTime};
DisplayMode currentMode = ipAddress;
int currentModeIndex = 0;
bool isLoading = true;

// Modules
LED led = LED();
DateTime dateTime = DateTime();

void setup() {
  Serial.begin(115200);

  // WiFi
  WiFi.begin(wifiSSID, wifiPassword);

  // SevSeg
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(100);

  // Multi Core
  xTaskCreatePinnedToCore(Core0a, "Core0a", 4096, NULL, 1, &Core0Task[0], 0); 
  xTaskCreatePinnedToCore(Core1a, "Core1a", 4096, NULL, 2, &Core1Task[0], 1); 
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

