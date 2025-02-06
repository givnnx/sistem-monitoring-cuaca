#include "WebSocketHandler.h"

WebSocketHandler::WebSocketHandler(AsyncWebServer &server) : ws("/ws")
{
    server.addHandler(&ws);
}

void WebSocketHandler::begin()
{
    ws.onEvent(std::bind(&WebSocketHandler::onEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
}

void WebSocketHandler::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        Serial.printf("Client connected: %u\n", client->id());
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.printf("Client disconnected: %u\n", client->id());
    }
    else if (type == WS_EVT_DATA)
    {
        client->text("Message received");
    }
}

void WebSocketHandler::sendToAll(const String &message)
{
    ws.textAll(message); // Kirim pesan ke semua klien
}
