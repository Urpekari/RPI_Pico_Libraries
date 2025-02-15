#include <stdio.h>
#include "pico/stdlib.h"
#include "sd_card.h"
#include "ff.h"
#include "SD.h"
#include <string.h>


SD::~SD(){

}
SD::SD(){
    strcpy(filename,"example.txt");
    initialize();
    mount_drive();
}
SD::SD(char *filename){
    strcpy(SD::filename,filename);
    initialize();
    mount_drive();
}

void SD::initialize(){
    if (!sd_init_driver()) {
        printf("ERROR: Could not initialize SD card\r\n");
        while (true);
    }
}

void SD::mount_drive(){
    fr = f_mount(&fs, "0:", 1);
    if (fr != FR_OK) {
        printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
        while (true);
    }
}

void SD::write_to_sd(char buf[1024]){
    fr = f_open(&fil,"test.txt", FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        printf("ERROR: Could not open file (%d)\r\n", fr);
        while (true);
    }
    ret = f_printf(&fil,"This text is a test.\n");
    if (ret < 0) {
        printf("ERROR: Could not write to file (%d)\r\n", ret);
        f_close(&fil);
        while (true);
    }
    fr = f_close(&fil);
    if (fr != FR_OK) {
        printf("ERROR: Could not close file (%d)\r\n", fr);
        while (true);
    }
} 

void SD::unmount(){
    f_unmount("0:");
}

int SD::get_written_bytes(){
    return SD::written_bytes;
}