#include "pico/stdlib.h"
#include "sw_in.h"
#include "led_out.h"
#include <cstdint>
#include <stdbool.h>

main(){
    bool int1, int2;
    uint16_t out;
    sw_in_init();
    led_out_init();
    
    while(1){
        
        int1 = sw_in_read1();
        int2 = sw_in_read2();

        if ( int1 == true && int2 == true){
            // turn on 8 leds
            led_out_write(0xFF); 
        }
        else if (int1 == true && int2 == false){
             // turn on left most led
            led_out_write(0x10); 
        }
        else if (int1 == false && int2 == true){
             // turn on right most led
            led_out_write(0x01); 
        }
        else {
             // turn off all led
            led_out_write(0x00); 
        }
    }
}