#include "WiFiConnector.h"

WiFiConnector::WiFiConnector(const char *ssid, const char *password, const char *hostname)
    : ssid(ssid), password(password), hostname(hostname) {}

void WiFiConnector::connect()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

bool WiFiConnector::setupMDNS()
{
    if (MDNS.begin(hostname))
    {
        Serial.println("mDNS responder started");
        return true;
    }
    else
    {
        Serial.println("Error setting up MDNS responder!");
        return false;
    }
}
