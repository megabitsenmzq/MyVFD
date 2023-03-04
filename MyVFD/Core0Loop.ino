// Core 0 is used for loading the data from modules.

const long modeCycleInterval = 3000;
unsigned long modeCycleTimeStamp = 0;
const int tempModeCycleInterval = 1000*60;
unsigned long tempModeCycleTimeStamp = 0;

void core0Loop() {
  showLoadingAnimation = false;
  switch (currentMode) {
    case ipAddress:
      if (WiFi.status() != WL_CONNECTED) {
        waitForWifi();
      }
      setupModules();
      delay(3000);
      showLoadingAnimation = true;
      while(millis() % 1000 > 5) {
        // Wait for time to align up.
      }
      modeCycleTimeStamp = millis(); 
      currentMode = modeCycle[0];
      break;

    case currentDate:
      dateTime.getNewDateTime();
      showLoadingAnimation = dateTime.isLoading;
      break;

    case currentTime:
      dateTime.getNewDateTime();
      showLoadingAnimation = dateTime.isLoading;
      break;

    case currentTemp:
    case highTemp:
    case lowTemp:
      if (!weather.firstValueLoaded) {
        showLoadingAnimation = weather.isLoading;
      }
      break;
      
    // Temp modes.
    case customText:
    case screenTest:
      if (millis() - tempModeCycleTimeStamp > tempModeCycleInterval) {
        exitTempMode();
      }
      break;

    default: break;
  }
  checkNextMode();
  weather.updateWeather();
}

void waitForWifi() {
  showLoadingAnimation = true;
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.print("OK\n");
  showLoadingAnimation = false;
}

void setupModules() {
  webServer.setupServer();
  webServer.registerCallback(webServerCallback);
  dateTime.setupTime();
}

void webServerCallback(const char* newMode){
  if (newMode == "customText") {
    currentMode = customText;
  } else if (newMode == "screenTest") {
    screenTestTimeStamp = millis();
    screenTestingAnimationIndex = 0;
    currentMode = screenTest;
  } else if (newMode == "reboot") {
    ESP.restart();
  } else {
    exitTempMode();
    return;
  }
  
  // Start temp mode.
  modeCycleTimeStamp = 0; // Stop cycle.
  tempModeCycleTimeStamp = millis();
}

void exitTempMode() {
  currentModeIndex = 0;
  currentMode = modeCycle[currentModeIndex];
  modeCycleTimeStamp = millis(); // Continue cycle.
}

void checkNextMode() {
  if (modeCycleTimeStamp == 0) {
    return; // Should not cycle through modes.
  }

  // Check time.
  if (millis() - modeCycleTimeStamp > modeCycleInterval) {
      modeCycleTimeStamp = millis();
  } else {
    return;
  }

  // Next mode.
  currentModeIndex += 1;
  currentModeIndex = currentModeIndex % (sizeof(modeCycle) / sizeof(DisplayMode));
  currentMode = modeCycle[currentModeIndex];

  showLoadingAnimation = false;
  
  // Serial.print(F("Stack Memory Left: "));
  // Serial.println(uxTaskGetStackHighWaterMark( NULL ));
  // Serial.print(F("Heap Memory Left: "));
  // Serial.println(ESP.getFreeHeap());
}