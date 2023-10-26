#include "WString.h"
#include "esp32-hal.h"
#include "Random.h"

Random::Random() {

}

void Random::setupRandomGenerator() {
  animationTimeStamp = millis();
  numberUpdateTimeStamp = millis();
  animationIndex = 0;
  currentNumberStringWithAnimation = String(random(1000000000));
  randomNumber = esp_random() / 10;
}

void Random::updateAnimation() {
  if (millis() - animationTimeStamp > animationInterval) {
    animationTimeStamp = millis();
    String newString = String(randomNumber);
    for (int i=animationIndex; i<9; i++) {
      char randomDigit = *const_cast<char*>(String(random(10)).c_str());
      newString.setCharAt(i,randomDigit);
    }
    currentNumberStringWithAnimation = newString;
  }

  if (millis() - numberUpdateTimeStamp > numberUpdateInterval) {
    numberUpdateTimeStamp = millis();
    if (animationIndex < 9) {
      animationIndex += 1;
    }
  }
}