#include <M5Stack.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <coap-simple.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
IPAddress serverIP(192, 168, 1, 100);  // Update with your server's IP address
int serverPort = 5683;  // CoAP default port

WiFiUDP udp;
Coap coap(udp);

void setup() {
  M5.begin();

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }

  M5.Lcd.println("");
  M5.Lcd.println("WiFi connected");
  M5.Lcd.println("IP address:");
  M5.Lcd.println(WiFi.localIP());

  coap.start();
}

void loop() {
  M5.update();

  if (M5.BtnA.wasReleased()) {
    sendButtonState("A");
  } else if (M5.BtnB.wasReleased()) {
    sendButtonState("B");
  } else if (M5.BtnC.wasReleased()) {
    sendButtonState("C");
  }

  delay(100);
}

void sendButtonState(const char* button) {
  M5.Lcd.print("Sending button state: ");
  M5.Lcd.println(button);

  int msgid = coap.put(serverIP, serverPort, "button", button);
  M5.Lcd.print("Message ID: ");
  M5.Lcd.println(msgid);
}
