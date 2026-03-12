#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup (replace 0x27 with your scanner-detected address if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define pH sensor analog pin
#define PH_PIN 34 

float voltage = 0.0;
float pHValue = 0.0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize I2C with custom pins
  Wire.begin(21, 22);  

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("pH Sensor Test");
}

void loop() {

  // Read raw ADC from pH sensor
  int adcValue = analogRead(PH_PIN);

  // Convert ADC (0-4095) to voltage (ESP32 3.3V)
  voltage = adcValue * (3.3 / 4095.0);

  // Approximate pH calculation (needs calibration!)
  pHValue = 7 + ((2.5 - voltage) / 0.18);

  // Print to Serial Monitor
  Serial.print("ADC: "); Serial.print(adcValue);
  Serial.print(" | Voltage: "); Serial.print(voltage, 3);
  Serial.print(" V | pH: "); Serial.println(pHValue, 2);

  // Display on LCD
  lcd.setCursor(0,1);
  lcd.print("pH: ");
  lcd.print(pHValue, 2);
  lcd.print("    ");  // Clear extra characters

  delay(1000);  // Read every 1 second
}