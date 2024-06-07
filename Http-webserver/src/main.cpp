#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "lwip/tcp.h"
#include "hardware/i2c.h"
#include "ssi.h"
#include "PRESS.h"

int main() {

	PRESS sensor;

    stdio_init_all();
    
    if (cyw43_arch_init()) {
        printf("failed to initialise\n");
        return 1;
    }
    const char *ap_name = "picow_test";
    const char *password = "password";
    cyw43_arch_enable_ap_mode(ap_name, password, CYW43_AUTH_WPA2_AES_PSK);
    
    httpd_init();
    ssi_init(sensor);
    
    while(1);
        


    cyw43_arch_deinit();
    return 0;
}
