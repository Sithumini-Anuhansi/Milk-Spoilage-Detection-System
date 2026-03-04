#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define sensor pins
#define PH_PIN 34         // ESP32 ADC pin for pH sensor
#define MQ135_PIN 35      // ESP32 ADC pin for MQ-135 sensor

float voltage = 0.0;
float pHValue = 0.0;
int mq135Value = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);

  // Initialize I2C with custom pins
  Wire.begin(21, 22);  

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("pH & MQ135 Test");
}

void loop() {
  // pH sensor reading
  int adcValue = analogRead(PH_PIN);
  voltage = adcValue * (3.3 / 4095.0);            // Convert ADC to voltage
  pHValue = 7 + ((2.5 - voltage) / 0.18);        // Approximate pH calculation (calibrate for accuracy!)

  // MQ-135 sensor reading
  mq135Value = analogRead(MQ135_PIN);            // Raw ADC value

  // Serial output
  Serial.print("pH ADC: "); Serial.print(adcValue);
  Serial.print(" | Voltage: "); Serial.print(voltage, 3);
  Serial.print(" V | pH: "); Serial.print(pHValue, 2);
  Serial.print(" | MQ-135 ADC: "); Serial.println(mq135Value);

  // LCD display
  lcd.setCursor(0,0);
  lcd.print("pH: ");
  lcd.print(pHValue, 2);
  lcd.print("    ");  // Clear extra chars

  lcd.setCursor(0,1);
  lcd.print("MQ: ");
  lcd.print(mq135Value);
  lcd.print("      ");  // Clear extra chars

  delay(2000);  // 2 second delay between readings
}