#include "WaterPump.h"


WaterPump::WaterPump() : _pin(12) {}

void WaterPump::begin() {
    DDRB |= (1 << DDB4);  // set pin 12 as an output
}

void WaterPump::turnOn() {
    PORTB |= (1 << PORTB4);  // set the output state of pin 12 to HIGH
}

void WaterPump::turnOff() {
    PORTB &= ~(1 << PORTB4); // set the output state of pin 12 to LOW
}
