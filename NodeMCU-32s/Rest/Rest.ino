/*
  This a simple example of the aREST Library for the ESP32 WiFi chip.
  See the README file for more details.

  Written in 2017 by Marco Schwartz under a GPL license.
  
*/

// Import required libraries
#include <WiFi.h>
#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "2o24";
const char* password = "19o82oo2";

// Create an instance of the server
WiFiServer server(80);

// Variables to be exposed to the API
int temperature;
int humidity;

int BUILT_IN_LED = 2;

// Declare functions to be exposed to the API
int ledControl(String command);

void setup()
{
  
  // Start Serial
  Serial.begin(115200);

  // Init variables and expose them to REST API
  temperature = 24;
  humidity = 40;

  pinMode(BUILT_IN_LED,OUTPUT);

  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);

  // Function to be exposed
  rest.function("led",ledControl);

  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id("1");
  rest.set_name("Thrillu's Node");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

}

void loop() {
  
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}

// Custom function accessible by the API
int ledControl(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(BUILT_IN_LED,state);
  return 1;
}
