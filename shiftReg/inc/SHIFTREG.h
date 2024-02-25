#ifndef __SHIFTREG_H_
#define __SHIFTREG_H_

#include "hardware/gpio.h"

class SHIFTREG
{

private: //Vars
  uint8_t dataPin;
  uint8_t latchPin;
  uint8_t clkPin;
  
  uint8_t nextByte;

public:  //Vars

private: //Funcs

public:  //Funcs
  void sendTheThing();


public:  //Constructor
  SHIFTREG(uint8_t dataPin, uint8_t latchPin, uint8_t clkPin);
  //~SHIFTREG();

};

#endif
