#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "string.h"
#include "GPS.h"

int main(){

    stdio_init_all();
    #if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c/mpu6050_i2c example requires a board with I2C pins
     puts("Default I2C pins were not defined");
    #else

    GPS gps(0,0,1);
    gps_data gdata;


    while(1){
    gdata = gps.parse_string();

    printf("Output con variables buenas: \n\n\n");
    printf("Protocol:%s\n", gdata.protocol);
    printf("UTC Time: %s\n", gdata.time);
    printf("Status: %c\n", gdata.status == 'V' ? "Data invalid. GPS fix not found." : "Data Valid");
    printf("Latitude: %f\n", gdata.latitude);
    printf("N/S indicator: %c\n", gdata.NSIndicator);
    printf("Longitude: %f\n", gdata.longitude);
    printf("E/W indicator: %c\n", gdata.EWIndicator);
    printf("Speed over ground: %f\n", gdata.speed);
    printf("Course over ground: %f\n", gdata.course);
    printf("Date: %c%c/%c%c/%c%c\n", gdata.date[0], gdata.date[1], gdata.date[2], gdata.date[3], gdata.date[4], gdata.date[5]);
    printf("\n\n");

    
    sleep_ms(10000);
    printf("\033[1;1H\033[2J");
    }

    
}

#endif