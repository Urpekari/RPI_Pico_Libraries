//v0 - TESTING
//2024-06-07

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"


//Prototypes
void readJoy(uint8_t* buffer, uint8_t* addresses);
void drawRGB(uint8_t channel, uint8_t intensity);

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

  uint8_t joyPos[4];
  uint8_t addresses[4] = {LXAddr, LYAddr, RXAddr, RYAddr};

  uint8_t buffer;

  stdio_init_all();
  
  i2c_init(i2c1, 400*1000);
  
  gpio_set_function(26, GPIO_FUNC_I2C);
  gpio_set_function(27, GPIO_FUNC_I2C);
  gpio_pull_up(26);
  gpio_pull_up(27);
  
  while(true){
  
    readJoy(joyPos, addresses);
    drawRGB(0, 255);
    printf("Received: %d %d %d %d \n", joyPos[0], joyPos[1], joyPos[2], joyPos[3]);
    
  }
  return(0);
}

void readJoy(uint8_t* buffer, uint8_t* addresses){
  for(int i = 0; i<4; i++){
    i2c_write_blocking(i2c1, I2Caddr, (addresses + i), sizeof(uint8_t), false);
    i2c_read_blocking(i2c1, I2Caddr, (buffer + i), sizeof(uint8_t), false);
    sleep_ms(50);    
  }
  
}

//Working, it seems to illuminate only in the direction the joystick in pointing to

void drawRGB(uint8_t channel, uint8_t intensity){

  uint8_t rgb = 0x20;
  
  uint8_t rgbVal[4];
  //First element provides the destination address
  rgbVal[0]=rgb;
  rgbVal[channel] = intensity;
  //Extra, changes the remaining channels to 0 in order to see only either red, green or blue. Mixing colours will require this function to be deactivated
  for(int i=1;i<=4;i++){
    if(i!=channel){
         rgbVal[i] = 0;
    }
  }
  printf("%d %d %d \n", rgbVal[1], rgbVal[2], rgbVal[3]);
  i2c_write_blocking(i2c1, I2Caddr, rgbVal, 4, false);

}
