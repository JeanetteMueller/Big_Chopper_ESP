
#ifndef WebServer_h
#define WebServer_h

#include "Arduino.h"
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESPAsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "webserver/content/styles.h"
#include "webserver/content/javascript.h"
#include "webserver/baseHtml.h"

#include "webserver/pages/indexHtml.h"
#include "webserver/pages/settingsHtml.h"

class WebServer
{
public:
    enum Page
    {
        indexPage,
        settingsPage
    };

    enum Content
    {
        stylesContent,
        javascriptContent
    };

    int16_t joy1_x = 0;
    int16_t joy1_y = 0;

    int16_t domeRotate = 1500;

    bool bodyArmLeft = false;
    bool bodyArmRight = false;

    WebServer(uint32_t port);
    void start();

private:
    AsyncWebServer *_server;

    String getBaseHtml(String body);
    String getContent(Content content);
    String getPage(Page page, AsyncWebServerRequest *request);

    void apiPostAction(AsyncWebServerRequest *request, uint8_t* data, size_t len, size_t index, size_t total);
    void postAction(AsyncWebServerRequest *request);

    void notFound(AsyncWebServerRequest *request);
};

#endif