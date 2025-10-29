/*
  Button and LED Control
  This program demonstrates reading a button input and controlling an LED.
  When the button is pressed, the LED turns on. When released, LED turns off.
*/

// Define pin numbers
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin = 13;       // the number of the LED pin

// Variable to store button state
int buttonState = 0;

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  // Initialize the pushbutton pin as an input with internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println("Button and LED Control Example");
  Serial.println("Press the button to control the LED");
}

void loop() {
  // Read the state of the pushbutton
  buttonState = digitalRead(buttonPin);
  
  // Check if the pushbutton is pressed (LOW when using INPUT_PULLUP)
  if (buttonState == LOW) {
    // Turn LED on
    digitalWrite(ledPin, HIGH);
    Serial.println("Button pressed - LED ON");
  } else {
    // Turn LED off
    digitalWrite(ledPin, LOW);
    Serial.println("Button released - LED OFF");
  }
  
  // Small delay to avoid excessive serial output
  delay(100);
}