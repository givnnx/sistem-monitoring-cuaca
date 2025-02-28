#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>
#include "DHTSensor.h"
#include "WiFiConnector.h"
#include "WebSocketHandler.h"
#include "FileSystemHandler.h"
#include "WebServerHandler.h"
#include "RaindropSensor.h"
#include "lcd_i2c.h"
#include "BMP280Sensor.h"

#define DHTPIN D3
#define DHTTYPE DHT22
#define RAINDROP_PIN D4

const char *ssid = "kamarku";
const char *password = "unbanned";
const char *hostname = "mynodemcu";

DHTSensor dhtSensor(DHTPIN, DHTTYPE);
RaindropSensor raindropSensor(RAINDROP_PIN);
WiFiConnector wifi(ssid, password, hostname);
AsyncWebServer server(8080);
WebSocketHandler wsHandler(server);
WebServerHandler webServerHandler(server);
lcd_i2c lcd(0x27, 16, 2);
BMP280Sensor bmp;

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

  Wire.begin();

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

  // Mulai BMP280 sensor
  bmp.begin();

  // Mulai LCD
  lcd.begin();

  Serial.println("Setup Completed");
}

void loop()
{
  // Membaca data sensor setiap 2 detik
  static unsigned long lastRead = 0;
  static unsigned long switchText = 0;
  static bool toggle = false; // Variabel untuk berganti antara dua teks

  if (millis() - lastRead > 2000) // Setiap 2 detik
  {
    lastRead = millis();
    float temp = dhtSensor.readTemperature();
    float hum = dhtSensor.readHumidity();
    bool isRaining = raindropSensor.isRaining();
    float pressure = bmp.readPressure();
    float altitude = bmp.readAltitude();

    if (!isnan(temp) && !isnan(hum))
    {
      // Kirim data ke WebSocket
      String json = "{\"temperature\": " + String(temp) + ", \"humidity\": " + String(hum) + ", \"isRaining\": " + String(isRaining) + "}";
      wsHandler.sendToAll(json);

      // Update LCD pertama
      lcd.setFirstln(("Temp: " + String(temp) + " °C").c_str());
      lcd.setSecondln(("Humid: " + String(hum) + " %").c_str());

      // Berganti teks tiap detik dalam 2 detik pembacaan
      if (millis() - switchText > 1000) // Berganti tiap 1 detik
      {
        switchText = millis(); // reset waktu switchText

        if (toggle)
        {
          lcd.setFirstln(("Pressure: " + String(pressure) + " hPa").c_str());
          lcd.setSecondln(("Altitude: " + String(altitude) + " m").c_str());
        }
        else
        {
          lcd.clear();
          lcd.setFirstln(("Temp: " + String(temp) + " °C").c_str());
          lcd.setSecondln(("Humid: " + String(hum) + " %").c_str());
        }

        toggle = !toggle;
      }
    }
  }
}
