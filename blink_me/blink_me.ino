// This code is to Blink the in-built LED

int BUILT_IN_LED = 2;

void setup(){
  pinMode(BUILT_IN_LED,OUTPUT);
  Serial.begin(115200);
}

void loop(){
  delay(10);
  digitalWrite(BUILT_IN_LED,HIGH);
  Serial.println("LED ON");
  delay(1000);
  digitalWrite(BUILT_IN_LED,LOW);
  Serial.println("LED OFF");
  delay(1000);
}zz