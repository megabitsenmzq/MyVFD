#include "Weather.h"
#include "Secret.h"

const String endpoint = "http://api.openweathermap.org/data/2.5/onecall?";
const long weatherUpdateInterval = 1000*60*10;
unsigned long weatherUpdateTimeStamp = 0;

Weather::Weather() {
  
}

void Weather::updateWeather() {
  if (millis() - weatherUpdateTimeStamp > weatherUpdateInterval) {
      weatherUpdateTimeStamp = millis();
      http.begin(apiURL());
      isLoading = true;
  }
}

String Weather::apiURL() {
  return endpoint + "appid=" + String(openWeatherKey) + "lat=" + String(latitude) + "&" + "lon=" + String(longitude);
}