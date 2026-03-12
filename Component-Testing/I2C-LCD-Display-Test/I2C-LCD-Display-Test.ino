/* I2C LCD TEST */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD I2C address (most common is 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  Serial.begin(115200);

  // Start I2C communication with custom pins
  Wire.begin(21, 22);   // SDA = 21, SCL = 22

  lcd.init();           // Initialize LCD
  lcd.backlight();      // Turn on backlight

  lcd.setCursor(0, 0);  // Column 0, Row 0
  lcd.print("Hello World!");

  lcd.setCursor(0, 1);  // Column 0, Row 1
  lcd.print("ESP32 LCD Test");
}

void loop() {
  // Nothing here for now
}