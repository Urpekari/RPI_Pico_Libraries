//v1.0
//2024-11-13

#include "pico/stdlib.h"
#include "SHIFTREG.h"
#include "MULTISTEPS.h"

#define dataPin 18
#define latchPin 19
#define clkPin 20

//Limit-switch constructor. This will initialise one of up to 4 motors.
MULTISTEPS::MULTISTEPS(uint8_t motorNumber, uint8_t limitSwitch, uint8_t stepClk, struct motorPins* motorPinSettings)
{
  shiftreg = SHIFTREG(dataPin, latchPin, clkPin);
  
}

//Homing sequence, it will get to a limit switch, then to the other.
uint8_t MULTISTEPS::home(uint8_t motNum){
  return 0;
};


//This one is the practical function.
uint8_t MULTISTEPS::stepTo(uint8_t motNum, uint16_t targetPos){
  uint16_t targetStepNumber = ((targetPos * this.totalSteps) / 0xFFFF);
  return 0;
}


//Specialised pre-programmed step functions. Just in case.
uint8_t MULTISTEPS::min(uint8_t motNum){
  return stepTo(motNum, 0x0000);
}

uint8_t MULTISTEPS::max(uint8_t motNum){
  return stepTo(motNum, 0xFFFF);
}


