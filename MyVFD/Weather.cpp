#include "Weather.h"
#include "Secret.h"

#define USE_METRIC 1

HTTPClient http;

Weather::Weather() {
  String url = apiURL();
  http.setTimeout(2000);
  http.begin(url);
}

void Weather::updateWeather() {
  const long intervalToUse = isError ? weatherErrorUpdateInterval : weatherUpdateInterval;
  if (millis() - weatherUpdateTimeStamp > intervalToUse || weatherUpdateTimeStamp == 0) {
    weatherUpdateTimeStamp = millis();

    isLoading = true;
    isError = false;

    int httpStateCode = http.GET();
    if (httpStateCode > 0) { // Make new API call.
      String json = http.getString();
      Serial.print(F("Weather::updateWeather(), Json string: "));
      Serial.println(json);
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, json);
      
      if (error) {
        Serial.print(F("Weather::updateWeather(), Deserialize json failed: "));
        Serial.println(error.f_str());
        isError = true;
      } else {
        const int returnCode = doc["cod"];
        if (returnCode == 200) {
          const char* main = doc["weather"][0]["main"];
          skycon = String(main);
          currentTemp = doc["main"]["temp"];
          maxTemp = doc["main"]["temp_max"];
          minTemp = doc["main"]["temp_min"];
        } else {
          isError = true;
        }
      }
    } else {
      isError = true;
      Serial.print(F("Weather::updateWeather(), HTTP error: "));
      Serial.println(httpStateCode);
    }
    firstValueLoaded = true;
    isLoading = false;
  }
}

String Weather::apiURL() {
  return endpoint + "appid=" + String(OPEN_WEATHER_KEY) + "&lat=" + String(LATITUDE) + "&lon=" + String(LONGITUDE) + (USE_METRIC ? "&units=metric" : "");
}