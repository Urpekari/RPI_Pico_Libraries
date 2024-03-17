#ifndef __STEPS_H_
#define __STEPS_H_

#include "hardware/gpio.h"

class STEPS
{
  private:  //VARS
  uint8_t stepperEnablePin;
  uint8_t stepperStepClkPin;
  uint8_t stepperStepDirPin;
  
  //In ms. Setting this to values between 2 and 5 yields the best results for the NEMA11s
  uint8_t stepLength;
  
  bool stepperEnable;
  bool stepClkState;
  bool stepDirState;

  public:   //VARS

  private:  //FUNCS
  bool togglePin(uint8_t pin, bool pinState);
  void fullInit(void);
  void partInit(void);

  public:   //FUNCS
  void step(void);
  void stop(void);
  void start(void);
  void setDir(bool dirTarget);

  public:   //CONSTRUCTOR
  //For single-motor controls
  STEPS(uint8_t stepperEnablePin, uint8_t stepperStepClkPin, uint8_t stepperStepDirPin, uint8_t stepLength);
  
  //For multiple-motor control. You only really get access to the clock here, the rest should be handled by the shift register!
  STEPS(uint8_t stepperStepClkPin, uint8_t stepLength);
  
  //~SHIFTREG();
};

#endif
