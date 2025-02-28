#include "BMP280Sensor.h"

BMP280Sensor::BMP280Sensor() {}

void BMP280Sensor::begin()
{
    while (!bmp.begin(0x76))
    {
        Serial.println("Could not find a valid BMP280 sensor, retrying...");
        delay(1000);
    }
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_500);
}

float BMP280Sensor::readTemperature()
{
    return bmp.readTemperature();
}

float BMP280Sensor::readPressure()
{
    return bmp.readPressure();
}

float BMP280Sensor::readAltitude()
{
    return bmp.readAltitude(1013.25);
}