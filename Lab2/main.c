#include "pico/stdlib.h"
#include "sw_in.h"
#include "led_out.h"

main(){
    bool int1, in;
    uint16_t out;
    sw_in_init();
    led_out_init();

    while(1){
        int1=sw_in_read1();
        int2 = sw_in_read2();
    }
}