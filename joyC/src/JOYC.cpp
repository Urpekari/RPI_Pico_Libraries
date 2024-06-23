//v1.2
//2024-06-23

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include <JOYC.h>

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
  #define LRAddr 0x72
  #define RPAddr 0x74
  #define RRAddr 0x76

  //Auxiliary buttons: 
  #define PBAddr 0x64
  
  /*
    Connections:
    For i2c1
    JoyC Pin 6 (G26) to Raspberry Pi Pico I2C1 SCL (GP27)
    JoyC Pin 5 (G36) to Raspberry Pi Pico I2C1 SDA (GP26)
  */

  JOYC::~JOYC(){
  }
  
  //SCL = GPIO 26
  //SDA = GPIO 27
  
  JOYC::JOYC(uint8_t i2c, uint8_t SCL, uint8_t SDA){
  //Initialising 
    gpio_set_function(SCL, GPIO_FUNC_I2C);
    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_pull_up(SCL);
    gpio_pull_up(SDA);
  
    //TODO: GET THIS TO SWITCH I2C BUSES BASED ON THE i2c VARIABLE
    i2c_init(i2c1, 400*1000);
  }
  
  //Cute little silly lights
  
  //Literally the map function in arduino with fewer steps
  uint8_t JOYC::colorRamp(uint8_t potValIn){

    //potValIn        : The input value we want to convert
    //in_min          : Lower limit of all possible inputs
    //in_max          : Upper limit of all possible inputs
    //this->min       : Lower limit of the desired outputs
    //this->max       : Upper limit of the desired outputs
    
    int8_t cleanPos = potValIn-100;
    uint8_t absPos;
    
    if(cleanPos < 0){
      absPos = -cleanPos;
    }
    else{
      absPos = cleanPos;
    }
    
    uint8_t out_min = 0;
    uint8_t out_max = 255;
    uint8_t in_min = 0;
    uint8_t in_max = 200;

    return( (absPos - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}
  
  //X axis: Red (Yaw)
  //Y axis: Green (Forward/Backward motion)
  //Z Axis: Blue (Depth)
  void JOYC::xyzGradient(){
    drawRGB(colorRamp(cartesian.Left0), colorRamp(cartesian.Left1), colorRamp(cartesian.Right1));	
  }
  
  void JOYC::drawRGB(uint8_t red, uint8_t green, uint8_t blue){
    uint8_t rgbVal[4];
    i2c_read_blocking(i2c1, I2Caddr, rgbVal, 4, false);
    
    rgbVal[0] = rgbAddr;
    
    //By leaving a value input as null we leave the intensity for that colour as-is
    if(red != NULL){
      rgbVal[1] = red;
    }
    else if(red < 25){
      rgbVal[1] = 0;
    }
    if(green != NULL){
      rgbVal[2] = green;
    }
    else if(green < 25){
      rgbVal[2] = 0;
    }
    if(blue != NULL){
      rgbVal[3] = blue;
    }
    else if(blue < 25){
      rgbVal[3] = 0;
    }
    
    i2c_write_blocking(i2c1, I2Caddr, rgbVal, 4, false);
  }
  
  //Actual functionality
  void JOYC::update(bool type){
    if(type==false){
        uint8_t buffer[9];
        for(int i = 0; i<9; i++){
          i2c_write_blocking(i2c1, I2Caddr, (addresses + i), sizeof(uint8_t), false);
          i2c_read_blocking(i2c1, I2Caddr, (buffer + i), sizeof(uint8_t), false); 
        }
        
        // Update the cartesian interpretation
        cartesian.Left0 = buffer[0];
        cartesian.Left1 = buffer[1];
        cartesian.Right0 = buffer[2];
        cartesian.Right1 = buffer[3];
        
        //Update buttons every time, it's just easier and cleaner than checking all buttons
        cartesian.RButton = 0;
        cartesian.LButton = 0;

        if(buffer[8] & 0x01){
          cartesian.RButton = 1;
        }
        if(buffer[8] & 0x10){
          cartesian.LButton = 1;
        }
        
        //This enables the basic gradient with 3 axis for the LEDs and one useless axis
        xyzGradient();
    
    }else{
        uint16_t polar_buffer[4];
        uint8_t tmp[2], button; 
        for(int i = 4; i<8; i++){
          i2c_write_blocking(i2c1, I2Caddr, (addresses + i), sizeof(uint8_t), false);
          i2c_read_blocking(i2c1, I2Caddr,tmp,2*sizeof(uint8_t), false);
          polar_buffer[(i-4)] = tmp[0] << 8 | tmp[1];
        }
        i2c_write_blocking(i2c1, I2Caddr,&addresses[8], sizeof(uint8_t), false);
        i2c_read_blocking(i2c1, I2Caddr,&button,sizeof(uint8_t), false);

        //Update buttons every time, it's just easier and cleaner than checking all buttons
        polar.RButton = 0;
        polar.LButton = 0;

        if(button & 0x01){
         polar.RButton = 1;
        }
        if(button & 0x10){
         polar.LButton = 1;
        }

        // Update the polar interpretation
        polar.LAngle = polar_buffer[0];
        polar.RAngle = polar_buffer[1];
        polar.LRadius = polar_buffer[2];
        polar.RRadius = polar_buffer[3];
        }
  }
  
  outputs JOYC::getCartesian(){
    update(0);
    return cartesian;
  }
  
  outputs JOYC::getPolar(){
    update(1);
    return polar;
  }
