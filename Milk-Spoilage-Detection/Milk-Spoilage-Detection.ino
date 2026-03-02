#include <DFRobot_PH.h> // pH Sensor library
#include <OneWire.h>           // DS18B20 library dependency
#include <DallasTemperature.h> // DS18B20 library


// Initialize pH Sensor
DFRobot_PH ph;


// PH-4502C pH Sensor Pin
#define PH_PIN 34   // Analog input

// ----- DS18B20 Setup -----
#define ONE_WIRE_BUS 32      // GPIO where DS18B20 data pin is connected

#define MQ135 35              // MQ-135 Gas Sensor(Analog pin)
#define BUZZER 25              // Buzzer

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float phValue;
float temperature = 25.0;   // Default temperature
int threshold = 400;           // Gas threshold

void setup() {
  Serial.begin(115200);
  ph.begin();

  sensors.begin();

  Serial.println("pH Sensor Monitoring Started...");

  Serial.println("MQ gas sensor monitoring started...");

  pinMode(BUZZER, OUTPUT);
}

void loop() {

  // Read pH value
  phValue = ph.readPH(analogRead(PH_PIN), temperature);

    // Request temperature from DS18B20
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0); // get temperature in Celsius

  // Print pH value every 2 seconds
  Serial.print("pH Value: ");
  Serial.println(phValue, 2);

   // Print temperature value every 2 seconds
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" °C");

  // --- PART 2: Gas Sensor (Milk Spoilage) Logic ---
  
  int gasValue = analogRead(MQ135);

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  if (gasValue < 300) {
    Serial.println("Milk Status: FRESH");
    digitalWrite(BUZZER, LOW);
  }
  else if (gasValue >= 300 && gasValue < threshold) {
    Serial.println("Milk Status: STARTING TO SPOIL");
    digitalWrite(BUZZER, LOW);
  }
  else {
    Serial.println("Milk Status: SPOILED");
    digitalWrite(BUZZER, HIGH);
  }

  Serial.println("-----------------------");

  delay(2000); // Wait 2 seconds before the next reading

}



