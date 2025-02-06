#include "WebServerHandler.h"
#include <LittleFS.h> // Untuk SPIFFS

WebServerHandler::WebServerHandler(AsyncWebServer &server) : server(server) {}

void WebServerHandler::serveFiles()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/html/index.html", "text/html"); });

    server.on("/css/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/css/style.css", "text/css"); });

    // Sajikan file JavaScript
    server.on("/js/main.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/js/main.js", "application/javascript"); });

    server.on("/js/shared.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/js/shared.js", "application/javascript"); });

    server.on("/js/chart.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/js/chart.js", "application/javascript"); });
}
