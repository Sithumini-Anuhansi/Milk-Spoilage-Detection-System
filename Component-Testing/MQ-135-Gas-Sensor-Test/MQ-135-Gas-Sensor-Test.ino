/* MQ-135 GAS SENSOR TEST */

#define MQ135_PIN 32 // MQ-135 A0 pin

void setup() {
  
  Serial.begin(115200);          
  delay(2000);                   
  
  Serial.println("MQ-135 Gas Sensor Test - GPIO 32");
}

void loop() {

  // Read raw analog value from MQ-135
  // ESP32 ADC range = 0 to 4095 (12-bit resolution)
  int adcValue = analogRead(MQ135_PIN);

  // Convert ADC value to actual voltage
  // ESP32 operates at 3.3V, so we use:
  // Voltage = (ADC / 4095) * 3.3
  float voltage = adcValue * (3.3 / 4095.0);

  // Print raw ADC value
  Serial.print("ADC Value: ");
  Serial.print(adcValue);

  // Print converted voltage
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);   // Show 3 decimal places
  Serial.println(" V");

  delay(3000);  // Wait 3 second before next reading
}