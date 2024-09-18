#include "pico/stdlib.h"
#include "timer.h"
#include "stdio.h"
#include "sw_in.h"
#include "debounce_sw2.h"
#include "led25_out.h"

void main()
{
    uint32_t t1, t2;
    bool led_state = true;
    led25_out_init();
    led25_out_write(led_state);
    sw_in_init();
    debounce_sw2_init();
    t1 = timer_read();
    stdio_init_all();
    printf("getting started\n");
    while (1) {
        t2 = timer_read();
        if (timer_elapsed_ms(t1,t2) >= DEBOUNCE_PD_MS) {
            debounce_sw2_tick();
            t1 = t2;
        }
        if (debounce_sw2_pressed()) {
            printf("+");
            led_state = !led_state;
            led25_out_write(led_state);
        }
    }
}