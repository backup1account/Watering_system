#ifndef LCD_h
#define LCD_h

#include <Arduino.h>
#include "LiquidCrystal_PCF8574.h"


class LCD {
public:
    LCD();
    void begin(uint8_t lcdColumns, uint8_t lcdRows, uint8_t lcdAddress, uint8_t backlight);
    void printWelcomeMessage();
    void printSoilMoistureLevel(float moistureValue);
    void printPlantNeedWateringMessage();
    void printPlantAlreadyWateredMessage();
    void clear();

private:
    LiquidCrystal_PCF8574 _lcdI2C;
};

#endif
