
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

    int16_t drive_x = 0;
    int16_t drive_y = 0;

    bool bodyArmLeft = false;
    bool bodyArmRight = false;
    bool utilityArm = false;
    bool utilityArmGripper = false;

    int16_t domeRotate = 1500;
    double domeArmsLeftExtend = 0;
    double domeArmsRightExtend = 0;
    double domeArmsLeftRotate = 0;
    double domeArmsRightRotate = 0;

    double domePeriscopeLift = 0;
    double domePeriscopeRotate = 0;


    WebServer(uint32_t port);
    void start();

    

private:
    AsyncWebServer *_server;
    String html;

    void getBaseHtml(const String & body, String &target);
    String getPage(Page page, AsyncWebServerRequest *request);

    void apiPostAction(AsyncWebServerRequest *request, uint8_t* data, size_t len, size_t index, size_t total);
    void postAction(AsyncWebServerRequest *request);

    void notFound(AsyncWebServerRequest *request);
    std::string random_string(size_t length);
};

#endif