#include "namedMesh.h"
#include <ArduinoJson.h>

#define MESH_SSID       "ThrillMesh"
#define MESH_PASSWORD   "somethingSneakyHehe"
#define MESH_PORT       5555

Scheduler userScheduler;
namedMesh mesh;

String nodeName = "Iron Man";

void setup() {
    Serial.begin(115200);

    mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);
    mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);
    mesh.setName(nodeName);

    mesh.onReceive([](String &from, String &msg) {
        Serial.printf("Received message from: %s, %s\n", from.c_str(), msg.c_str());

        StaticJsonDocument<64> doc;
        DeserializationError error = deserializeJson(doc, msg);
        if (!error) {
            int buttonState = doc["button_state"];
            if (buttonState == 0) {
                pinMode(2, OUTPUT);
                digitalWrite(2, HIGH);
                Serial.println("LED turned on");
            }
            else {
                pinMode(2, OUTPUT);
                digitalWrite(2, LOW);
            }
        }
    });
}

void loop() {
    mesh.update();
}
