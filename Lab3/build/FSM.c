#include "fsm.h"
#include "led_display.h"
#include "debounce_sw1.h"  // Left button debounce
#include "debounce_sw2.h"  // Right button debounce
#include "pico/stdlib.h"
#include "timer.h"

// Declare the FSM state variable
static FSM_State current_state;

// Initialize the FSM
void fsm_init(void) {
    current_state = INIT;  // Start in the INIT state
     timer_init();      // initialize the timer
     uart_print_fsm_state("INIT");
}

// Run the FSM 
void fsm_run(void) {
    bool btn2 = debounce_sw2();
    bool btn1 = debounce_sw1();
    // Check the current FSM state
    switch (current_state) {
        case INIT:
            // Wait for either left or right button press to start
            if (btn1) {
                uart_print_left_serve(); 
                // Left player pressed, move to WAITPUSHR state
                current_state = WAITPUSHR;
                uart_print_fsm_state("WAITPUSHR");
                led_display_shift_right();  // Start moving the ball to the right
                timer_decrease(); // timer decrease 

            } else if (btn2) {
                uart_print_right_serve(); 
                // Right player pressed, move to WAITPUSHL state
                current_state = WAITPUSHL;
                uart_print_fsm_state("WAITPUSHL");
                led_display_shift_left();  // Start moving the ball to the left
                timer_decrease(); //timer decrease 
            }
            break;

        case WAITPUSHL:
            // Ball is moving left, wait for right player press or a miss
            if (btn2) {
                // Right player pressed, move the ball to the right
                current_state = WAITPUSHR;
                uart_print_fsm_state("WAITPUSHR");
                led_display_shift_right();
                timer_decrease();
            } else {
                // Simulate a miss (no button press in time)
                current_state = MISSL;
                art_print_fsm_state("MISSL");
                uart_print_left_loss();
            }
            break;

        case WAITPUSHR:
            // Ball is moving right, wait for left player press or a miss
            if (btn1) {
                // Left player pressed, move the ball to the left
                current_state = WAITPUSHL;
                uart_print_fsm_state("WAITPUSHL");
                led_display_shift_left();
                timer_decrease();
            } else {
                // Simulate a miss (no button press in time)
                current_state = MISSR;
                uart_print_fsm_state("MISSR");
                uart_print_right_loss();

            }
            break;

        case MISSL:
            // Left player missed, flash the rightmost LED and reset to INIT
            led_display_flash_left_loss();
            current_state = INIT;
            uart_print_fsm_state("INIT");
            timer_reset();  //reset the timer 
            break;

        case MISSR:
            // Right player missed, flash the leftmost LED and reset to INIT
            led_display_flash_right_loss();
            current_state = INIT;
            uart_print_fsm_state("INIT");
            timer_reset();  //reset the timer 
            break;
    }
}

