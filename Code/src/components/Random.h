#ifndef RANDOM_H
#define RANDOM_H

#include <Arduino.h>

class Random {
  private:
    const int animationInterval = 50;
    const int numberUpdateInterval = 1000;
    unsigned long animationTimeStamp = 0;
    unsigned long numberUpdateTimeStamp = 0;
    uint8_t animationIndex = 0;
    int randomNumber = 0;
  public:
    Random();
    String currentNumberStringWithAnimation = "";
    void setupRandomGenerator();
    void updateAnimation();
};

#endif