#ifndef DATETIME_H
#define DATETIME_H

#include <Arduino.h>
#include <time.h>

class DateTime {
  private:
    const char *weekDay[7] = {"Sun","Mon","Tue","Wed","Thr","Fri","Sat"};
    const int timeZone = 3600*9; // JST
  public:
    DateTime();
    bool isLoading = true;
    char dateString[10];
    char timeString[10];
    void setupTime();
    void getNewDateTime();
};

#endif