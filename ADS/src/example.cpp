#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#define I2C_ADDR 0x48

//prototypes
void ads_init(i2c_inst_t *i2c_port, uint8_t resol);
void ads_read_config(i2c_inst_t *i2c_port);
void ads_set_mux(i2c_inst_t* i2c_port, uint8_t channel);
void ads_set_pga(i2c_inst_t * i2c_port, uint8_t resol);
void ads_set_mode(i2c_inst_t* i2c_port, uint8_t mode);
void ads_set_speed(i2c_inst_t* i2c_port, uint8_t speed);
void ads_write_config(i2c_inst_t* i2c_port, uint16_t config);
uint16_t ads_read_channel(i2c_inst_t* i2c_port, uint8_t channel);

//Hard-coded pointers
const uint8_t config_ptr = 0x01;
const uint8_t conver_ptr = 0x00;

//Global variables
uint16_t config = 0;

int main(){

  stdio_init_all();
  
  gpio_set_function(4, GPIO_FUNC_I2C);
  gpio_set_function(5, GPIO_FUNC_I2C);
  gpio_pull_up(4);
  gpio_pull_up(5);

  sleep_ms(1000);
  printf("===== ===== ===== =====\n");

  ads_init(i2c0, 4);
  
  uint8_t chan = 0;
  
  while(1){
    ads_read_config(i2c0);
    uint16_t result = ads_read_channel(i2c0, chan);
    printf("\t ==> \tREAD: %d \t <== \t \n", result);
    if(chan<3){
      chan++;
    }
    else{
      chan = 0;
    }
    
    sleep_ms(500);
    //printf("Hello world!\n");
  }
  
  return 0;

}

void ads_init(i2c_inst_t *i2c_port, uint8_t resol){
  i2c_init(i2c_port, 400*1000);
  ads_set_mode(i2c_port, 1);
  ads_set_pga(i2c_port, resol);
  ads_set_mux(i2c_port, 3);
  ads_set_speed(i2c_port, 5);
}

//We're assuming there's just one connected, on the i2c bus that we are giving it
void ads_read_config(i2c_inst_t *i2c_port){
  uint8_t preConf[2];
  i2c_write_blocking(i2c_port, I2C_ADDR, &config_ptr, 1, true);
  i2c_read_blocking(i2c_port, I2C_ADDR, preConf, 2, false);
  
  config = (preConf[0] << 8) | preConf[1];
  
  printf("Read config: %#04x %#04x - %#06x \n", preConf[0], preConf[1], config);
}

//We're only going to allow single ADC measurements, differential measurements are not necessary
//This function will get called every time we read from the device
void ads_set_mux(i2c_inst_t* i2c_port, uint8_t channel){
  uint16_t channelMask = 0x7000;
  uint16_t channels[4] = {0x4000, 0x5000, 0x6000, 0x7000};
  
  config &= ~channelMask;
  config |= channels[channel];
  
  printf("Mux reconfigured!");
  
  ads_write_config(i2c_port, config);
}

//We're only going to allow the 4V and 5V options because they're the ones we can use at 3.3V and 5V VCC
//This one, as opposed to the mux setting, will only get called during initialisation
void ads_set_pga(i2c_inst_t* i2c_port, uint8_t resol){
  uint16_t pgaMask = 0x0E00;
  config &= ~pgaMask;
  switch(resol){
    case 5:
      //Weird cases where 5V is necessary happen here
      config |= 0x0000;
      break;
    default:
      //3.3V operation happens here
      config |= 0x0200;
      break;
  }
  
  ads_write_config(i2c_port, config);
  
}

void ads_set_mode(i2c_inst_t* i2c_port, uint8_t mode){
  
  uint16_t modeMask = 0x0100;
  config &= ~modeMask;
  if(mode > 0){
    //Default
    config |= 0x0100;
  }
  
  //We also:
  // - bit 4-Forcibly set the comparator mode to regular, instead of windowed comparator mode
  // - bit 3: Set the comaprator polarity to default (Active Low)
  // - bit 2: Set the comparator latches to disable
  uint16_t compMask = 0x001F;
  config &= ~compMask;
  // - bits 0:1: Disable all the comparator nonsense. The previous defaults shouldn't matter because of this, but still.
  config |= 0x0003;
  
  ads_write_config(i2c_port, config);
}


void ads_set_speed(i2c_inst_t* i2c_port, uint8_t speed){
  
  uint16_t speedMask = 0x00E0;
  uint16_t speedOpts[8] = {0x0000, 0x0020, 0x0040, 0x0060, 0x0080, 0x00A0, 0x00C0, 0x00E0};
  
  config &= ~speedMask;
  config |= speedOpts[speed];
  
  ads_write_config(i2c_port, config);
}

uint16_t ads_read_channel(i2c_inst_t* i2c_port, uint8_t channel){
  ads_set_mux(i2c_port, channel);
  
  uint8_t res[2];
  uint16_t result;
  
  i2c_write_blocking(i2c_port, I2C_ADDR, &conver_ptr, 1, true);
  i2c_read_blocking(i2c_port, I2C_ADDR, res, 2, false);
  
  result = (res[0] << 8) | res[1];
  
  return result;
}

void ads_write_config(i2c_inst_t* i2c_port, uint16_t config){
  uint8_t tmp[3];
  
  //When writing an array to i2c, the first thing we write is where the array goes, and then the contents of the array.
  tmp[0] = config_ptr;
  tmp[1] = (uint8_t)(config >> 8);
  tmp[2] = (uint8_t)(config & 0xff);
  
  printf("Write config: %#04x %#04x \n", tmp[1], tmp[2]);
  
  i2c_write_blocking(i2c_port, I2C_ADDR, tmp, 3, false);
}
