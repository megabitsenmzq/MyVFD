#ifndef WebServer_h
#define WebServer_h

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>

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
    <h3>Random Number: </h3>
    <button type="submit" name="random" value="1">Start</button>
    <br/><br/>
  </form>
  <form action="/get">
    <h3>Screen Test: </h3>
    <button type="submit" name="screenTest" value="1">Test Now</button>
    <br/><br/>
  </form>
  <form action="/get">
    <h3>Actions: </h3>
    <button type="submit" name="clearState" value="1">Clear State</button>
    <button type="submit" name="reboot" value="1">Reboot</button>
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
  <META http-equiv="Refresh" content="3;URL=/">
  %Style%
  </head>
  <body>
  <h1>MyVFD</h1>
  <h4>%message%</h4>
  <br/>
  <a href="/">Return to Home Page</a>
  </body>
  </html>
)";

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