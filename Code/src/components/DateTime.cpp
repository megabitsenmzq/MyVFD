#include "DateTime.h"

DateTime::DateTime() {

}

void DateTime::setupTime() {
  configTime(timeZone, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp", "pool.ntp.org");
}

void DateTime::getNewDateTime() {
  time_t timeItem;
  struct tm *timeComponent;

  timeItem = time(NULL);
  timeComponent = localtime(&timeItem);
  if (timeItem > 1234567890) { // Date updated.
    isLoading = false;
  }
  sprintf(dateString, "%02d-%02d-%s", timeComponent->tm_mon+1, timeComponent->tm_mday, weekDay[timeComponent->tm_wday]);
  if (millis() % 1000 < 500) {
    sprintf(timeString, "%02d-%02d  %02d", timeComponent->tm_hour, timeComponent->tm_min, timeComponent->tm_sec);
  } else {
    sprintf(timeString, "%02d-%02d--%02d", timeComponent->tm_hour, timeComponent->tm_min, timeComponent->tm_sec);
  }
}