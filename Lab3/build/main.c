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
  
    gpio_init_mask(MASK_9_2);
    gpio_set_dir_out_masked(MASK_9_2);

     
    uint32_t current_time = timer_read();
    
    
    // Initialize the FSM, timer, and LED display
    my_uart_init();
    fsm_init();

    while (true) {
        // Run the FSM (Finite State Machine)
      debounce_sw1_tick();
      debounce_sw2_tick();
      fsm_run();
    }

    return 0;
}