#include "RaindropSensor.h"
#include <Arduino.h>

RaindropSensor::RaindropSensor(int pin) : _pin(pin) {}

bool RaindropSensor::isRaining()
{
    if (digitalRead(_pin) == HIGH)
    {
        return true;
    }
    else
    {
        return false;
    }
}