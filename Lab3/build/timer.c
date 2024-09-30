#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "timer.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include "stdint.h"
#include "stdbool.h"



static int current_delay;
static uint32_t last_time;

uint32_t timer_read()
{
    return time_us_32();
}

uint32_t get_current_delay(){
    return current_delay; 
    // return 100; //fixed delay of 100
}

// return the elapsed time in us between two 32-bit timestamps
// note the need to deal with rollovers
uint32_t timer_elapsed_us(uint32_t t1, uint32_t t2)
{
    if (t2 > t1)
        return t2 - t1;
    else
        return UINT32_MAX - t1 + t2 + 1;
}

// return the elapsed time in use betwen two 32-bit timestamps
uint32_t timer_elapsed_ms(uint32_t t1, uint32_t t2)
{
    return timer_elapsed_us(t1, t2) / 1000;
}

// Initialize starting delay to 300ms
void timer_init(void)
{
    current_delay = INITIAL_DELAY; // Start with the initial delay
    last_time = timer_read();      // Store the current time
}

// Decrease the current delay after each iteration
void timer_decrease(void)
{
    if (current_delay > MIN_DELAY)
    {
        current_delay -= DELAY_STEP; // Decrease the delay by a fixed step which is 100ms defined above
    }
}

// Reset the delay back to 300ms when the game restarts
void timer_reset(void)
{
    current_delay = INITIAL_DELAY; // Reset to the initial delay of 300ms
}

// Check if the timer's delay period has elapsed
bool timer_elapsed(void)
{
    uint32_t current_time = timer_read(); // Get the current time
    // If the time passed since last time is bigger than the delay return true
    if (timer_elapsed_ms(last_time, current_time) >= current_delay)
    {
        last_time = current_time; // Update the last time for the next check
        return true;              // Return true if the delay period has elapsed
    }
    return false; // Return false if the delay period has not elapsed
}
