#ifndef WATER_PUMP_h
#define WATER_PUMP_h

#include <Arduino.h>


class WaterPump {
public:
    WaterPump();
    void begin();
    // void setSpeed(uint8_t speed); ?
    void turnOn();
    void turnOff();

private:
    uint8_t _pin;
};

#endif
