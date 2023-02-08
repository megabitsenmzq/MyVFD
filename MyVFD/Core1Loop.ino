// Core 0 is used for updating the screen.

// Loading Animation
const long loadingAnimtaionStep = 100;
unsigned long loadingAnimationTimeMark = 0;
int loadingAnimationIndex = 0;

void core1Loop() {
  sevseg.refreshDisplay();

  if(isLoading) {
    // Load animation.
    uint8_t segments[9];
    for (int i=0; i<9; i++) {
      segments[i] = loadingAnimation[loadingAnimationIndex % loadingAnimationLenth];
    }
    sevseg.setSegments(segments);

    // Wait for next.
    if (millis() - loadingAnimationTimeMark > loadingAnimtaionStep) {
      loadingAnimationTimeMark = millis();
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

    default:
    sevseg.blank();
    break;
  }
}