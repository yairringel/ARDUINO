#include <Arduino.h>
#include <Bounce2.h>
#include <AccelStepper.h>

/*
  Stepper Motor Control - STATE MACHINE ARCHITECTURE
  
  Hardware Setup:
  - Button: Pin 2 to one side, GND to other side
  - Joystick: A1 to signal, 5V to VCC, GND to GND
  - Stepper Driver: Pin 10 (step), Pin 8 (direction)
  
  States:
  - IDLE: Waiting for input
  - BUTTON_JOG: Button pressed, motor jogging reverse
  - RETURNING: Button released, motor returning 100 steps
  - JOYSTICK_CONTROL: Joystick moved, motor following joystick
*/

// ==================== PIN DEFINITIONS ====================
const int BUTTON_PIN = 2;
const int STEP_PIN = 10;
const int DIR_PIN = 8;
const int JOYSTICK_PIN = A1;
//333
// ==================== CONFIGURATION ====================
const int JOYSTICK_DEADBAND = 150;      // Deadband around center (512)
const int JOYSTICK_CENTER = 512;        // Center position of joystick
const int BUTTON_JOG_SPEED = -400;      // Speed when button pressed (negative = reverse)
const int RETURN_STEPS = 500;           // Steps to return after button release
const int MAX_JOYSTICK_SPEED = 4000;    // Maximum speed for joystick control
const int MAX_SPEED = 4000;             // Maximum stepper speed
const int ACCELERATION = 20000;           // Acceleration for position movements

// ==================== STATE DEFINITIONS ====================
enum State {
  IDLE,
  BUTTON_JOG,
  RETURNING,
  JOYSTICK_CONTROL
};

// ==================== GLOBAL OBJECTS ====================
Bounce2::Button button = Bounce2::Button();
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// ==================== STATE VARIABLES ====================
State currentState = IDLE;
State previousState = IDLE;
int joystickValue = 512;

// ==================== SETUP ====================
void setup() {
  Serial.begin(9600);
  Serial.println("==================================");
  Serial.println("Stepper Motor State Machine Control");
  Serial.println("==================================");
  Serial.println("Button on Pin 2: Jog reverse, auto-return 100 steps");
  Serial.println("Joystick on A1: Variable speed CW/CCW");
  Serial.println("Deadband: +/- 100 around center");
  Serial.println("==================================");
  
  // Configure button
  button.attach(BUTTON_PIN, INPUT_PULLUP);
  button.interval(15);
  button.setPressedState(LOW);
  
  // Configure stepper
  stepper.setMaxSpeed(MAX_SPEED);
  stepper.setAcceleration(ACCELERATION);
  
  Serial.println("State: IDLE - Ready for input");
}

// ==================== STATE MACHINE FUNCTIONS ====================

void enterState(State newState) {
  // Exit current state
  switch (currentState) {
    case BUTTON_JOG:
      stepper.setSpeed(0);
      break;
    case JOYSTICK_CONTROL:
      stepper.setSpeed(0);
      break;
    default:
      break;
  }
  
  // Update state
  previousState = currentState;
  currentState = newState;
  
  // Enter new state
  switch (newState) {
    case IDLE:
      Serial.println("State: IDLE - Waiting for input");
      stepper.setSpeed(0);
      break;
      
    case BUTTON_JOG:
      Serial.println("State: BUTTON_JOG - Jogging reverse");
      stepper.setSpeed(BUTTON_JOG_SPEED);
      break;
      
    case RETURNING:
      Serial.print("State: RETURNING - Moving ");
      Serial.print(RETURN_STEPS);
      Serial.println(" steps forward");
      stepper.move(RETURN_STEPS);
      break;
      
    case JOYSTICK_CONTROL:
      Serial.println("State: JOYSTICK_CONTROL - Following joystick");
      break;
  }
}

void handleIdleState() {
  // Check for button press
  if (button.pressed()) {
    enterState(BUTTON_JOG);
    return;
  }
  
  // Check for joystick movement
  if (abs(joystickValue - JOYSTICK_CENTER) > JOYSTICK_DEADBAND) {
    enterState(JOYSTICK_CONTROL);
    return;
  }
}

void handleButtonJogState() {
  // Run motor at constant speed
  stepper.runSpeed();
  
  // Check for button release
  if (button.released()) {
    enterState(RETURNING);
    return;
  }
}

void handleReturningState() {
  // Run position-based movement
  stepper.run();
  
  // Check if return is complete
  if (stepper.distanceToGo() == 0) {
    Serial.println("Return complete");
    enterState(IDLE);
    return;
  }
  
  // Button press during return is ignored
  // This prevents interruption of safety return movement
}

void handleJoystickControlState() {
  // Calculate speed based on joystick position
  int speed = 0;
  
  if (joystickValue < (JOYSTICK_CENTER - JOYSTICK_DEADBAND)) {
    // CW direction (0 to center-deadband)
    speed = map(joystickValue, 0, JOYSTICK_CENTER - JOYSTICK_DEADBAND, 
                MAX_JOYSTICK_SPEED, 0);
  } 
  else if (joystickValue > (JOYSTICK_CENTER + JOYSTICK_DEADBAND)) {
    // CCW direction (center+deadband to 1023)
    speed = map(joystickValue, JOYSTICK_CENTER + JOYSTICK_DEADBAND, 1023, 
                0, -MAX_JOYSTICK_SPEED);
  }
  
  stepper.setSpeed(speed);
  stepper.runSpeed();
  
  // Check if joystick returned to center
  if (abs(joystickValue - JOYSTICK_CENTER) <= JOYSTICK_DEADBAND) {
    enterState(IDLE);
    return;
  }
  
  // Check for button press (overrides joystick)
  if (button.pressed()) {
    enterState(BUTTON_JOG);
    return;
  }
}

// ==================== MAIN LOOP ====================
void loop() {
  // Update inputs
  button.update();
  joystickValue = analogRead(JOYSTICK_PIN);
  
  // Run state machine
  switch (currentState) {
    case IDLE:
      handleIdleState();
      break;
      
    case BUTTON_JOG:
      handleButtonJogState();
      break;
      
    case RETURNING:
      handleReturningState();
      break;
      
    case JOYSTICK_CONTROL:
      handleJoystickControlState();
      break;
  }
  
  // Small delay for stability
  delayMicroseconds(100);
}