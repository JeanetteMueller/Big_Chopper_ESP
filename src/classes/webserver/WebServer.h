
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

#include "content/styles.h"
#include "content/javascript.h"
#include "baseHtml.h"

#include "pages/indexHtml.h"
#include "pages/settingsHtml.h"

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

    WebServer(uint32_t port);
    void setup();

private:
    AsyncWebServer *_server;

    String getBaseHtml(String body);
    String getContent(Content content);
    String getPage(Page page, AsyncWebServerRequest *request);
    void postAction(AsyncWebServerRequest *request);
    void notFound(AsyncWebServerRequest *request);
};

#endif