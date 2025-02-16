#include <stdio.h>
#include "pico/stdlib.h"
#include "sd_card.h"
#include "ff.h"

#ifndef __SD_H_
#define __SD_H_

class SD{

    private:
        //VARS
        char buf[1024];
        char *filename;
        FRESULT fr;
        FATFS fs;
        FIL fil;
        int ret;
        uint written_bytes;
        //FUNCS
        void initialize();
        void mount_drive();
        
        void unmount();
    public:
        //VARS

        //FUNCS
        SD(char *filename);
        SD();
        ~SD();
        uint get_written_bytes();
        void write_to_sd(char buf[1024]);

};

#endif
