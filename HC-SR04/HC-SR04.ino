int trig = 9;
int echo = 13;
int led = 2;

void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trig,1);
  delayMicroseconds(2);
  digitalWrite(trig,0);

  int duration = pulseIn(echo,1);
  float distance = (duration*0.034)/2;

  digitalWrite(led,0);  
  if(distance<100) { digitalWrite(led,1); }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

}
