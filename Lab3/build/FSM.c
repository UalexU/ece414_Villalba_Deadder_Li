#include "fsm.h"
#include "led_display.h"
#include "debounce_sw1.h" // Left button debounce
#include "debounce_sw2.h" // Right button debounce
#include "pico/stdlib.h"
#include "timer.h"
#include "uart.h"
#include "sw_in.h"
#include "hardware/timer.h"
#include <stdio.h>
static int current_delay = INITIAL_DELAY;


// Declare the FSM state variable
static enum current_state {
    INIT,
    SERVE_RIGTH,
    SERVE_LEFT,
    LED1,
    LED2,
    LED3, 
    LED4,
    LED5,
    LED6,
    LED7,
    LED8, 
    MISS
} current_state; //all of the different states
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

    bool btn1 = debounce_sw1_pressed();   // Debounced check for left button
    bool btn2 = debounce_sw2_pressed();  // Debounced check for right button

switch (current_state) //FSM cases to show which light is on
    {
    case INIT:
        break;

    case SERVE_LEFT:
        led_out_write(0b10000000);
        break;

    case SERVE_RIGTH:
        led_out_write(0b00000001);
        break;

    case LED1:
        led_out_write(0b10000000);
        break;

    case LED2:
        led_out_write(0b01000000);
        break;

    case LED3:
        led_out_write(0b00100000);
        break;

    case LED4:
        led_out_write(0b00010000);
        break;

    case LED5:
        led_out_write(0b00001000);
        break;

    case LED6:
        led_out_write(0b00000100);
        break;

    case LED7:
        led_out_write(0b00000010);
        break;

    case LED8:
        led_out_write(0b00000001);
        break;
    }

    switch (current_state)
    {
 case INIT:

        if(initial_server==1)
        {
            current_state = SERVE_RIGTH;
        }
        else
        {
            current_state = SERVE_LEFT;
        }
        break;

    case SERVE_RIGTH: //when the ball is started on the right
        if (btn2)
        {
            dir_right = false; //starting direction (left)
            current_state = LED7; //skips LED8 for better visual flow
        }
        else
        {
            current_state = SERVE_RIGTH;
        }
        break;

    case SERVE_LEFT: //when the ball is started on the left
        if (btn1)
        {
            dir_right = true; //light moves right
            current_state = LED2; //skips L1 for better visual flow
        }
        else
        {
            current_state = SERVE_LEFT; //loops until button pressed
        }
        break;

    case LED1: 

        if (!dir_right && btn1)
        {
            if (current_delay > MIN_DELAY) //speeds up pong after every hit
            {
                current_delay -= DELAY_STEP;
            }
            dir_right = true; //switch direction
            current_state = LED2; 
        }
        else if (!btn1 && !dir_right) //miss condition
        {
            current_state = MISS;
            win = 1;
        }
        else // for testing purposes
        {
            current_state = LED1; 
        }
        break;

    case LED2: //light 2

        if (dir_right)
        {
            current_state = LED3;
        }
        else if (!dir_right)
        {
            current_state = LED1;
        }
        break;

    case LED3: //light 3

        if (dir_right)
        {
            current_state = LED4;
        }
        else if (!dir_right)
        {
            current_state = LED2;
        }
        break;

    case LED4: // light 4

        if (dir_right)
        {
            current_state = LED5;
        }
        else if (!dir_right)
        {
            current_state = LED3;
        }
        break;

    case LED5: //light 5
        
        if (dir_right)
        {
            current_state = LED6;
        }
        else if (!dir_right)
        {
            current_state = LED4;
        }
        break;

    case LED6: //light 6
        
        if (dir_right)
        {
            current_state = LED7;
        }
        else if (!dir_right)
        {
            current_state = LED5;
        }
        break;

    case LED7: //light 7
        
        if (dir_right)
        {
            current_state = LED8;
        }
        else if (!dir_right)
        {
            current_state = LED6;
        }
        break;

    case LED8:
        
        if (dir_right && btn2) //button is pressed, lights move the other way
        {
            if (current_delay > MIN_DELAY) //speeds up pong after  hit
            {
                current_delay -= DELAY_STEP;
            }
            dir_right = false;
            current_state = LED7; 
        }
        else if (!btn1 && dir_right) 
        {
            win = 0;
            current_state = MISS;
        }
        else 
        {
            current_state = LED8;
        }
        break;

    case MISS: // player misses the ball, then returns to start
        if(win) //right wins
        {
            //printf("Right Wins\n");
            led_display_flash_right_loss();
            initial_server = !initial_server;
            current_state = INIT;

        }
        else if(!win) //left wins
        {
            //printf("Left Wins\n");
            initial_server = !initial_server;
            led_display_flash_left_loss();
            current_state = INIT;
        }


    }
    
    }
    
