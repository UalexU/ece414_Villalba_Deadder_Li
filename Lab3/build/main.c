#include "pico/stdlib.h"
#include "sw_in.h"
#include "led_out.h"
#include <stdint.h>
#include "debounce_sw1.h"
#include "debounce_sw2.h"
#include "timer.h" 
//#include "hardware/uart.h"
#include "fsm.h"
#include "uart.h"

//set up the UART
#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1


int main(){
    //initialize all the modules 
    led_out_init();
    sw_in_init();
    debounce_sw1_init();
    debounce_sw2_init();
    my_uart_init();
    timer_init();
    fsm_init();
    //const uint32_t MASK_9_2 = 0x000003fc;
   // uint32_t outval = 0x1;
   // bool dir_left = true;

    uint32_t last_debounce_time = 0;
    uint32_t last_fsm_time = 0;
    // Initialize the FSM, timer, and LED display

    while (1) {
        uint32_t current_time = timer_read();
        //t3 = timer_read();
        if (timer_elapsed_ms(last_debounce_time,current_time) >= DEBOUNCE_PD_MS) {
            debounce_sw1_tick();
            debounce_sw2_tick();
            last_debounce_time = current_time;

        }

        if (timer_elapsed_ms(last_fsm_time,current_time) >= get_current_delay()) {
            fsm_run();
            last_fsm_time = current_time;
        }
    }
    return 0;
}