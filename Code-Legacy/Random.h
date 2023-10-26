#ifndef Random_h
#define Random_h

#include <Arduino.h>

class Random {
  private:
    const int animationInterval = 50;
    const int numberUpdateInterval = 1000;
    unsigned long animationTimeStamp = 0;
    unsigned long numberUpdateTimeStamp = 0;
    int animationIndex = 0;
    int randomNumber = 0;
  public:
    Random();
    String currentNumberStringWithAnimation = "";
    void setupRandomGenerator();
    void updateAnimation();
};

#endif