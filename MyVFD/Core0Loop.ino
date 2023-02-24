// Core 0 is used for loading the data from modules.

const long modeCycleInterval = 3000;
unsigned long modeCycleTimeStamp = 0;

void core0Loop() {
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
      currentMode = modecycle[0];
      break;

    case currentDate:
      dateTime.getNewDateTime();
      showLoadingAnimation = dateTime.isLoading;
      break;

    case currentTime:
      dateTime.getNewDateTime();
      showLoadingAnimation = dateTime.isLoading;
      break;

    case currentWeather:
      if (weather.firstValueLoaded) {
        showLoadingAnimation = false;
      } else {
        showLoadingAnimation = weather.isLoading;
      }
      weather.updateWeather();
      break;
    default: break;
  }
  checkNextMode();
}

void waitForWifi() {
  showLoadingAnimation = true;
  Serial.print("Connecting to ");
  Serial.print(wifiSSID);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.print("OK\n");
  showLoadingAnimation = false;
}

void setupModules() {
  dateTime.setupTime();
}

void checkNextMode() {
  if (modeCycleTimeStamp == 0) {
    return; // WiFi setup not finished.
  }

  // Check time.
  if (millis() - modeCycleTimeStamp > modeCycleInterval) {
      modeCycleTimeStamp = millis();
  } else {
    return;
  }

  // Next mode.
  currentModeIndex += 1;
  currentModeIndex = currentModeIndex % (sizeof(modecycle) / sizeof(DisplayMode));
  currentMode = modecycle[currentModeIndex];

  showLoadingAnimation = false;
}