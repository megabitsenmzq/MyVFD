#include "WebServer.h"

AsyncWebServer server(80);

const char style[] = R"(
  <style>
    body {
        background: #121617;
        color: #85e7c1;
    }
    a:link {
	    color: #04AA6D;
	  }
	  a:visited {
	    color: #04AA6D;
	  }
	  a:hover {
	    color: #85e7c1;
	  }
    a:active {
	    color: #04AA6D;
	  }
    input[type=text] {
        background-color: #000000; 
        border: 2px solid #85e7c1;
        border-radius: 5px;
        color: #85e7c1;
    }
    input[type=button], input[type=submit], input[type=reset], button {
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
    <br/><br/>
  </form>
  <form action="/get">
    <h3>Screen Test: </h3>
    <button type="submit" name="screenTest" value="1">Test Now</button>
    <br/><br/>
  </form>
  <form action="/get">
    <h3>Actions: </h3>
    <button type="submit" name="backToNormal" value="1">Back to Normal Mode</button>
    <button type="submit" name="reset" value="1">Reset</button>
    <br/><br/>
  </form>
  <h5>All contents set here will be displayed for 1 minute.</h5>
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
    <h4>%message%</h4>
    <br/>
    <a href="/">Return to Home Page</a>
  </body>
  </html>
)";
    
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

    if (request->hasParam("screenTest")) {    
      callback("screenTest");
      message = "Test started.";
    }

    if (request->hasParam("backToNormal")) {
      callback("");
      message = "Action Sended.";
    }
    if (request->hasParam("reset")) {
      callback("reset");
      message = "Action Sended.";
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
