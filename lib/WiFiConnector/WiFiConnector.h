#ifndef WIFICONNECTOR_H
#define WIFICONNECTOR_H

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h> // mDNS untuk ESP8266

class WiFiConnector
{
public:
    WiFiConnector(const char *ssid, const char *password, const char *hostname);
    void connect();
    bool setupMDNS();

private:
    const char *ssid;
    const char *password;
    const char *hostname;
};

#endif