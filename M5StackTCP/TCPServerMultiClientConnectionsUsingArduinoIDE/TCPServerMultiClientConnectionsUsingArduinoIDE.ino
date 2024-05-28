#include <M5Stack.h>
#include <WiFi.h>
#include <WiFiMulti.h>

const char *ssid = "2o24";  // Update with your WiFi credentials
const char *password = "19o82oo2";
const uint16_t serverPort = 8080;

WiFiMulti WiFiMulti;
WiFiServer server(serverPort);

void setup() {
    M5.begin();
    M5.Power.begin();

    WiFiMulti.addAP(ssid, password);
    while (WiFiMulti.run() != WL_CONNECTED) {
        delay(1000);
        M5.lcd.print(".");
    }

    server.begin();
    M5.lcd.println("Server started");
    M5.lcd.println(WiFi.localIP());
}

void loop() {
    WiFiClient client = server.available();

    if (client) {
        M5.lcd.println("New client connected");
        client.println("Hello from M5Stack TCP Server");

        while (client.connected()) {
            if (client.available()) {
                String request = client.readStringUntil('\r');
                M5.lcd.println(request);

                // Process client request here and send response
                client.println("HTTP/1.1 200 OK");
                client.println("Content-Type: text/plain");
                client.println();
                client.println("Response from M5Stack TCP Server");
                break;  // Exit the loop after handling one request
            }
            delay(1);
        }
        client.stop();
        M5.lcd.println("Client disconnected");
    }
}
