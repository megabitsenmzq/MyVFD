#ifndef Weather_h
#define Weather_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

class Weather {
  private:
    const String endpoint = F("http://api.openweathermap.org/data/2.5/onecall?");
    const long weatherUpdateInterval = 1000*60*30;
    const long weatherErrorUpdateInterval = 1000*60;
    unsigned long weatherUpdateTimeStamp = 0;
    String apiURL();
  public:
    Weather();
    bool firstValueLoaded = false;
    bool isLoading = true;
    bool isError = false;
    double temp = -1;
    String skycon = "";
    void updateWeather();
};

#endif