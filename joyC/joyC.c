//v0 - TESTING
//2024-06-07

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

//I2C address
#define I2Caddr 0x38

//Memory addresses within the module

  //Decorative RGB LEDs:
  #define rgbAddr 0x20

  //Joysticks: Cartesian coordinates (X = Horizontal, Y = Vertical)
  #define LXAddr 0x60
  #define LYAddr 0x61
  #define RXAddr 0x62
  #define RYAddr 0x63
  
  //Joysticks: Polar coordinates (P = Angle, R = Radius)
  #define LPAddr 0x70
  #define LRAddr 0x71
  #define RPAddr 0x72
  #define RRAddr 0x73

  //Auxiliary buttons: 
  #define PBAddr 0x64

  /*
  Connections:
    JoyC Pin 6 (G26) to Raspberry Pi Pico I2C1 SCL (GP27)
    JoyC Pin 5 (G36) to Raspberry Pi Pico I2C1 SDA (GP26)
  */

int main(){

  uint8_t buffer;

  stdio_init_all();
  
  i2c_init(i2c1, 400*1000);
  
  gpio_set_function(26, GPIO_FUNC_I2C);
  gpio_set_function(27, GPIO_FUNC_I2C);
  gpio_pull_up(26);
  gpio_pull_up(27);
  
  while(true){
  
    buffer = LXAddr;
    i2c_write_blocking(i2c1, I2Caddr, &buffer, sizeof(buffer), false);
    printf("Sent: %d\t", buffer);
    i2c_read_blocking(i2c1, I2Caddr, &buffer, sizeof(buffer), false);
    printf("Received: %d \n", buffer);
    
    sleep_ms(250);
  }
  
  return(0);
}
