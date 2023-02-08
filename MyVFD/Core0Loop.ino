const long modeCycleStep = 3000;
unsigned long modeCycleTimeMark = 0;

void core0Loop() {
  switch (currentMode) {
    case ipAddress:
      if (WiFi.status() != WL_CONNECTED) {
        waitForWifi();
      }
      setupModules();
      delay(3000);
      while(millis() % 1000 > 5) {
        // Wait for time to align.
      }
      modeCycleTimeMark = millis(); 
      currentMode = modecycle[0];
      break;
    case currentDate:
      dateTime.getNewDateTime();
      isLoading = dateTime.isLoading;
      break;
    case currentTime:
      dateTime.getNewDateTime();
      isLoading = dateTime.isLoading;
      break;
    default: break;
  }
  checkNextMode();
}

void waitForWifi() {
  isLoading = true;
  Serial.print("Connecting to ");
  Serial.print(wifiSSID);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.print("OK\n");
  isLoading = false;
}

void setupModules() {
  dateTime.setupTime();
}

void checkNextMode() {
  if (modeCycleTimeMark == 0) {
    return;
  }
  if (millis() - modeCycleTimeMark > modeCycleStep) {
      modeCycleTimeMark = millis();
  } else {
    return;
  }
  currentModeIndex += 1;
  if (currentModeIndex >= (sizeof(modecycle) / sizeof(DisplayMode))) {
    currentModeIndex = 0;
  }
  currentMode = modecycle[currentModeIndex];
  isLoading = false;
  Serial.println(currentModeIndex);
  Serial.println((sizeof(modecycle) / sizeof(DisplayMode)));
}