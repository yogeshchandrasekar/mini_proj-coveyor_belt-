# Conveyor Belt Automation System

## Overview

An embedded systems project developed using the **LPC2129 ARM7 microcontroller** to control and automate a conveyor belt system.

The system uses a 4×4 matrix keypad for user input, an LCD for displaying system information, and a DC motor with a motor driver circuit to control conveyor belt movement. An IR sensor detects and counts objects passing through the conveyor belt. A SIM800C GSM module enables SMS communication, while an external interrupt provides an emergency shutdown mechanism.

## Features

- **Keypad Interface:** Allows users to provide input and control conveyor operations.
- **LCD Display:** Displays project information and operating status.
- **DC Motor Control:** Controls conveyor belt movement using a motor driver.
- **IR-Based Object Counting:** Detects objects passing through the conveyor belt and maintains the object count.
- **Emergency Stop:** External interrupt-based mechanism to immediately stop conveyor motor operation.
- **GSM Communication:** Uses the SIM800C module for SMS communication.
- **UART Communication:** Enables serial communication between the LPC2129 microcontroller and GSM module.

## Hardware Components

- LPC2129 ARM7 Microcontroller
- DC Motor
- Motor Driver Module
- IR Sensor
- 4×4 Matrix Keypad
- 16×2 LCD Display
- SIM800C GSM Module
- Power Supply
- Supporting electronic components

## Software & Development Tools

- Embedded C
- Keil µVision IDE
- Proteus Design Suite (Simulation)
- UART Serial Communication
- ARM7 LPC2129

## System Working Principle

1. The microcontroller initializes the required peripherals and interfaces.
2. The LCD displays the project title and startup information.
3. The user provides input through the 4×4 matrix keypad.
4. The microcontroller processes the input and controls the conveyor belt motor.
5. The IR sensor detects objects passing through the conveyor belt and updates the object count.
6. The GSM module handles SMS communication through UART.
7. An external interrupt provides an emergency shutdown mechanism by disabling the motor operation.

## Microcontroller Peripherals Used

- **GPIO:** Motor control and peripheral interfacing.
- **UART:** Serial communication with the SIM800C GSM module.
- **External Interrupt:** Emergency stop mechanism.
- **GPIO-Based Keypad Interfacing:** User input through the matrix keypad.
- **LCD Interfacing:** Displays system information and status.
- **GPIO-Based IR Sensor Interfacing:** Object detection and counting.

## Future Improvements

- Implement automated object sorting.
- Develop real-time conveyor monitoring.
- Integrate advanced sensor-based product tracking.
- Add wireless monitoring and control.

Developed as an embedded systems project using the LPC2129 ARM7 microcontroller.
