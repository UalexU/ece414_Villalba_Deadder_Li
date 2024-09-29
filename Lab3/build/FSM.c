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
enum current_state {INIT,WAITPUSHL,WAITPUSHR,MISSL,MISSR} current_state;

// Initialize the FSM

void fsm_init(void)
{

    // Use the current timer value to make a pseudo-random decision
    initial_server = random_server(); // XOR with last_server to alternate

    // timer_init(); // initialize the timer
    uart_print_fsm_state("INIT");
    current_state = INIT; // Start in the INIT state
    
}

// Run the FSM
void fsm_run()
{

    bool btn1 = debounce_sw2_pressed();   // Debounced check for left button
    bool btn2 = debounce_sw1_pressed();  // Debounced check for right button

    switch (current_state)
    {
    case INIT:
        if (initial_server == 1) // Left server
        {
            led_display_left_serve(); // Turn on left led
            uart_print_left_serve();
            if (btn1) // Player serves
            {
                uart_print_fsm_state("WAITPUSHR");
                led_display_shift_right();        // Start moving the ball to the right
                timer_decrease();                 // Decrease the timer                            
                initial_server = !initial_server; // Change the server
                current_state = WAITPUSHR;
            }
            else
            {
                led_display_left_serve(); // Turn on left led
                current_state = INIT;
            }
        }
        else if (initial_server == 0)
        {   
            uart_print_right_serve();
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
        if (btn2) // if the player hits the ball 
        {
            uart_print_fsm_state("WAITPUSHL");
            led_display_shift_left(); // Shift ball to the left 
            timer_decrease(); 
            
            current_state = WAITPUSHL; // left player turn
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
        timer_reset(); // Reset the timer
        uart_print_fsm_state("INIT");
       
        break;
    case MISSR:
        led_display_flash_right_loss();
        current_state = INIT;
        timer_reset(); // Reset the timer
        uart_print_fsm_state("INIT");
        
        break;
    }
}