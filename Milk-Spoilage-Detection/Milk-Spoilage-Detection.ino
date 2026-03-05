#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define sensor pins
#define PH_PIN 34          // ESP32 ADC pin for pH sensor
#define MQ135_PIN 35       // ESP32 ADC pin for MQ-135 sensor
#define TEMP_PIN 4         // DS18B20 data pin connected to GPIO4

// DS18B20 setup
OneWire oneWire(TEMP_PIN);
DallasTemperature sensors(&oneWire);

float voltage = 0.0;
float pHValue = 0.0;
int mq135Value = 0;
float temperatureC = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);

  // Initialize I2C with custom pins
  Wire.begin(21, 22);  

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Start temperature sensor
  sensors.begin();

  lcd.setCursor(0,0);
  lcd.print("Milk Test System");
}

void loop() {

  // pH sensor reading
  int adcValue = analogRead(PH_PIN);
  voltage = adcValue * (3.3 / 4095.0);
  pHValue = 7 + ((2.5 - voltage) / 0.18);

  // MQ-135 sensor reading
  mq135Value = analogRead(MQ135_PIN);

  // Temperature reading
  sensors.requestTemperatures();
  temperatureC = sensors.getTempCByIndex(0);

  // Serial Monitor Output
  Serial.print("pH: "); Serial.print(pHValue,2);
  Serial.print(" | MQ135: "); Serial.print(mq135Value);
  Serial.print(" | Temp: "); Serial.print(temperatureC);
  Serial.println(" C");

  // LCD Display
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("pH:");
  lcd.print(pHValue,1);
  lcd.print(" T:");
  lcd.print(temperatureC,1);

  lcd.setCursor(0,1);
  lcd.print("MQ135:");
  lcd.print(mq135Value);

  delay(2000);
}