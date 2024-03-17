# Libraries and objects

A number of libraries we've made in order to control all the components of any vehicle. All of these are written in C/C++ for the Raspberry Pi Pico and its variations.

## shiftReg

SN74HC959N Shift register controller. It should be compatible with most if not all 959 series (Serial-To-Parallel) shift registers

## steps

Stepper control via STSPIN820 board/controller. It should be compatible with most if not all A4988-like stepper motor drivers

It does NOT *yet* have "Mode" control (full step, half step, quarter step...) as our use-case deals with this with hard-wired and jumper-based connections.
