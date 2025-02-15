#include <stdio.h>
#include "pico/stdlib.h"
#include "sd_card.h"
#include "ff.h"
#include "SD.h"
#include <string.h>


int main(){
    char buf[100];
    stdio_init_all();
    printf("\r\nSD card test. Press 'enter' to start.\r\n");
    while (true) {
        buf[0] = getchar();
        if ((buf[0] == 'a') || (buf[0] == 'b')) {
            break;
        }
    }
    printf("Filename: test.txt\n");
    char *filename, *text;
    strcpy(filename,"test.txt");
    SD sd(filename);
    strcpy(text,"This text is a test.\n");
    sd.write_to_sd(text);
    return 0;
}