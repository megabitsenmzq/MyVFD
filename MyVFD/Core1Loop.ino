// Core 0 is used for updating the screen.

// Loading Animation
const long loadingAnimtaionInterval = 100;
unsigned long loadingAnimationTimeStamp = 0;
int loadingAnimationIndex = 0;

void core1Loop() {
  sevseg.refreshDisplay();

  led.setState(dateTime.isLoading || weather.isLoading);
  led.pwmLoop();

  if(showLoadingAnimation) {
    // Load animation.
    uint8_t segments[9];
    for (int i=0; i<9; i++) {
      segments[i] = loadingAnimation[loadingAnimationIndex % loadingAnimationLenth];
    }
    sevseg.setSegments(segments);

    // Wait for next.
    if (millis() - loadingAnimationTimeStamp > loadingAnimtaionInterval) {
      loadingAnimationTimeStamp = millis();
      loadingAnimationIndex += 1;
    }
    return;
  } else {
    loadingAnimationIndex = 0;
  }

  switch (currentMode) {
    case ipAddress:
    sevseg.setChars(WiFi.localIP().toString().c_str());
    break;

    case currentDate:
    sevseg.setChars(dateTime.dateString);
    break;

    case currentTime:
    sevseg.setChars(dateTime.timeString);
    break;

    case currentWeather:
    if (weather.isError) {
      sevseg.setChars("OPW ERROR");
    } else {
      char buffer[10];
      sprintf(buffer, "TEMP%5.1f*", weather.temp);
      sevseg.setChars(buffer);
    }
    break;

    default:
    sevseg.blank();
    break;
  }
}