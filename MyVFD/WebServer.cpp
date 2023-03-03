#include "WebServer.h"

AsyncWebServer server(80);

const char* customTextInput = "customTextInput";

const char style[] = R"(
  <style>
    body {
        background: #121617;
        color: #85e7c1;
    }
    input[type=text] {
        background-color: #000000; 
        border: 2px solid #85e7c1;
        border-radius: 5px;
        color: #85e7c1;
    }
    input[type=button], input[type=submit], input[type=reset] {
        background-color: #04AA6D;
        border: none;
        border-radius: 5px;
        color: white;
    }
  </style>
)";

const char index_html[] = R"(
  <!DOCTYPE HTML>
  <html>
  <head>
  <title>MyVFD</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  %Style%
  </head>
  <body>
  <h1>MyVFD</h1>
  <form action="/get">
    <h3>Custom Text: </h3>
    <input type="text" name="customTextInput">
    <input type="submit" value="Submit">
    <br/>
    <h4>Text will display for 1 minute.</h4>
  </form>
  </body>
  </html>
)";

const char success_html[] = R"(
  <!DOCTYPE HTML>
  <html>
  <head>
  <title>MyVFD</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  %Style%
  </head>
  <body>
  <h1>MyVFD</h1>
  <form action="/get">
    <h4>Text Sended: %newText%</h4>
  </body>
  </html>
)";
    
WebServer::WebServer() {
  
}

void WebServer::setupServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String htmlWithStyles = String(index_html);
    htmlWithStyles.replace("%Style%", String(style));
    request->send_P(200, "text/html", htmlWithStyles.c_str());
  });

  server.on("/get", HTTP_GET, [this] (AsyncWebServerRequest *request) {
    if (request->hasParam(customTextInput)) {
      customText = request->getParam(customTextInput)->value();
    } else {
      customText = "";
    }
    String htmlWithStyles = String(success_html);
    htmlWithStyles.replace("%Style%", String(style));
    htmlWithStyles.replace("%newText%", customText);
    request->send(200, "text/html", htmlWithStyles.c_str());
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Not found");
  });

  server.begin();
}
