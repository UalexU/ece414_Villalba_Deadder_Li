#include "pico/stdlib.h"
#include "sw_in.h"
#include "led_out.h"
#include <stdint.h>
#include "debounce_sw1.h"
#include "debounce_sw2.h"
#include "timer.h" 
#include "uart_demo.c"

//we need to add timer for speed control, the UART for printing, the FSM to cnotrol the ball 
//the debunce_1 and 2
int main(){
  const uint32_t MASK_9_2 = 0x000003fc;
    uint32_t outval = 0x1;
    bool dir_left = true;
    gpio_init_mask(MASK_9_2);
    gpio_set_dir_out_masked(MASK_9_2);
    while (true) {
        gpio_put_masked(MASK_9_2, outval << 2);
        sleep_ms(100);
        if (dir_left) {
            if (outval == 0x80) {
                dir_left = false;
                outval = outval >> 1;
            }
            else outval = outval << 1;
        }
        else {
            if (outval == 0x1) {
                dir_left = true;
                outval = outval << 1;
            }
            else outval = outval >> 1;
        }
    }
  return 0;
}