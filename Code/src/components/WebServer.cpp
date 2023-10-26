#include "WebServer.h"

AsyncWebServer server(80);
    
WebServer::WebServer() {
  
}

void WebServer::registerCallback(WebServerCallback newCallback){
    callback = newCallback;
}

void WebServer::setupServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String htmlWithStyles = String(index_html);
    htmlWithStyles.replace("%Style%", String(style));
    request->send_P(200, "text/html", htmlWithStyles.c_str());
  });

  server.on("/get", HTTP_GET, [this] (AsyncWebServerRequest *request) {
    if (request->hasParam("customTextInput")) {
      customText = request->getParam("customTextInput")->value();
      if (customText == "") {
        callback("");
      } else {
        callback("customText");
      }
    }

    if (request->hasParam("random")) {    
      callback("random");
    }

    if (request->hasParam("screenTest")) {    
      callback("screenTest");
    }

    if (request->hasParam("clearState")) {
      callback("");
    }

    if (request->hasParam("reboot")) {
      request->redirect("/");
      delay(1000);
      callback("reboot");
      return;
    }

    request->redirect("/");
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Not found");
  });

  server.begin();
}
