# Arduino Project with VS Code

This project contains several Arduino examples to help you get started with Arduino development in VS Code.

## Prerequisites

1. **Arduino IDE** - Download and install from [arduino.cc](https://www.arduino.cc/en/software)
2. **VS Code Extensions** - Already installed:
   - PlatformIO IDE
   - Arduino Community Edition

## Project Files

### 1. `blink_example.ino`
- Classic "Hello World" of Arduino
- Blinks the built-in LED every second
- No additional hardware required

### 2. `serial_example.ino`
- Demonstrates serial communication
- Open Serial Monitor to interact with Arduino
- Type messages and see responses

### 3. `button_led_example.ino`
- Reads button input and controls LED
- **Hardware needed:**
  - Push button connected to pin 2
  - LED connected to pin 13 (or use built-in LED)
  - Optional: 10kΩ resistor for button (code uses internal pull-up)

## How to Upload Code to Arduino

### Method 1: Using Arduino Community Extension

1. Open any `.ino` file
2. Connect your Arduino board via USB
3. Press `Ctrl+Shift+P` to open Command Palette
4. Type "Arduino: Upload" and select it
5. Choose your board type and COM port when prompted

### Method 2: Using PlatformIO

1. Press `Ctrl+Shift+P`
2. Type "PlatformIO: Initialize or Update PlatformIO Project"
3. Follow the setup wizard to configure your board
4. Use PlatformIO's build and upload features

## Quick Start Steps

1. **Connect Arduino**: Plug your Arduino board into your computer via USB
2. **Select Board**: In VS Code, select your Arduino board type (Uno, Nano, etc.)
3. **Select Port**: Choose the correct COM port for your Arduino
4. **Open Example**: Open one of the `.ino` files
5. **Upload**: Use the upload command to send code to your Arduino
6. **Monitor**: Open Serial Monitor to see output (if applicable)

## Troubleshooting

- **Can't find COM port**: Make sure Arduino drivers are installed
- **Upload fails**: Check that the correct board and port are selected
- **Code errors**: Verify syntax and that required libraries are installed

## Next Steps

- Modify the existing examples
- Add sensors and actuators
- Create your own projects
- Explore Arduino libraries

Happy coding with Arduino and VS Code!