/* I2C CODE SCANNER FOR LCD */

#include <Wire.h>   // Library for I2C communication

void setup() {

  Serial.begin(115200);     // Start serial communication at 115200 baud rate
  delay(1000);              // Small delay for stability

  Serial.println("I2C Scanner Starting...");

  // Start I2C communication
  // Wire.begin(SDA, SCL)
  // SDA = GPIO 21
  // SCL = GPIO 22
  Wire.begin(21, 22);       
}

void loop() {

  byte error, address;      // Variables to store error status and device address
  int deviceCount = 0;      // Counter for detected devices

  Serial.println("Scanning...");

  // I2C addresses range from 1 to 126
  for(address = 1; address < 127; address++) {

    // Begin communication with a device at 'address'
    Wire.beginTransmission(address);

    // End transmission and check for response
    error = Wire.endTransmission();

    // If error == 0, device responded successfully
    if (error == 0) {
      
      Serial.print("I2C device found at address: 0x");

      // Add leading zero if address is less than 16
      if (address < 16)
        Serial.print("0");

      // Print address in hexadecimal format
      Serial.println(address, HEX);

      deviceCount++;   // Increase device counter
    }
  }

  // If no device detected
  if (deviceCount == 0) {
    Serial.println("No I2C devices found");
  } 
  else {
    Serial.println("Scan complete");
  }

  delay(5000);   // Wait 5 seconds before scanning again
}