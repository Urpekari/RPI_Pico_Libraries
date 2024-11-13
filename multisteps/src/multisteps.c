//v1.0
//2024-11-13

#include "pico/stdlib.h"
#include "MULTISTEPS.h"
#include "STEPS.h"

//Limit-switch constructor. This will initialise one of up to 4 motors.
MULTISTEPS::MULTISTEPS(uint8_t motorNumber, uint8_t limitSwitch);
{
  stepsTaken = 0;
  totalSteps = 0;
  limitSwitchPin = limitSwitch;
  
}

//Hard-limited range constructor. This will initialise one of up to 4 motors.
MULTISTEPS::MULTISTEPS(uint8_t motorNumber, uint16_t rangeLimitSteps);
{
  stepsTaken = 0;
  totalSteps = rangeLimitSteps;
  limitSwitchPin = NULL;
  
}

//Homing sequence, it will get to a limit switch, then to the other.
MULTISTEPS::home(){

}

