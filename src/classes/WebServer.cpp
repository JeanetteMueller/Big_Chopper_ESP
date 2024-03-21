#include "WebServer.h"

WebServer::WebServer(uint32_t port)
{
    _server = new AsyncWebServer(port);
}

void WebServer::setup()
{
    _server->on("/", HTTP_POST, [&](AsyncWebServerRequest *request)
                { postAction(request); });

    _server->on("/", HTTP_GET, [&](AsyncWebServerRequest *request)
                { request->send(200, "text/html", getPage(indexPage, request)); });

    _server->on("/styles.css", HTTP_GET, [&](AsyncWebServerRequest *request)
                { request->send(200, "text/css", getContent(stylesContent)); });

    _server->on("/javascript.js", HTTP_GET, [&](AsyncWebServerRequest *request)
                { request->send(200, "text/text", getContent(javascriptContent)); });

    _server->on("/index.html", HTTP_GET, [&](AsyncWebServerRequest *request)
                { request->send(200, "text/html", getPage(indexPage, request)); });

    _server->on("/settings.html", HTTP_GET, [&](AsyncWebServerRequest *request)
                { request->send(200, "text/html", getPage(settingsPage, request)); });

    _server->onNotFound([&](AsyncWebServerRequest *request)
                        { notFound(request); });

    _server->begin();
}

void WebServer::postAction(AsyncWebServerRequest *request)
{
    Serial.println("ACTION!");

    int params = request->params();
    for (int i = 0; i < params; i++)
    {
        AsyncWebParameter *p = request->getParam(i);
        Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());

        if (p->name() == "whatever")
        {
        }
    }
    request->send(200, "text/html", getPage(indexPage, request));
}

String WebServer::getPage(Page page, AsyncWebServerRequest *request)
{
    if (request->hasParam("whatever"))
    {
        String action = request->getParam("whatever")->value();

        if (action == "1")
        {
        }
    }

    switch (page)
    {
    case indexPage:
        return getBaseHtml(indexHtml);
    case settingsPage:
        return getBaseHtml(settingsHtml);
    }
    return "";
}

String WebServer::getContent(Content content)
{
    switch (content)
    {
    case stylesContent:
        return styles;
    case javascriptContent:
        return javascript;
    }
    return "";
}

void WebServer::notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

String WebServer::getBaseHtml(String body)
{
    String html = baseHtml;
    html.replace("###BODY###", body);
    return html;
}