#ifndef RAINDROPSENSOR_H
#define RAINDROPSENSOR_H

class RaindropSensor
{
public:
    RaindropSensor(int pin);
    bool isRaining();

private:
    int _pin;
};

#endif