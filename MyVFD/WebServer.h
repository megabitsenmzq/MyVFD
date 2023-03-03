#ifndef WebServer_h
#define WebServer_h

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>

class WebServer {
  private:
  public:
    WebServer();
    String customText = "";
    void setupServer();
};

#endif