#ifndef Weather_h
#define Weather_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <secret.h>

#define USE_METRIC 1

class Weather {
  private:
    const String endpoint = F("https://api.openweathermap.org/data/2.5/weather?");
    const long weatherUpdateInterval = 1000*60*30;
    const long weatherErrorUpdateInterval = 1000*60;
    unsigned long weatherUpdateTimeStamp = 0;
    String apiURL();
  public:
    Weather();
    bool firstValueLoaded = false;
    bool isLoading = true;
    bool isError = false;
    String skycon = "";
    double maxTemp = -1;
    double minTemp = -1;
    double currentTemp = -1;
    void updateWeather();
};

#endif