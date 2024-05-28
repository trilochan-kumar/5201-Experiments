//#include <DHT.h>

//dht DHT;

#define DHT11_PIN 4
void setup(){

	Serial.begin(115200);
}
void loop(){
  // int chk = DHT.read11(DHT11_PIN);
  // Serial.print("Temperature = ");
  // Serial.println(DHT.temperature);
  // Serial.print("Humidity = ");
  // Serial.println(DHT.humidity);
  Serial.print("\n Raw Data = ");
  Serial.println(analogRead(4));
  delay(100);
}