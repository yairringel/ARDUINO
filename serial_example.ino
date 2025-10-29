/*
  Serial Communication Example
  This program demonstrates basic serial communication with Arduino.
  It reads input from the serial monitor and echoes it back.
*/

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // Wait for serial port to connect (needed for native USB port only)
  while (!Serial) {
    ; // wait for serial port to connect
  }
  
  Serial.println("Arduino Serial Communication Example");
  Serial.println("Type something and press Enter:");
}

void loop() {
  // Check if data is available to read
  if (Serial.available() > 0) {
    // Read the incoming string
    String incomingMessage = Serial.readString();
    
    // Remove any whitespace/newlines
    incomingMessage.trim();
    
    // Echo the message back
    Serial.print("You sent: ");
    Serial.println(incomingMessage);
    Serial.println("Type something else:");
  }
}