#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <ESPAsyncWebServer.h>

class WebServerHandler
{
public:
    WebServerHandler(AsyncWebServer &server);
    void serveFiles();

private:
    AsyncWebServer &server;
};

#endif
