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
  const uint32_t MASK_9_2 = 0x000003fc;
    uint32_t outval = 0x1;
    bool dir_left = true;
  
    led_out_init();

    uint32_t current_time = timer_read();
    
    // Initialize the FSM, timer, and LED display
    my_uart_init();
    fsm_init();

    uint32_t t1, t2 ,t3;
    sw_in_init();
    debounce_sw1_init();
    debounce_sw2_init();

    t1 = timer_read();
   
   
    while (1) {
        t3 = timer_read();
        if (timer_elapsed_ms(t1,t3) >= DEBOUNCE_PD_MS) {
            debounce_sw1_tick();
            debounce_sw2_tick();

            t1 = t3;
        }

        if (timer_elapsed_ms(t2,t3) >= 500) {
            fsm_run(debounce_sw1_pressed(),debounce_sw2_pressed());
            t2 = t3;
        }
    }
    return 0;
}