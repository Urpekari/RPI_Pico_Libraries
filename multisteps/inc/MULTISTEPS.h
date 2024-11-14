//v1.0
//2024-11-13

#ifndef __MULTISTEPS_H_
#define __MULTISTEPS_H_

#include "hardware/gpio.h"
#include "SHIFTREG.h"

class MULTISTEPS

//TODO: We may need 32 bit variables - I don't know how many steps it'll take for the motor to cover the whole 

{
  private:  //VARS
  uint8_t stepClk;
  uint16_t *currentStep;
  uint16_t *totalSteps;
  uint8_t *limitSwitchPin;
  SHIFTREG shiftreg;

  public:   //VARS
  
  //My hope is that I can use this struct from outside the class.
  struct motorPins{
    uint8_t motEnPin;
    uint8_t motDirPin;
    uint8_t limitSwtichPin;
    //Limit switch pin pulled up when TRUE, pulled down when FALSE
    bool limitSwitchPullUpDown;
  };

  private:  //FUNCS

  public:   //FUNCS
  
  //Initialisation
  uint16_t home(uint8_t motNum);
  
  //For semi-auto handling. These should be pretty rarely used.
  uint8_t step(uint8_t motNum, uint16_t targetSteps);
  
  //This one is the practical function.
  uint16_t stepTo(uint8_t motNum, uint16_t targetPos);
  
  //Calls stepTo(0xFFFF);
  uint8_t max(uint8_t motNum);
  
  //Calls stepTo(0x0000);
  uint8_t min(uint8_t motNum);

  
  public:   //CONSTRUCTORS
  
  //each axis has its own limit switch.
  //Despite assigning every motor a step clock pin, we can handle moving multiple motors together later.
  MULTISTEPS(uint8_t motorNumber, uint8_t limitSwitch, uint8_t stepClk, struct motorPins* motorPinSettings);
};

#endif
