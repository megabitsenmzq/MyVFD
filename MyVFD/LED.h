#ifndef LED_h
#define LED_h

#include <Arduino.h>

class LED {
  private:
    bool state = false;
  public:
    LED();
    void setState(bool newState);
    void pwmLoop();
};

#endif