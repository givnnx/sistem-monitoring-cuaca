#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <ESPAsyncWebServer.h>

class WebSocketHandler
{
public:
    WebSocketHandler(AsyncWebServer &server);
    void begin();
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    void sendToAll(const String &message);

private:
    AsyncWebSocket ws;
};

#endif
