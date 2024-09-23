#include "pico/stdlib.h"
#include "sw_in.h"
#include "led_out.h"
#include <stdint.h>
#include "debounce_sw1.h"
#include "debounce_sw2.h"
#include "timer.h" 
#include "hardware/uart.h"


//set up the UART
#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

//we need to add timer for speed control, the UART for printing 
//the debunce_1 and 2
static enum DB_States {INIT,WAITPUSHL,WAITPUSHR,MISSR,MISSL} DB_State;

// Timing variables
const uint32_t INITIAL_DELAY = 300; // Start delay at 300ms
const uint32_t MIN_DELAY = 100;      // Minimum delay at 100ms
uint32_t delay_time = INITIAL_DELAY; // Current delay time
uint32_t last_move_time = 0;  

void FSM() { 

bool btn2 = debounce_sw2();
bool btn1 = debounce_sw1();

    switch(DB_State) {
        case INIT:
            if(btn2) {
                DB_State = WAITPUSHL;  
            } else if(btn1) {
                DB_State = WAITPUSHR;  
            }
            delay_time = INITIAL_DELAY; // Reset delay to 300ms
            last_move_time = timer_read(); // Record the start time
            uart_puts(UART_ID, "FSM State: INIT\n");
            break;

case WAITPUSHR:
            if(btn2) {
                DB_State = WAITPUSHL;
                 uart_puts(UART_ID, "FSM State: WAITPUSHL\n");
            } else {
                DB_State = MISSR;
                 uart_puts(UART_ID, "FSM State: MISSR\n");
            }
           

            break;

case WAITPUSHL:
            if(btn1) {
                DB_State = WAITPUSHR;
                uart_puts(UART_ID, "FSM State: WAITPUSHR\n");

            } else {
                DB_State = MISSL;
                uart_puts(UART_ID, "FSM State: MISSL\n");

            }
            break;

case MISSL:
case MISSR:
    DB_State = INIT;
    break;

    }
}

int main(){
  const uint32_t MASK_9_2 = 0x000003fc;
    uint32_t outval = 0x1;
    bool dir_left = true;

    gpio_init_mask(MASK_9_2);
    gpio_set_dir_out_masked(MASK_9_2);

     DB_State = INIT;
     uint32_t current_time = timer_read();
     const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    stdio_init_all();

    while (true) {
    
          FSM();
         
         // Check if enough time has passed since the last move
        if (timer_elapsed_ms(last_move_time, current_time) >= delay_time) {
            gpio_put_masked(MASK_9_2, outval << 2);


        
       // sleep_ms(100);
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
}
    if (delay_time > MIN_DELAY) {
                delay_time -= 10; // Decrease delay time gradually
            }
            last_move_time = current_time; // Update last move time
        }
    }
  return 0;
}