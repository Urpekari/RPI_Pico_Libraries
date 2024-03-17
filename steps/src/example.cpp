#include "pico/stdlib.h"
#include "STEPS.h"

int main(){

  #ifndef PICO_DEFAULT_LED_PIN
  #warning blink example requires a board with a regular LED
  #else

  //Debug:
  const uint LED_PIN = PICO_DEFAULT_LED_PIN;
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  STEPS stepper(13, 14, 15, 1);
  
  while(true){
    
    for(int i = 0; i<1024; i++){

      if(i == 511){
        stepper.setDir(false);
      }
      else if(i == 1023){
        i = 0;
        stepper.setDir(true);
      }
      
      stepper.step();
    }    
  }
  #endif

}
