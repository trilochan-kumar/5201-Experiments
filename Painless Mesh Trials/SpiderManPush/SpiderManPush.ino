#include "namedMesh.h"
#include <ArduinoJson.h>

#define MESH_SSID       "ThrillMesh"
#define MESH_PASSWORD   "somethingSneakyHehe"
#define MESH_PORT       5555

Scheduler userScheduler; // to control your personal task
namedMesh mesh;

String nodeName = "Spider Man"; // Name needs to be unique

Task flashButtonTask( TASK_SECOND*1, TASK_FOREVER, []() {
    int flashButtonState = digitalRead(0); // Read the state of flash button
    if (flashButtonState == LOW) {
        // Create a JSON object
        StaticJsonDocument<64> doc;
        doc["button_state"] = 0; // Button state is LOW
        String msg;
        serializeJson(doc, msg); // Serialize the JSON object to a string
        String to = "Iron Man"; // Replace with appropriate recipient
        mesh.sendSingle(to, msg); // Send the message over mesh network
    }
    else {
        // Create a JSON object
        StaticJsonDocument<64> doc;
        doc["button_state"] = 1; // Button state is HIGH2w
        String msg;
        serializeJson(doc, msg); // Serialize the JSON object to a string
        String to = "Iron Man"; // Replace with appropriate recipient
        mesh.sendSingle(to, msg); // Send the message over mesh network
    }
}); // execute every 1 second

void setup() {
    Serial.begin(115200);

    mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION); // set before init() so that you can see startup messages

    mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);

    mesh.setName(nodeName); // This needs to be a unique name!

    mesh.onReceive([](String &from, String &msg) {
        Serial.printf("Received message by name from: %s, %s\n", from.c_str(), msg.c_str());
    });

    mesh.onChangedConnections([]() {
        Serial.printf("Changed connection\n");
    });

    userScheduler.addTask(flashButtonTask);
    flashButtonTask.enable();
}

void loop() {
    userScheduler.execute(); // run the user scheduler tasks
    mesh.update(); // update the mesh network
}
