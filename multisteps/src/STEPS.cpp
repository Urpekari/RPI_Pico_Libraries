//v1.1
//2024-06-07

#include "pico/stdlib.h"
#include "STEPS.h"
//Full constructor for when we need just one stepper motor and to control it directly
STEPS::STEPS(uint8_t stepperEnablePin, uint8_t stepperStepClkPin, uint8_t stepperStepDirPin, uint8_t stepLength)
{
  this -> stepperEnablePin = stepperEnablePin;
  this -> stepperStepClkPin = stepperStepClkPin;
  this -> stepperStepDirPin = stepperStepDirPin;
  this -> stepLength = stepLength;
  
  fullInit();
}

void STEPS::fullInit(){
    gpio_init(stepperEnablePin);
    gpio_set_dir(stepperEnablePin, GPIO_OUT);
    gpio_init(stepperStepClkPin);
    gpio_set_dir(stepperStepClkPin, GPIO_OUT);
    gpio_init(stepperStepDirPin);
    gpio_set_dir(stepperStepDirPin, GPIO_OUT);
    
    //Disables and sets the motor forward by default.
    gpio_put(stepperEnablePin, 1);
    gpio_put(stepperStepDirPin, 1);
}

//Basic constructor for when we use external enable and direction control (like on the glider)
STEPS::STEPS(uint8_t stepperStepClkPin, uint8_t stepLength)
{
  this -> stepperStepClkPin = stepperStepClkPin;
  this -> stepLength = stepLength;
  
  this -> stepperEnablePin = -1;
  this -> stepperStepDirPin = -1;
  
  partInit();
}

//Initializes the clock pin and nothing else. This might cause issues when we have multiple motors... or it might not.
//I think they will just overwrite one another?
//Might be worth looking into.
void STEPS::partInit(void){
    gpio_init(stepperStepClkPin);
    gpio_set_dir(stepperStepClkPin, GPIO_OUT);
}

//Sets the direction of the rotation... pretty self explanatory
void STEPS::setDir(bool dirTarget){
  if(stepperStepDirPin >0){
    gpio_put(stepperStepDirPin, dirTarget);
  }
}

//Nothing in the documentation says I can't use get on an output pin
bool STEPS::getDir(){
  return(gpio_get(stepperStepDirPin));
}

//Pulls the enable pin HIGH -> Prevents the motor from moving.
void STEPS::stop(void){
  if(stepperEnablePin >0){
    gpio_put(stepperEnablePin, 1);
  }
}

//Pulls the enable pin LOW -> Allows the motor to move.
void STEPS::start(void){
  if(stepperEnablePin >0){
    gpio_put(stepperEnablePin, 0);
  }
}

void STEPS::step(void){
  gpio_put(stepperStepClkPin, 0);
  
  gpio_put(stepperStepClkPin, 1);
  //TODO: USE TIMERS INSTEAD OF HYJACKING THE CPU
  sleep_ms(stepLength);
  
  gpio_put(stepperStepClkPin, 0);
}

