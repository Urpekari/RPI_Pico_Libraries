# Libraries and objects

A number of libraries we've made in order to control all the components of any vehicle. All of these are written in C/C++ for the Raspberry Pi Pico and its variations.

## Http-webserver
Webserver using the lwIP stack for Raspberry Pi Pico W.

## joyC
Simple driver for joyC dual joystick kits.

We still don't really know how the polar coordinates work, but the cartesian readings and LEDs are working.

Pinout (I2C1 Bus):

![1: 5V (VBUS/VSYS), 2: 3v3 OUT, 3: NO CONNECTION, 4: SDA, 5: NO CONNECTION, 6: SCL, 7: 5V (VBUS/VSYS), 8: GND](https://github.com/Urpekari/RPI_Pico_Libraries/blob/main/joyC/docs/Pinout%20table.png?raw=true)


## press
Reads temperature and pressure data from a [Sensor Name] sensor via I²C.

## servo
Basic servo motor controller, 50Hz PWM signal generator that takes a value 0-255 to represent angles 0-180 on a regular servo motor.

## shiftReg

SN74HC959N Shift register controller. It should be compatible with most if not all 959 series (Serial-To-Parallel) shift registers

## steps

Stepper control via STSPIN820 board/controller. It should be compatible with most if not all A4988-like stepper motor drivers

*NOTE: It does NOT *yet* have "Mode" control (full step, half step, quarter step...) as our use-case deals with this via hard-wired and jumper-based connections.*
