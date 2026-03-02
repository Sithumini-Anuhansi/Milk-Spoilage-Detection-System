#include <DFRobot_PH.h> // pH Sensor library
#include <OneWire.h>           // DS18B20 library dependency
#include <DallasTemperature.h> // DS18B20 library


// Initialize pH Sensor
DFRobot_PH ph;

 // Initialize DS18B20
  sensors.begin();
  Serial.println("DS18B20 Temperature Sensor Started...");

// PH-4502C pH Sensor Pin
#define PH_PIN 34   // Analog input

// ----- DS18B20 Setup -----
#define ONE_WIRE_BUS 32      // GPIO where DS18B20 data pin is connected
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

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


  Serial.println("-----------------------");

  delay(2000); 
}



#define MQ135 A0      // MQ-135 connected to A0
#define BUZZER 8      // Buzzer connected to D8 (optional)

int threshold = 400;  // Adjust after testing

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  Serial.println("Milk Spoilage Detection System Started");
}

void loop() {
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

  Serial.println("----------------------------");
  delay(2000);
}