#ifndef WebServer_h
#define WebServer_h

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>

class WebServer {
  using WebServerCallback = void (*)(const char*);
  private:
    WebServerCallback callback;
  public:
    String customText = "";

    WebServer();
    void setupServer();
    void registerCallback(WebServerCallback newCallback);
};

#endif