// Pulse Monitor Test Script 
int PinS = 22;
int PinPlus = 23;
 
void setup() { 
	  Serial.begin(115200);
    pinMode(PinS,INPUT);
    pinMode(PinPlus,OUTPUT);
    digitalWrite(PinPlus,HIGH);
} 
void loop () 
{ 
	  //while(1) 
	  //{ 
	    Serial.println(analogRead(PinS)); 
	    //Serial.print('\n'); 
	  //} 
}  
