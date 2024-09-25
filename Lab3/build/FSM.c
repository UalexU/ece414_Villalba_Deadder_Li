#include "fsm.h"
#include "led_display.h"
#include "debounce_sw1.h" // Left button debounce
#include "debounce_sw2.h" // Right button debounce
#include "pico/stdlib.h"
#include "timer.h"
#include "uart.h"
#include "sw_in.h"
#include "hardware/timer.h"
// Declare the FSM state variable
static FSM_State current_state;
int initial_server;
// Initialize the FSM

void fsm_init(void)
{
    // debounce_sw1_init();
    // debounce_sw2_init();
    // Use the current timer value to make a pseudo-random decision
    initial_server = led_display_init(); // XOR with last_server to alternate

    timer_init(); // initialize the timer
    uart_print_fsm_state("INIT");
    current_state = INIT; // Start in the INIT state
    
}

// Run the FSM
void fsm_run(int btn1, int btn2)
{
    
    switch (current_state)
    {
    case INIT:
        current_state = INIT;
        break;
    case WAITPUSHL:
        current_state = WAITPUSHL;
        break;
    case WAITPUSHR:
        current_state = WAITPUSHR;
        break;
    case MISSL:
        current_state = MISSL;
        break;
    case MISSR:
        current_state = MISSR;
        break;
    }
    switch (current_state)
    {
    case INIT:
        if (initial_server == 0)
        {
            led_display_left_serve(); // Turn on left led
            uart_print_left_serve();
            if (btn1)
            {
                uart_print_fsm_state("WAITPUSHR");
                led_display_shift_right();        // Start moving the ball to the right
                timer_decrease();                 // Decrease the timer
                                                  // Left player pressed, move to WAITPUSHR state
                initial_server = !initial_server; // Change the server
                current_state = WAITPUSHR;
            }
            else
            {
                led_display_left_serve(); // Turn on left led
                current_state = INIT;
            }
        }
        else if (initial_server == 1)
        {   
            uart_print_left_serve();
            led_display_right_serve();
            if (btn2)
            {
                uart_print_fsm_state("WAITPUSHL");
                led_display_shift_left();         // Start moving the ball to the left
                timer_decrease();                 // Decrease the timer
                initial_server = !initial_server; // Change the server
                                                  // Right player pressed, move to WAITPUSHL state
                current_state = WAITPUSHL;
            }
            else
            {
                current_state = INIT;
                led_display_right_serve();
            }
        }

        break;

    case WAITPUSHL:
        // Ball is moving left, wait for right player press or a miss
        if (btn1)
        {
            // Right player pressed, move the ball to the right
            uart_print_fsm_state("WAITPUSHR");
            led_display_shift_right();
            timer_decrease();
            current_state = WAITPUSHR;
        }
        else if (timer_elapsed())
        {
            // Simulate a miss if no button press occurred within the time limit
            uart_print_fsm_state("MISSL");
            uart_print_left_loss();
            current_state = MISSL;
        }
        break;

    case WAITPUSHR:
        if (btn2)
        {
            uart_print_fsm_state("WAITPUSHL");
            led_display_shift_left();
            timer_decrease();
            // Left player pressed, move the ball to the left
            current_state = WAITPUSHL;
        }
        else if (timer_elapsed())
        {
            uart_print_fsm_state("MISSR");
            uart_print_right_loss();
            // Simulate a miss if no button press occurred within the time limit
            current_state = MISSR;
        }
        break;
    case MISSL:
        led_display_flash_left_loss();
        current_state = INIT;
        uart_print_fsm_state("INIT");
        timer_reset(); // Reset the timer
        break;
    case MISSR:
        led_display_flash_left_loss();
        current_state = INIT;
        uart_print_fsm_state("INIT");
        timer_reset(); // Reset the timer
        break;
    }
}