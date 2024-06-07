#ifndef __PRESS_H_
#define __PRESS_H_

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include <stdbool.h>


#pragma once
class PRESS{

    private:
        //VARS
        const uint8_t REG_P_OUT_XL = 0x28;
        const uint8_t REG_P_OUT_L = 0x29;
        const uint8_t REG_P_OUT_H = 0x2A;
        const uint8_t REG_T_OUT_L = 0x2B;
        const uint8_t REG_T_OUT_H = 0x2C;
        const uint8_t REG_CTRL_REG1 = 0x10; //Proper config ==>0b01000010
        const uint8_t REG_CTRL_REG2 = 0x11; //Proper config ==>0b00010001
        const uint8_t ADDRESS = 0x5D;

        uint8_t buf[2];
        uint8_t tempbuf[3];
        uint8_t tmptlo;
        uint8_t tmpthi;
        uint8_t tmpplo;
        uint8_t tmppme;
        uint8_t tmpphi;
        
        float temp;
        float press;

        //FUNCS
        void read_press();
        void read_temp();
    public:

        float convert_press();
        float convert_temp();
        void configure();
    
    public:

        PRESS( uint8_t buf[2], uint8_t tempbuf[3], uint8_t tmptlo, uint8_t tmpthi, uint8_t tmpplo, uint8_t tmppme, uint8_t tmpphi);
        PRESS();
};

#endif
