#include <WiFi.h>

const char *ssid = "2o24";  // Update with your WiFi credentials
const char *password = "19o82oo2";
const uint16_t serverPort = 8080;
const int maxClients = 5;  // Maximum number of simultaneous clients

WiFiServer server(serverPort);
WiFiClient clients[maxClients];

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    server.begin();
    Serial.println("Server started");
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    // Check for new client connections
    WiFiClient newClient = server.available();

    if (newClient) {
        for (int i = 0; i < maxClients; i++) {
            if (!clients[i] || !clients[i].connected()) {
                if (clients[i]) {
                    clients[i].stop();
                }
                clients[i] = newClient;
                Serial.println("New client connected");

                // Handle the client in a separate task
                TaskHandle_t task;
                xTaskCreatePinnedToCore(
                    handleClientTask,  // Task function
                    "HandleClient",    // Task name
                    10000,             // Stack size (bytes)
                    (void *)&clients[i],   // Task parameter
                    1,                 // Task priority
                    &task,             // Task handle
                    0                  // Core to run the task (0 or 1)
                );

                break;
            }
        }
    }

    // Check for disconnected clients and clear the corresponding slot
    for (int i = 0; i < maxClients; i++) {
        if (clients[i] && !clients[i].connected()) {
            clients[i].stop();
        }
    }

    // Check for incoming data from the serial monitor
    if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');
        sendDataToClient(data);
    }

    delay(100);  // Small delay for stability
}

void handleClientTask(void *param) {
    WiFiClient *client = (WiFiClient *)param;

    while (client->connected()) {
        if (client->available()) {
            String request = client->readStringUntil('\r');
            Serial.println(request);

            // Process client request here and send response
            client->println("HTTP/1.1 200 OK");
            client->println("Content-Type: text/plain");
            client->println();
            client->println("Response from ESP32 TCP Server");

            // Keep the connection alive by reading from the client
            client->read();  // Read a byte from the client

            delay(10);  // Small delay for stability
        }
        delay(10);
    }

    vTaskDelete(NULL);  // Delete the task when done handling the client
}

void sendDataToClient(String data) {
    // Parse client index from input data
    int clientIndex = -1;
    if (data.startsWith("1,")) {
        clientIndex = 0;
    } else if (data.startsWith("2,")) {
        clientIndex = 1;
    } else if (data.startsWith("3,")) {
        clientIndex = 2;
    } else if (data.startsWith("4,")) {
        clientIndex = 3;
    } else if (data.startsWith("5,")) {
        clientIndex = 4;
    }

    if (clientIndex != -1 && clients[clientIndex] && clients[clientIndex].connected()) {
        // Extract message from input data
        int commaIndex = data.indexOf(',');
        if (commaIndex != -1) {
            String message = data.substring(commaIndex + 1);
            clients[clientIndex].println(message);
        }
    }
}
