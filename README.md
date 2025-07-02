# Embedded morse
The code we were mainly working on is in the `src` directory. The entry point is `project_main_notog.c`.

## Technologies used
- C language for the embedded programming
- UART and i2c for the communication
- SensorTag from Texas Instruments (MPU sensor utilized in the project)
- TI-RTOS

## Overview
The project was completed as part of a university course in embedded systems and real-time operating systems. We were posted a challenge to develop a communication device that allows sending messages with hidden interactions using SensorTag. 
Once finished, our device could recognize different hand movements by acceleration and send different characters or messages based on that. It was also receiving the Morse and playing it with sound. We have also added a feature of music playing once the mode of operation is switched.

## Learning outcomes
- Real-time programming with TI-RTOS
- Sensor input handling and gesture recognition
- UART communication protocol
- Embedded systems debugging and testing
