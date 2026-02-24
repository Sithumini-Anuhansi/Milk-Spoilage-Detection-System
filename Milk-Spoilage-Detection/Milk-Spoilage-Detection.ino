#include <DFRobot_PH.h> // pH Sensor library

// Initialize pH Sensor
DFRobot_PH ph;

// PH-4502C pH Sensor Pin
#define PH_PIN 34   // Analog input

float phValue;
float temperature = 25.0;   // Default temperature

void setup() {
  Serial.begin(115200);
  ph.begin();

  Serial.println("pH Sensor Monitoring Started...");
}

void loop() {

  // Read pH value
  phValue = ph.readPH(analogRead(PH_PIN), temperature);

  // Print pH value every 2 seconds
  Serial.print("pH Value: ");
  Serial.println(phValue, 2);

  Serial.println("-----------------------");

  delay(2000); 
}