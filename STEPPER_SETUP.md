# Stepper Motor Control with Button - Arduino Project

## 🎯 **Project Description**
This project controls a stepper motor using a button press. When the button is pressed, the stepper motor moves continuously. When released, it stops smoothly.

## 🔌 **Hardware Connections**

### Button Setup:
- **Pin 2** → One side of button
- **GND** → Other side of button
- Uses internal pull-up resistor (no external resistor needed)

### Stepper Motor Driver Setup:
- **Pin 10** → Step pin on stepper driver
- **Pin 8** → Direction pin on stepper driver
- **5V/12V** → Power supply to stepper driver (check driver specs)
- **GND** → Ground connection
- **Stepper Motor** → Connect to driver outputs (A+, A-, B+, B-)

## 📚 **Libraries Used**
- **Bounce2** v2.71 - For button debouncing
- **AccelStepper** v1.64 - For smooth stepper motor control

## ⚙️ **Motor Settings**
- **Max Speed**: 1000 steps/second
- **Acceleration**: 500 steps/second²
- **Running Speed**: 800 steps/second
- **Direction**: Forward (can be changed by swapping DIR pin logic)

## 🔧 **How to Customize**

### Change Motor Speed:
```cpp
stepper.setMaxSpeed(1500);    // Faster maximum speed
stepper.setSpeed(1200);       // Faster running speed
```

### Change Direction:
```cpp
stepper.move(-100000);  // Negative number = reverse direction
```

### Change Button Debounce Time:
```cpp
button.interval(50);  // 50ms debounce (increase if button is noisy)
```

### Different Stepper Driver Types:
```cpp
// For full step mode (4 pins)
AccelStepper stepper(AccelStepper::FULL4WIRE, pin1, pin3, pin2, pin4);

// For half step mode (4 pins)
AccelStepper stepper(AccelStepper::HALF4WIRE, pin1, pin3, pin2, pin4);
```

## 🛠️ **Troubleshooting**

### Motor Not Moving:
1. Check power supply to stepper driver
2. Verify step and direction pin connections
3. Ensure stepper motor is properly connected to driver
4. Check if driver enable pin needs to be connected

### Button Not Responding:
1. Verify button connection to pin 2 and GND
2. Try increasing debounce interval
3. Check serial monitor for button press messages

### Motor Moving Wrong Direction:
1. Swap the direction pin logic: change `stepper.move(100000)` to `stepper.move(-100000)`
2. Or swap two motor wires

## 📊 **Serial Monitor Output**
```
Stepper Motor Control with Button
Press button to move stepper, release to stop
----------------------------------------
Setup complete. Ready for button input.
Button PRESSED - Starting stepper motor
Button RELEASED - Stopping stepper motor
```

## 💡 **Tips**
- Always power stepper drivers with appropriate voltage (check datasheet)
- Use appropriate current settings on stepper driver
- For high-power steppers, consider heat sinks on drivers
- Test with low speeds first, then increase as needed

## 🚀 **Upload Instructions**
1. Connect Arduino to computer via USB
2. Run: `platformio run --target upload`
3. Open serial monitor: `platformio device monitor --baud 9600`
4. Press button to test!