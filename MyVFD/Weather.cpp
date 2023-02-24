#include "Weather.h"
#include "Secret.h"

HTTPClient http;

Weather::Weather() {
  String url = apiURL();
  // Serial.println(url);
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
      Serial.println(json);
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, json);

      if (error) {
        Serial.print(F("Weather::updateWeather(), Deserialize json failed: "));
        Serial.println(error.f_str());
        isError = true;
      } else {
        const char* main = doc["current"]["weather"][0]["main"];
        skycon = String(main);
        // Serial.println(skycon);
        if (skycon == "") {
          // Skycon is empty;
          isError = true;
        } else {
          temp = doc["current"]["temp"];
          // Serial.println(temp);
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
  return endpoint + "appid=" + String(openWeatherKey) + "&lat=" + String(latitude) + "&lon=" + String(longitude) + F("&units=metric&exclude=minutely,hourly,daily,alerts");
}