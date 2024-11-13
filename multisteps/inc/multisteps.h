//v1.0
//2024-11-13

#ifndef __MULTISTEPS_H_
#define __MULTISTEPS_H_

#include "hardware/gpio.h"

class MULTISTEPS

//TODO: We may need 32 bit variables - I don't know how many steps it'll take for the motor to cover the whole 

{
  private:  //VARS
  uint16_t stepsTaken;
  uint16_t totalSteps;
  uint8_t limitSwitchPin;

  public:   //VARS

  private:  //FUNCS

  public:   //FUNCS
  
  //Initialisation
  uint16_t stepTo(uint16_t targetPos)
  
  //For semi-auto handling. These should be pretty rarely used.
  bool step();
  bool step(uint16_t targetSteps);
  
  //This one is the practical function.
  uint16_t stepTo(uint16_t targetPos)
  
  //Calls stepTo(0xFFFF);
  bool max();
  
  //Calls stepTo(0x0000);
  bool min();

  public:   //CONSTRUCTOR
  //each axis has its own limit switch.
  MULTISTEPS(uint8_t motorNumber, uint8_t limitSwitch);

  //manual range limiter. The starting point is where the motor physically is on boot. Not recommended for production!
  //
  MULTISTEPS(uint8_t motorNumber, uint16_t rangeLimitSteps);

};

#endif
