#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "DHTSensor.h"
#include "WiFiConnector.h"
#include "WebSocketHandler.h"
#include "FileSystemHandler.h"
#include "WebServerHandler.h"
#include "RaindropSensor.h"
#include "lcd_i2c.h"

#define DHTPIN D3
#define DHTTYPE DHT22
#define RAINDROP_PIN D4
#define LCD_SDA_PIN D5
#define LCD_SCL_PIN D6

const char *ssid = "kamarku";
const char *password = "unbanned";
const char *hostname = "mynodemcu";

DHTSensor dhtSensor(DHTPIN, DHTTYPE);
RaindropSensor raindropSensor(RAINDROP_PIN);
WiFiConnector wifi(ssid, password, hostname);
AsyncWebServer server(8080);
WebSocketHandler wsHandler(server);
WebServerHandler webServerHandler(server);
lcd_i2c lcd(0x27, 16, 2, LCD_SDA_PIN, LCD_SCL_PIN);

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // Hubungkan ke WiFi
  wifi.connect();
  // Inisialisasi mDNS
  if (!wifi.setupMDNS())
  {
    Serial.println("mDNS setup failed");
  }

  // Inisialisasi sensor DHT
  dhtSensor.begin();

  if (!LittleFS.begin())
  {
    Serial.println("Failed to mount LittleFS");
    return;
  }
  else
  {
    Serial.println("LittleFS mounted successfully");
  }

  // Menyajikan file melalui server web
  webServerHandler.serveFiles();

  // Inisialisasi WebSocket
  wsHandler.begin();

  // Mulai server
  server.begin();

  // Mulai LCD
  lcd.begin();
  lcd.setFirstln("LCD Initialized");
  delay(1000);
  lcd.setSecondln("Ready to go...");
  delay(500);
  lcd.clear();
}

void loop()
{
  // Membaca data sensor setiap 2 detik
  static unsigned long lastRead = 0;
  if (millis() - lastRead > 2000)
  {
    lastRead = millis();
    float temp = dhtSensor.readTemperature();
    float hum = dhtSensor.readHumidity();
    bool isRaining = raindropSensor.isRaining();
    if (!isnan(temp) && !isnan(hum))
    {
      Serial.printf("Temperature: %.2f °C, Humidity: %.2f %%\n", temp, hum);

      // Kirim data ke klien WebSocket
      String json = "{\"temperature\": " + String(temp) + ", \"humidity\": " + String(hum) + ", \"isRaining\": " + String(isRaining) + "}";
      wsHandler.sendToAll(json); // Mengirim data dalam format JSON

      lcd.clear();
      lcd.setFirstln(("Temperature: " + String(temp) + " °C").c_str());
      lcd.setSecondln(("Humidity: " + String(hum) + " %").c_str());
    }
  }
}
