#include "pico/stdlib.h"
#include "sw_in.h"
#include "led_out.h"
#include <stdint.h>

int main(){
    bool int1, int2;
    uint8_t out;
    sw_in_init();
    led_out_init();
    
    while(1){
        
        int1 = sw_in_read1();
        int2 = sw_in_read2();

        if ( int1 && int2 ){
            // turn on 8 leds
            led_out_write(0xFF); 
        }
        else if (~int1 && int2){
             // turn on left most led
            led_out_write(0x80); 
        }
        else if (int1 && ~int2){
             // turn on right most led
            led_out_write(0x01); 
        }
        else {
             // turn off all led
            led_out_write(0x00); 
        }

        sleep_ms(10); // for optimized cpu performance 
    }
    return 0; 
}