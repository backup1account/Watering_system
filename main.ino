#include <Arduino.h>
#include "LCD.h"
#include "WaterPump.h"

#define SOILMOISTURE_PIN A0
#define WATERPUMP_PIN 12
#define PUMP_ON_TIME 2000 // pump ON time in milliseconds

const int moistureThreshold = 700;

// LCD configuration variables
const int lcdAddress = 0x3F; // I2C address of LCD module
const int lcdColumns = 16; // Number of columns in LCD module
const int lcdRows = 2; // Number of rows in your LCD module
const int backlight = 255;

LCD lcdDisplay;
WaterPump WPump;

enum PumpState {
  OFF,
  ON,
};

PumpState pumpState = OFF;
unsigned long pumpTurnOnTime = 0;

void setup() {
    // Setup Serial for debugging
    Serial.begin(9600);
    while (!Serial);  // wait for serial port to connect
    Serial.println("Start");

    // LCD setup
    lcdDisplay.begin(lcdColumns, lcdRows, lcdAddress, backlight);
    
    // Display welcome message
    lcdDisplay.printWelcomeMessage();
    delay(1000);
    lcdDisplay.clear();

    // Water pump setup
    WPump.begin();  // setup pump control pin (12 is default)
    WPump.turnOff();
}

void loop() {
    static unsigned long lastReadTime = 0;
    if (millis() - lastReadTime > 1000) { // read every 1000 ms
        lastReadTime = millis();
        int moistureValue = analogRead(SOILMOISTURE_PIN);
        Serial.println(moistureValue);

        float moistureValuePercentage = ( 100 - ( (moistureValue / 1023.00) * 100 ) );

        if (moistureValue > moistureThreshold) {
          lcdDisplay.clear();
          lcdDisplay.printPlantNeedWateringMessage();
          lcdDisplay.printSoilMoistureLevel(moistureValuePercentage);

          // launch water pump for 1 second
          if (pumpState == OFF) {
            pumpState = ON;
            pumpTurnOnTime = millis();
            WPump.turnOn();
          }
        } else {
          lcdDisplay.clear();
          lcdDisplay.printPlantAlreadyWateredMessage();
          lcdDisplay.printSoilMoistureLevel(moistureValuePercentage);
        }
    }

    if (pumpState == ON && millis() - pumpTurnOnTime > PUMP_ON_TIME) {
        pumpState = OFF;
        WPump.turnOff();
    }
}