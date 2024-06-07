#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "lwip/tcp.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "PRESS.h"

const char * ssi_tags[] = {"temp","press"};
PRESS sensor;

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen){
    size_t printed;
    
    switch(iIndex){
        case 0:     //Temperature
        {
            const float temp=sensor.convert_temp();
            printed = snprintf(pcInsert,iInsertLen,"%f",temp);        
            break;
        }
        case 1:     //Pressure
        {
            const float press=sensor.convert_press();
            printed = snprintf(pcInsert,iInsertLen,"%f",press);
            break;
            
        }
        default:
            printed=0;
            break;
            
    }
    return (u16_t)printed;
}
void ssi_init(){
    sensor.configure();

    http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}