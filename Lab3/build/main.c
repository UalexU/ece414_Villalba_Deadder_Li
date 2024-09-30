#include "pico/stdlib.h"
#include "sw_in.h"
#include "led_out.h"
#include <stdint.h>
#include "debounce_sw1.h"
#include "debounce_sw2.h"
#include "timer.h" 
#include "fsm.h"
// Set up UART
#include "uart.h"

int main() {
    // Initialize all the modules
    led_out_init();
    sw_in_init();
    debounce_sw1_init();
    debounce_sw2_init();
    my_uart_init();
    timer_init();
    fsm_init();

    uint32_t t1 = timer_read();
    uint32_t t1_debouncer = timer_read();
    uint32_t t2;  // Only declare once

    while (1) {
        t2 = timer_read();  // Use t2 without redeclaring

        // Updates the debounce tick
        if (timer_elapsed_ms(t1_debouncer, t2) >= DEBOUNCE_PD_MS) {
            debounce_sw1_tick();
            debounce_sw2_tick();
            t1_debouncer = t2;  // Update t1_debouncer with t2
        }

        // Updates the FSM tick
        if (timer_elapsed_ms(t1, t2) >= INITIAL_DELAY) {
            fsm_run();
            t1 = t2;  // Update t1 for the next FSM tick
        }
    }
    return 0;
}
