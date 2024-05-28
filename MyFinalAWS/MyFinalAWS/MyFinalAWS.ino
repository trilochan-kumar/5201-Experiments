#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* ssid = "2o25";
const char* password = "19o82oo2";
const char* awsEndpoint = "at7bpkpyvqan0-ats.iot.us-east-1.amazonaws.com";
const char* deviceID = "IronMan";

const char* certificate = "-----BEGIN CERTIFICATE-----\n\
MIIDWjCCAkKgAwIBAgIVAP6FpxjI+JOp3oMtilu6lhRt6GrjMA0GCSqGSIb3DQEB\n\
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n\
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDA0MTIxMDQz\n\
MDlaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n\
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDAYjYHaT9FZpbmtsdO\n\
rvELT94+0sVy8IfEo9bjakKkt8sRx5V/pCLMPMUfpdKg1OL6vZCHhPMOuGy669OZ\n\
eMMfh0cvJq31vdk5h7mWR5NgvshbvWu17QS0m+H8azOFqQK0b9rNNXQ/22ZOR3fU\n\
D68/JgO1I4xWhB2C4mPdz2IOZn95Je5JIurL7b0lP37fdt2qXyqdQRGtQNiA+8/y\n\
tqqZPZ91/uelpgYY4I6XL1VtXpDwVQ6TyXyXWP5bexh3nS9DNsclwoptZkHV2M8D\n\
wHZugHBKEz245HxRPgCIlV8Jh1ajtbZQ8MYYREnGBmcn7nP8Hc6tSk3+wwS2NUdN\n\
t5dJAgMBAAGjYDBeMB8GA1UdIwQYMBaAFKhHI73SEcdE4hX53UEuJn82kbAnMB0G\n\
A1UdDgQWBBQvou9Qf3wG60R2RYHk0rnxpsX+FjAMBgNVHRMBAf8EAjAAMA4GA1Ud\n\
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAN4B+l/pAhEZwlAjqFnJArvYH\n\
MvN3HUzROn6fZLQUezD0Namt4yyQH+9Aihk2kFK0MLNTDp+hqNRXBBknQFEjT6pb\n\
V23QfxZ1G1ykGF4A0Jya9o2YAwg3wpgcT81Olqflu3Inxrv4ZYM/bn86W2lDnZ72\n\
9CZj+XN14jzBGlrj+KFy9E0YPKcxGtU94ASOaEbLetuWB6Vwut+LHHbad8EfP3F1\n\
frabPcuKCuqyO58vrhn6Yn7tNopwxmYDYoyITlvpp/mZ7/qwOj3HU70KOQ5gA5ED\n\
AHLBA+gjslFXvgKbKGoF2y7hfQVsiX/GeSegXfGr9cCQ3lh8Ln2qpw3NQB8KWw==\n\
-----END CERTIFICATE-----\n";

