#include "WebServer.h"

WebServer::WebServer(uint32_t port)
{
    _server = new AsyncWebServer(port);
}

void WebServer::start()
{
    _server->on(
        "/api/post.json", HTTP_POST, [&](AsyncWebServerRequest *request) {}, nullptr, [&](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        { apiPostAction(request, data, len, index, total); });

    // _server->on("/", HTTP_POST, [&](AsyncWebServerRequest *request)
    //             { postAction(request); });

    _server->on("/styles.css", HTTP_GET, [&](AsyncWebServerRequest *request)
                { 
                    AsyncResponseStream *response = request->beginResponseStream("text/css");
                    response->print(styles);
                    request->send(response); });

    _server->on("/javascript.js", HTTP_GET, [&](AsyncWebServerRequest *request)
                {
                    AsyncResponseStream *response = request->beginResponseStream("text/javascript");
                    response->print(javascript_1);
                    response->print(javascript_2);
                    response->print(javascript_3);

                    request->send(response); });

    _server->on("/joystick.js", HTTP_GET, [&](AsyncWebServerRequest *request)
                {
                    AsyncResponseStream *response = request->beginResponseStream("text/javascript");
                    response->print(javascript_joystick);
                    request->send(response); });

    _server->on("/index.html", HTTP_GET, [&](AsyncWebServerRequest *request)
                {
                    AsyncResponseStream *response = request->beginResponseStream("text/html");
                    response->print(getPage(indexPage, request));
                    request->send(response); });

    _server->on("/settings.html", HTTP_GET, [&](AsyncWebServerRequest *request)
                { request->send(200, "text/html", getPage(settingsPage, request)); });

    _server->onNotFound([&](AsyncWebServerRequest *request)
                        { notFound(request); });

    _server->begin();
}

void WebServer::apiPostAction(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    Serial.println("apiPostAction!");

    JsonDocument json;
    deserializeJson(json, data, len);

    joy1_x = json["joy1"]["x"];
    joy1_y = json["joy1"]["y"];
    Serial.print("post: joy1: ");
    Serial.print(joy1_x);
    Serial.print(" - ");
    Serial.println(joy1_y);

    bodyArmLeft = json["body"]["arms"]["left"];
    bodyArmRight = json["body"]["arms"]["right"];

    domeRotate = json["dome"]["rotate"];
    Serial.print("domeRotate: ");
    Serial.println(domeRotate);

    domeArmsLeftExtend = json["dome"]["arms"]["left"]["extend"];
    domeArmsRightExtend = json["dome"]["arms"]["right"]["extend"];
    domeArmsLeftRotate = json["dome"]["arms"]["left"]["rotate"];
    domeArmsRightRotate = json["dome"]["arms"]["right"]["rotate"];

    Serial.print("domeLeftArm extend: ");
    Serial.print(domeArmsLeftExtend);
    Serial.print(" rotate: ");
    Serial.println(domeArmsLeftRotate);

    Serial.print("domeRightArm extend: ");
    Serial.print(domeArmsRightExtend);
    Serial.print(" rotate: ");
    Serial.println(domeArmsRightRotate);

    domePeriscopeLift = json["dome"]["periscope"]["lift"];
    domePeriscopeRotate = json["dome"]["periscope"]["rotate"];

    Serial.print("Periscope lift: ");
    Serial.print(domePeriscopeLift);
    Serial.print(" rotate: ");
    Serial.println(domePeriscopeRotate);

    String result;
    serializeJson(json, result);

    request->send(200, "application/json", result);
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
        getBaseHtml(indexHtml, html);
        break;
    case settingsPage:
        getBaseHtml(settingsHtml, html);
        break;
    }
    return html;
}

void WebServer::notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

void WebServer::getBaseHtml(const String &body, String &target)
{
    target = baseHtml;
    target.replace("###BODY###", body);
    target.replace("###RANDOM###", random_string(10).c_str());
}

std::string WebServer::random_string(size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}