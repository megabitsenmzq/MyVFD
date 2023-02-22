#include "LED.h"

#define LED_PIN 2 // ESP32 on board LED.
#define PWM_RATE 3

LED::LED() {
  pinMode(LED_PIN, OUTPUT);
}

void LED::setState(bool newState) {
  state = newState;
}

void LED::pwmLoop() {
  if (state) {
    if (millis() % PWM_RATE == 0) {
      digitalWrite(LED_PIN, true);
    } else {
      digitalWrite(LED_PIN, false);
    }
  } else {
    digitalWrite(LED_PIN, false);
  }
}