const char* privateKey = "-----BEGIN RSA PRIVATE KEY-----\n\
MIIEpAIBAAKCAQEAwGI2B2k/RWaW5rbHTq7xC0/ePtLFcvCHxKPW42pCpLfLEceV\n\
f6QizDzFH6XSoNTi+r2Qh4TzDrhsuuvTmXjDH4dHLyat9b3ZOYe5lkeTYL7IW71r\n\
te0EtJvh/GszhakCtG/azTV0P9tmTkd31A+vPyYDtSOMVoQdguJj3c9iDmZ/eSXu\n\
SSLqy+29JT9+33bdql8qnUERrUDYgPvP8raqmT2fdf7npaYGGOCOly9VbV6Q8FUO\n\
k8l8l1j+W3sYd50vQzbHJcKKbWZB1djPA8B2boBwShM9uOR8UT4AiJVfCYdWo7W2\n\
UPDGGERJxgZnJ+5z/B3OrUpN/sMEtjVHTbeXSQIDAQABAoIBAHTDJseYuS4F9dBR\n\
XuYCh4m2D81RX0VDdyOBzQp5k7klU7qWx8WQeQ48U+fBXPUAQEKuium1Z0+n31YT\n\
i3m6MbMRB8M2Vp6vewfPuHPdPTWalUAY1yazlAeKFL5+0eZtjZa1zLZ/mu6m2pDo\n\
D3JFkrdg+x8VVDeuN7sYbERTedACl+AkIPC5f7bn49LgAV2YOkQWMGNMETCp959N\n\
A/ho4Nhc5qEhch8/YNz+f3ZlCbj1feW0Toi5H4JaS68O88s9N02ZaJ6vKJ/SyOja\n\
sluHBxdOe8RLzdPt41HH6Do1JuoEcC5Cec0QIH8P6GC0Ut8S1Eg9fM+sg+Pz8P7b\n\
Y1jkHYECgYEA6XXKYiCUb5GmbO/5/BIbrG9cFQjQb2KdG+trLTtRqZQWKHiisdHQ\n\
6FR693RpfJsjct4Rv2Qo0+Ho9itfJ0RhnRFoGfaQJ2KveJ0lymcdu7O12OGRBO1m\n\
sfyqsgB+h3yQJIrpQ5sCFJjAJQKasKb7K1G2n6vUiOnQk9lESki9IpMCgYEA0vUs\n\
K9gQib6oWevtcEglSPBZ3WWBY+ijEMJu1pTq6sTpRfxHSPoG9M5JZcdM85uoiZwi\n\
brdNMeccvIr4FoPbX99RhRMIvL23jbqh9GeK0mzNWh6Fz/djEp9DpDHPx+dOWe51\n\
RyeOA5NjWWFof2OrE1r/JQkFMYNj/garkWGb/DMCgYEA1/HIffO82WZUFrfy96KY\n\
TmvDNQGuKxmAUW70+CXCZ6U+ybisZOa64ewiwfnACS5HH90hdXNkAHkaT3nWzi+G\n\
Sw7qx/k1Zfj2bg6OAiZXbmPQdQhQZ8pgD4qzKWsjnpctjV+gXJRo3Dxent1F0Njj\n\
wzIWRqNeODZuZBO4Ay49JFkCgYAiek2A0OxLBu0O3T9OJYxqclXNmGRgRso31/8z\n\
dN08B3i0pnmkFLEEW56lUsBh5CPUcb8y5yRnroUEz5WiYGR/M8ln/WdlKYCRWlpT\n\
zoRixcN+IhTum1kG1x6//CAgZM5qZk2mlnFgZjtLhV8Fyu1P2YRvshy2LeouvzpV\n\
JWXP/wKBgQCqYCKoxME4IheMNRcDOcWtL7t87YFUAF8o6+KWYMr03RviUSr9tGi4\n\
PzVx+h6YamLjhdkg5zpT49nYSGT8s+Zs4BMY2m/UVhlsTHgqhSl/6hU3r273IcDd\n\
f4z/d2VTKmhx/6R2tzY1Db6tj/eRNTm15lxR6cAe+y+o8zgwRZdESg==\n\
-----END RSA PRIVATE KEY-----\n";

const char* rootCA = "-----BEGIN CERTIFICATE-----\n\
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n\
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n\
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n\
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n\
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n\
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n\
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n\
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n\
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n\
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n\
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n\
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n\
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n\
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n\
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n\
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n\
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n\
rqXRfboQnoZsG4q5WTP468SQvvG5\n\
-----END CERTIFICATE-----\n";

WiFiClientSecure espClient = WiFiClientSecure();
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi Connected");

  espClient.setCACert(rootCA);
  espClient.setCertificate(certificate);
  espClient.setPrivateKey(privateKey);

  client.setServer(awsEndpoint, 8883);
  client.setCallback(callback);

  while (!client.connected()) {
    if (client.connect(deviceID)) {
      Serial.println("Connected to AWS IoT Core");
      client.subscribe("esp32/trial");
    } else {
      Serial.print("Failed to connect to AWS, rc=");
      Serial.println(client.state());
      delay(1000);
    }
  }

  // Publish a message after connecting to AWS IoT Core
  //client.publish("esp32/trial", "Hello from ESP32!");
}
`
void loop() {
  client.loop();
  client.publish("esp32/trial", "Hello from ESP32!");
  delay(5000);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
