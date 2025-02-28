#ifndef BMP280SENSOR_H
#define BMP280SENSOR_H

#include <Adafruit_BMP280.h>

class BMP280Sensor
{
public:
    BMP280Sensor();
    void begin();
    float readTemperature();
    float readPressure();
    float readAltitude();

private:
    Adafruit_BMP280 bmp;
};

#endif