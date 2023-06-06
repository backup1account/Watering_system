#include "LCD.h"


LCD::LCD() {}

void LCD::begin(uint8_t lcdColumns, uint8_t lcdRows, uint8_t lcdAddress, uint8_t backlight) {
    _lcdI2C.begin(lcdColumns, lcdRows, lcdAddress, backlight);
}

void LCD::printSoilMoistureLevel(float moistureValue) {
    _lcdI2C.selectLine(2);
    String message = "Moisture: " + String(moistureValue) + "%";
    _lcdI2C.print(message);
}

void LCD::printWelcomeMessage() {
    _lcdI2C.print("Plant Watering");
    _lcdI2C.selectLine(2);
    _lcdI2C.print("System");
}

void LCD::printPlantNeedWateringMessage() {
    _lcdI2C.print("Plant need water");  
}

void LCD::printPlantAlreadyWateredMessage() {
    _lcdI2C.print("Plant watered"); 
}

void LCD::clear() {
    _lcdI2C.clear();
}
