//v1.0
//2024-06-07

#include "SHIFTREG.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "cstdio"

SHIFTREG::SHIFTREG(uint8_t dataPin, uint8_t latchPin, uint8_t clkPin)
{
  this -> dataPin = dataPin;
  this -> latchPin = latchPin;
  this -> clkPin = clkPin;
}

void SHIFTREG::sendTheThing(uint8_t data) {
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
  //Pin 14 on the iC
  //uint8_t dataPin = 18;
  //Pin 12 on the iC
  //uint8_t latchPin = 19;
  //Pin 11 on the iC
  //uint8_t clkPin = 20;
  
  //Debug:
  const uint LED_PIN = PICO_DEFAULT_LED_PIN;
                
  uint8_t bits[8] = {0,0,0,0,0,0,0,0};
  
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  
  gpio_init(dataPin);
  gpio_init(latchPin);
  gpio_init(clkPin);
  
  gpio_set_dir(dataPin, GPIO_OUT);
  gpio_set_dir(latchPin, GPIO_OUT);
  gpio_set_dir(clkPin, GPIO_OUT);
  
  gpio_put(LED_PIN, 1);
  
  printf("Input data: %d\n");
  
  gpio_put(latchPin, 0);
  
  for(uint8_t j = 0; j<8; j++){
  
    // 1 << (i%8)  <- That's a mask
    
    // We and the mask and the data byte together
    // The last >>(i%8) shifts the bit to the least significant bit of a byte in the bits[] array.
    // The smallest variable we can make is a byte!
    
    bits[j] = ((1 << (j%8)) & (data))>>(j%8);
  }
  
  for(uint8_t i = 0; i<8; i++){
  
    gpio_put(dataPin, bits[i]);
    
    gpio_put(clkPin, 1);
    gpio_put(clkPin,0); 
  }
  gpio_put(latchPin, 1);
  gpio_put(LED_PIN, 0);
  
#endif
}
