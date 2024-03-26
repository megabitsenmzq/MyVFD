#ifndef DateTime_h
#define DateTime_h

#include <Arduino.h>
#include <time.h>

class DateTime {
  private:
    const char *weekDay[7] = {"Sun","Mon","Tue","Wed","Thr","Fri","Sat"};
  public:
    DateTime();
    bool isLoading = true;
    char dateString[10];
    char timeString[10];
    void setupTime();
    void getNewDateTime();
};

#endif