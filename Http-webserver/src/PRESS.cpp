#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include <stdbool.h> 
#include "PRESS.h"

PRESS::PRESS(uint8_t buf[2], uint8_t tempbuf[3], uint8_t tmptlo, uint8_t tmpthi, uint8_t tmpplo, uint8_t tmppme, uint8_t tmpphi){
    this->buf[2]=buf[2];
    this->tempbuf[3]=tempbuf[3];
    this->tmptlo=tmptlo;
    this->tmpthi=tmpthi;
    this->tmpplo=tmpplo;
    this->tmppme=tmppme;
    this->tmpplo=tmpplo;

    configure();
}

void PRESS::configure(){
    stdio_init_all();

    #if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c/lps33hw_i2c example requires a board with I2C pins
    puts("Default I2C pins were not defined");
    #else
    printf("Definitions done!\n");

    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c_default, 400 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
    #endif
    buf[0]=REG_CTRL_REG1;
    buf[1] = 0b01000010; 
    i2c_write_blocking(i2c_default, ADDRESS, buf, 2, false);
    buf[0] = REG_CTRL_REG2;
    buf[1]=0b00010001; 
    i2c_write_blocking(i2c_default, ADDRESS, buf, 2, false);
    temp=0.0;
    press=0.0;

}
float PRESS::convert_press(){

    read_press();
    float tmp1=tmpphi<<16;
    float tmp2=tmppme<<8;
    float tmpp=tmpplo+tmp1+tmp2;
    return(tmpp/4096);
}
float PRESS::convert_temp(){

    read_temp();
    float tmp=tmpthi<<8;
    float tmp2=tmptlo+tmp;
    return (tmp2/100);
}
void PRESS::read_temp(){

    i2c_write_blocking(i2c_default, ADDRESS, &REG_T_OUT_L, 1, true);
    i2c_read_blocking(i2c_default, ADDRESS, &tmptlo, 1, false);

    i2c_write_blocking(i2c_default, ADDRESS, &REG_T_OUT_H, 1, true);
    i2c_read_blocking(i2c_default, ADDRESS, &tmpthi, 1, false);
}
void PRESS::read_press(){

    i2c_write_blocking(i2c_default, ADDRESS, &REG_P_OUT_XL, 1, true);
    i2c_read_blocking(i2c_default, ADDRESS, &tmpplo, 1, false);

    i2c_write_blocking(i2c_default, ADDRESS, &REG_P_OUT_L, 1, true);
    i2c_read_blocking(i2c_default, ADDRESS, &tmppme, 1, false);

    i2c_write_blocking(i2c_default, ADDRESS, &REG_P_OUT_H, 1, true);
    i2c_read_blocking(i2c_default, ADDRESS, &tmpphi, 1, false);
}