#include "pico/stdlib.h"
#include "JOYC.h"

int main(){
  
  printf("Hello world!\n");
  
  stdio_init_all();
  struct outputs test;
  
  JOYC joyc(1, 26, 27);
  
  while(1){
    //test = joyc.getCartesian();
    //printf("Received: %d %d %d %d - %d %d\n", test.Left0, test.Left1, test.Right0, test.Right1, test.LButton, test.RButton);
    test=joyc.getPolar();
    printf("Received: %d %d %d %d - %d %d\n", test.LAngle, test.RAngle, test.LRadius, test.RRadius, test.LButton, test.RButton);
    sleep_ms(20);
  }
  
  return(0);
}
