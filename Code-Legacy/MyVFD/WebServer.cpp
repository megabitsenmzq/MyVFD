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
    String message = "Unknown action.";
    if (request->hasParam("customTextInput")) {
      customText = request->getParam("customTextInput")->value();
      if (customText == "") {
        callback("");
        message = "Text cleared.";
      } else {
        callback("customText");
        message = "Text Sended: " + customText;
      }
    }

    if (request->hasParam("random")) {    
      callback("random");
      message = "Random number generator started.";
    }

    if (request->hasParam("screenTest")) {    
      callback("screenTest");
      message = "Test started.";
    }

    if (request->hasParam("clearState")) {
      callback("");
      message = "Action Sended.";
    }

    if (request->hasParam("reboot")) {
      message = "Rebooting...";
      String htmlWithStyles = String(success_html);
      htmlWithStyles.replace("%Style%", String(style));
      htmlWithStyles.replace("%message%", message);
      request->send(200, "text/html", htmlWithStyles.c_str());
      delay(1000);
      callback("reboot");
      return;
    }

    String htmlWithStyles = String(success_html);
    htmlWithStyles.replace("%Style%", String(style));
    htmlWithStyles.replace("%message%", message);
    request->send(200, "text/html", htmlWithStyles.c_str());
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Not found");
  });

  server.begin();
}
