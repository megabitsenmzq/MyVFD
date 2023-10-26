#include "core1Loop.h"

// Core 1 is used for updating the screen.

void core1Loop() {
  sevseg.refreshDisplay();

  bool ledState = dateTime.isLoading || weather.isLoading;
  ledcWrite(0, ledState ? LED_BRIGHTNESS : 0);

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

  // Normal display modes.
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
      
    case currentTemp:
    case highTemp:
    case lowTemp:
      if (weather.isError) {
        sevseg.setChars("OPW ERROR");
      } else {
        char buffer[10];
        switch(currentMode) {
          case currentTemp:
            sprintf(buffer, "TEMP%5.1f*", weather.currentTemp);
            break;
          case highTemp:
            sprintf(buffer, "HIGH%5.1f*", weather.maxTemp);
            break;
          case lowTemp:
            sprintf(buffer, "LOW %5.1f*", weather.minTemp);
            break;
          default: break;
        }
        sevseg.setChars(buffer);
      }
      break;
      
    // Temp modes.
    case randomNumber:
    randomAnimator.updateAnimation();
      sevseg.setChars(randomAnimator.currentNumberStringWithAnimation.c_str());
      break;

    case customText:
      sevseg.setChars(webServer.customText.c_str());
      break;
    
    case screenTest:
      sevseg.setSegments(screenTestingAnimation[screenTestingAnimationIndex % screenTestingAnimationLenth]);
      if (millis() - screenTestTimeStamp > screenTestInterval) {
        screenTestTimeStamp = millis();
        screenTestingAnimationIndex += 1;
      }
      break;
    default:
    sevseg.blank();
    break;
  }
}