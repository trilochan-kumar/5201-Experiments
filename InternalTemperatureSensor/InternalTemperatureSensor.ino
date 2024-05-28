#include <DHT.h>

#define DHTPIN 12 // Connect DHT11 data pin to GPIO 4
#define DHTTYPE DHT11 // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(2000); // Delay to allow sensor initialization
  dht.begin();
}

void loop() {
  float internalTemp = readInternalTemperature();
  float dhtTemp = readDHTTemperature();

  Serial.print("Internal Temperature: ");
  Serial.print(internalTemp);
  Serial.println(" °C");

  Serial.print("DHT11 Temperature: ");
  Serial.print(dhtTemp);
  Serial.println(" °C");

  float tempDifference = internalTemp - dhtTemp;
  Serial.print("Temperature Difference: ");
  Serial.print(tempDifference);
  Serial.println(" °C");

  delay(1000); // Delay before reading again (adjust as needed)
}

float readInternalTemperature() {
  adcAttachPin(32); // Attach ADC to GPIO 32 for internal temperature sensor
  return (float)analogRead(32) / 1000.0; // Read and convert to Celsius
}

float readDHTTemperature() {
  return dht.readTemperature(); // Read DHT11 temperature in Celsius
}
