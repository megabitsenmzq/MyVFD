#include "WebServer.h"

AsyncWebServer server(80);

const char* customTextInput = "customTextInput";

const char index_html[] = R"(
  <!DOCTYPE HTML><html><head>
    <title>MyVFD</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    </head><body>
    <form action="/get">
      Custom Text: <input type="text" name="customTextInput">
      <input type="submit" value="Submit">
    </form>
  </body></html>
)";
    
WebServer::WebServer() {
  
}

void WebServer::setupServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [this] (AsyncWebServerRequest *request) {
    if (request->hasParam(customTextInput)) {
      customText = request->getParam(customTextInput)->value();
    } else {
      customText = "";
    }
    request->send(200, "text/html", "New Value Sended" + customText + "<br><a href=\"/\">Return</a>");
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Not found");
  });

  server.begin();
}
