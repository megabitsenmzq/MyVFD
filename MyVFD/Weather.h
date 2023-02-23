#ifndef Weather_h
#define Weather_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

class Weather {
  private:
    HTTPClient http;
    String apiURL();
  public:
    Weather();
    bool isLoading = true;
    void updateWeather();
};

#endif