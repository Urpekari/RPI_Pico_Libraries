#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "ADS.h"

int main(void){
  
  stdio_init_all();
  ADS ads(i2c0, 5, 4);
  
  uint8_t chan = 0;
  
  while(1){

    printf("%12d\t", ads.readChannel(chan));
    
    chan++;
    if(chan > 3){
      chan = 0;
      printf("\n");
    }
  
  }
  return 0;
}

