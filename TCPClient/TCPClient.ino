#include <M5Stack.h>
#include <WiFi.h>
#include <WiFiMulti.h>

const char *ssid     = "xxx";
const char *password = "xxx";
WiFiMulti WiFiMulti;

void setup() {
    int sum = 0;
    M5.begin();        // Init M5Core.
    M5.Power.begin();  // Init power
    WiFiMulti.addAP(ssid, password);  // Add wifi configuration information.
    M5.lcd.printf("Waiting connect to WiFi: %s ...", ssid);  // Serial port output format string.
    while (WiFiMulti.run() !=WL_CONNECTED) {  // If the connection to wifi is not established successfully.
        M5.lcd.print(".");
        delay(1000);
        sum += 1;
        if (sum == 8) M5.lcd.print("Conncet failed!");
    }
    M5.lcd.println("\nWiFi connected");
    M5.lcd.print("IP address: ");
    M5.lcd.println(WiFi.localIP());  // The serial port outputs the IP address of the M5Core.
    delay(500);
}

void loop() {
    M5.lcd.setCursor(0, 40);
    const char *host = "xxxxxx";  // Set the IP address or DNS of the TCP server.
    const uint16_t port = 80;  // The port of the TCP server is specified.
    
    M5.lcd.printf("Connecting to: %s\n", host);
    WiFiClient client;
    if (!client.connect(host,port)) {  // Connect to the server. 0 is returned if the connection fails.
        M5.lcd.print("Connection failed.\nWaiting 5 seconds before retrying...\n");
        delay(5000);
        return;
    }
    // send an arbitrary string to the server.
    client.print("Send this data to the server");
    // send a basic document request to the server.
    client.print("GET /index.html HTTP/1.1\n\n");
    int maxloops = 0;

    // wait for the server's reply to become available
    while (!client.available() && maxloops < 1000) {
        maxloops++;
        delay(1);
    }
    if (client.available() > 0) {  // Detects whether data is received.
        String line = client.readStringUntil('\r');  // Read information from data received by the device until \r is read.
        M5.lcd.println(line);  // String received by serial port output.
    } 
    else
        M5.lcd.println("client.available() timed out ");
        
    M5.lcd.println("Closing connection.");
    client.stop();
    M5.lcd.println("Waiting 5 seconds before restarting...");
    delay(5000);
    M5.lcd.fillRect(0, 40, 320, 220, BLACK);
}
