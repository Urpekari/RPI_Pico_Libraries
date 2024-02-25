#include "pico/stdlib.h"
#include "SHIFTREG.h"

int main(){

  #ifndef PICO_DEFAULT_LED_PIN
  #warning blink example requires a board with a regular LED
  #else

  //Debug:
  const uint LED_PIN = PICO_DEFAULT_LED_PIN;
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  SHIFTREG shift(18, 19, 20);
  
  shift.sendTheThing();

  #endif

}
