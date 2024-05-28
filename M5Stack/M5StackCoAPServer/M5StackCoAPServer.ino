#include <WiFi.h>
#include <WiFiUdp.h>
#include <coap-simple.h>
#include <M5Stack.h>

const char* ssid = "your ssid";
const char* password = "your passowrd";

WiFiUDP udp;
Coap coap(udp);

void callback_button(CoapPacket &packet, IPAddress ip, int port) {
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;

  String message(p);
  
  if (message.equals("A")) {
    M5.Lcd.print("A is pressed");
  } else if (message.equals("B")) {
    M5.Lcd.print("B is pressed");
  } else if (message.equals("C")) {
    M5.Lcd.print("C is pressed");
  }
}

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
  
  coap.server(callback_button, "button");
  coap.start();
}

void loop() {
  delay(500);
  coap.loop();
}
