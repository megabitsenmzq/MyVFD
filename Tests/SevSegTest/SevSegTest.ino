#include <SevSeg.h>

// SveSeg
SevSeg sevseg;
const byte hardwareConfig = P_TRANSISTORS;
const byte numDigits = 9;
const byte digitPins[] = {15, 16, 18, 21, 12, 22, 27, 25, 32};
const byte segmentPins[] = {14, 33, 26, 13, 19, 17, 4, 23};

void setup() {
  Serial.begin(115200);

  // SevSeg
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(100);

  sevseg.setChars("a.b.c");
}

void loop() {
  sevseg.refreshDisplay();
}

