// const int RESET_BUTTON_PIN = 0 or 2; // RST button pin
const int FLASH_BUTTON_PIN = 0; // FLASH button pin

void setup() {
  // pinMode(RESET_BUTTON_PIN, INPUT_PULLUP); // Set RESET button pin as input with internal pull-up resistor
  pinMode(FLASH_BUTTON_PIN, INPUT_PULLUP); // Set FLASH button pin as input with internal pull-up resistor
  pinMode(2,OUTPUT); // In-built LED
  Serial.begin(115200);
}

void loop() {
  // Read the state of the buttons
  // int resetButtonState = digitalRead(RESET_BUTTON_PIN);
  int flashButtonState = digitalRead(FLASH_BUTTON_PIN);

  // Check if the reset button is pressed
  // if (resetButtonState == LOW) {
  //   Serial.println("Reset button pressed");
  //   // Perform reset action here
  // }

  // Check if the flash button is pressed
  if (flashButtonState == LOW) {
    Serial.println("Flash button pressed");
    digitalWrite(2,HIGH);
    // Perform flash mode action here
  } else {
    digitalWrite(2,LOW);
  }

  delay(100); // Add a small delay to debounce buttons
}
