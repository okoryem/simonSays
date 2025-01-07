## Simon Says Tilt and Joystick Raspberry Pi Game

### Overview

This project is a game that leverages a joystick and tilt sensor to interact 
with an 8x8 LED matrix display. The user is prompted to perform specific tilt 
or joystick actions within a time limit, with visual feedback displayed on the 
LED grid. The game is implemented in C and designed to run on a Raspberry Pi 
with the necessary hardware interfaces.

### Features
- Detects joystick movements (up, down, left, right, and press).
- Detects tilt gestures (forward, backward, left, and right).
- Displays feedback on an 8x8 LED matrix using predefined color codes.
- Randomized prompts for user interaction.
- Real-time error handling for hardware interactions.

### Hardware Requirements
- A Raspberry Pi.
- A joystick connected via /dev/input/event4.
- A tilt sensor connected via /dev/i2c-1.
- An 8x8 LED matrix connected via /dev/fb0.

### Software Requirements
- Linux-based system on the Raspberry Pi.
- GCC compiler.
- Libraries:
  - fcntl.h
  - unistd.h
  - linux/input.h
  - linux/i2c-dev.h
  - sys/mman.h
  - stdint.h
  - stdio.h
  - stdlib.h

### Project Structure
- main.c
  - Contains the game loop and orchestrates the game logic.
- input.c
  - Handles joystick and tilt sensor inputs.
- output.c
  - Manages LED matrix display and rendering.
- project.h
  - Header file defining structs, constants, and function prototypes.
- Makefile
  - Automates the build process.

### Game Logic
- A random prompt is generated, either a joystick or tilt action.
- The corresponding symbol is displayed on the LED matrix.
- The user performs the required action.
- The game checks the correctness of the action and provides visual feedback (green for correct, red for incorrect).
- The game continues until the user fails or exits.

### Build Instructions
- Ensure all required libraries are installed.
- Use the provided Makefile to compile the project:
```bash
make all
```
- Run the executable:
```bash
./simonSays
```

### File Descriptions
- main.c
  - Initializes and closes hardware interfaces.
  - Contains the game loop logic and integrates other modules.
- input.c
  - Opens, reads, and closes joystick and tilt sensor inputs.
  - Implements functions like checkJoyInput() and getPosition().
- output.c
  - Controls the LED matrix display.
  - Implements functions like drawSymbol() and checkCorrect() for visual feedback.
- project.h
  - Contains necessary constants, macros, and function prototypes.
- Makefile
  - Defines rules for compiling and cleaning the project:
    - all: Builds the executable.
    - clean: Removes all generated files.
    - run: Executes the program.

### Usage
1. Compile and run the program.
2. Follow the prompts displayed on the LED matrix.
3. Use the joystick or tilt sensor to perform the required actions.
4. Watch for feedback on the LED matrix to determine correctness.

### Known Issues
- Ensure proper permissions for accessing /dev/input/event4, /dev/i2c-1, and /dev/fb0.
- Calibration of tilt sensor might vary based on hardware.

### Future Enhancements
- Add difficulty levels to increase gameplay complexity.
- Support for additional sensors or input methods.
- Improved error handling and diagnostics.
