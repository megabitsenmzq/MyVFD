#ifndef PUBLIC_H
#define PUBLIC_H

#include <Arduino.h>
#include <SevSeg.h>
#include <bitmap.h>
#include <secret.h>
#include "components/WebServer.h"
#include "components/DateTime.h"
#include "components/Weather.h"
#include "components/Random.h"

// LED
#define LED_PIN 2 // On board LED.
#define LED_BRIGHTNESS 64

// SveSeg
extern SevSeg sevseg;
const byte hardwareConfig = P_TRANSISTORS;
const byte numDigits = 9;
const byte digitPins[] = {15, 16, 18, 21, 12, 22, 27, 25, 32};
const byte segmentPins[] = {14, 33, 26, 13, 19, 17, 4, 23};
const bool resistorsOnSegments = false;
const bool updateWithDelays = false;

// Display Mode
enum DisplayMode {
    ipAddress, 
    currentDate, 
    currentTime, 
    currentTemp, 
    highTemp, 
    lowTemp, 
    customText, 
    randomNumber, 
    screenTest
};
extern DisplayMode modeCycle[5];
extern DisplayMode currentMode;
extern uint8_t currentModeIndex;
extern bool showLoadingAnimation;

// Modules
extern WebServer webServer;
extern DateTime dateTime;
extern Weather weather;
extern Random randomAnimator;

// Loading Animation
const long loadingAnimtaionInterval = 100;
extern unsigned long loadingAnimationTimeStamp;
extern uint8_t loadingAnimationIndex;

// Screen test animation.
const int screenTestInterval = 1000;
extern unsigned long screenTestTimeStamp;
extern uint8_t screenTestingAnimationIndex;

#endif
