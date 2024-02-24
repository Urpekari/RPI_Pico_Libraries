#include "pico/stdlib.h"

int main() {
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
  //Pin 14 on the iC
  uint8_t dataPin = 18;
  //Pin 12 on the iC
  uint8_t latchPin = 19;
  //Pin 11 on the iC
  uint8_t clkPin = 20;
  
  //Debug:
  const uint LED_PIN = PICO_DEFAULT_LED_PIN;
  
  //TODO: Replace with actual things
  uint8_t bitValue = 0;
  
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  
  gpio_init(dataPin);
  gpio_init(latchPin);
  gpio_init(clkPin);
  
  gpio_set_dir(dataPin, GPIO_OUT);
  gpio_set_dir(latchPin, GPIO_OUT);
  gpio_set_dir(clkPin, GPIO_OUT);
  
  //while (true) {
  //    gpio_put(LED_PIN, 1);
  //    sleep_ms(250);
  //    gpio_put(LED_PIN, 0);
  //    sleep_ms(250);
  //}
  
  while(true){
  
//    gpio_put(LED_PIN, 1);
//    sleep_ms(250);
//    gpio_put(LED_PIN, 0);
//    sleep_ms(250);
  
    sleep_ms(200);
    gpio_put(LED_PIN, 1);
    
    if(bitValue == 0){
      bitValue = 1;
    }
    else{
      bitValue = 0;
    }
    
    gpio_put(latchPin, 0);
    for(uint8_t i = 0; i<8; i++){
      //TODO: REMOVE WHEN ACTUAL THINGS ARE IMPLEMENTED! REPLACE WITH "READ NEXT BIT"
      if(bitValue == 0){
        bitValue = 1;
      }
      else{
        bitValue = 0;
      }
      //TODO: **ABOVE** REMOVE WHEN ACTUAL THINGS ARE IMPLEMENTED! REPLACE WITH "READ NEXT BIT"

      gpio_put(dataPin, bitValue);
      
      sleep_ms(50);
      gpio_put(clkPin, 1);
      sleep_ms(50);
      gpio_put(clkPin,0); 
    }
    gpio_put(latchPin, 1);
    
    sleep_ms(200);
    gpio_put(LED_PIN, 0);
  
  }
  
#endif
}
