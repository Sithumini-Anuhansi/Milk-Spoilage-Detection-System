/* 4502C PH SENSOR TEST */

#define PH_PIN 34 

float voltage = 0.0;
float pHValue = 0.0;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("4502C pH Sensor Test with ESP32");
}

void loop() {

  int adcValue = analogRead(PH_PIN);   // Read raw ADC value

  voltage = adcValue * (3.3 / 4095.0); // Convert ADC to voltage (ESP32 is 12-bit)

  // Approximate pH calculation (needs calibration!)
  pHValue = 7 + ((2.5 - voltage) / 0.18);

  Serial.print("ADC Value: ");
  Serial.print(adcValue);

  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);

  Serial.print(" V | pH Value: ");
  Serial.println(pHValue, 2);

  delay(3000);
}