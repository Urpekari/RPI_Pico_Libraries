# Libraries and objects

A number of libraries we've made in order to control all the components of any vehicle. All of these are written in C/C++ for the Raspberry Pi Pico and its variations.

## Http-webserver
Webserver using the lwIP stack for Raspberry Pi Pico W.

## press
Reads temperature and pressure data from a [Sensor Name] sensor via I²C.

## servo
Basic servo motor controller, 50Hz PWM signal generator that takes a value 0-255 to represent angles 0-180 on a regular servo motor.

## shiftReg

SN74HC959N Shift register controller. It should be compatible with most if not all 959 series (Serial-To-Parallel) shift registers

## steps

Stepper control via STSPIN820 board/controller. It should be compatible with most if not all A4988-like stepper motor drivers

*NOTE: It does NOT *yet* have "Mode" control (full step, half step, quarter step...) as our use-case deals with this via hard-wired and jumper-based connections.*
