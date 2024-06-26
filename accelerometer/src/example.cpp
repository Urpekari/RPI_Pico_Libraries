#include <stdio.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "ACCELEROMETER.h"

int main(){
  
  printf("Hello world!\n");
  
  stdio_init_all();

  
  ACCELEROMETER accel(1, 26, 27);
  
  while(1){
    printf("Roll:%.2f Pitch:%.2f\n",accel.getRoll(),accel.getPitch());
    sleep_ms(200);
  }
  
  return(0);
}
