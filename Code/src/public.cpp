#include "public.h"

// SveSeg
SevSeg sevseg;

// Display Mode
DisplayMode modeCycle[5] = { currentDate, currentTime, currentTemp, highTemp, lowTemp };
DisplayMode currentMode = ipAddress;
uint8_t currentModeIndex = 0;
bool showLoadingAnimation = true;

// Modules
WebServer webServer = WebServer();
DateTime dateTime = DateTime();
Weather weather = Weather();
Random randomAnimator = Random();

// Loading Animation
unsigned long loadingAnimationTimeStamp = 0;
uint8_t loadingAnimationIndex = 0;

// Screen test animation.
unsigned long screenTestTimeStamp = 0;
uint8_t screenTestingAnimationIndex = 0;