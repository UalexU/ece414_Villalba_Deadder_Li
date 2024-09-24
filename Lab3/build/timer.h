#ifndef TIMER_H
#define TIMER_H

#include "pico/stdlib.h"
#include "hardware/timer.h"

uint32_t timer_read();

uint32_t timer_elapsed_us(uint32_t t1, uint32_t t2);

uint32_t timer_elapsed_ms(uint32_t t1, uint32_t t2);

// initialize starting delay to 300ms
void timer_init(void);

// Decrease the current delay after each iteration of the game
void timer_decrease(void);

// Reset the delay back to 300ms when the game restarts
void timer_reset(void);

// Check if the timer's delay period has elapsed
bool timer_elapsed(void);


#endif