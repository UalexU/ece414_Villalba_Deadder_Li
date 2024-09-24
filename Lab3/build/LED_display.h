#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include <stdbool.h>

// nitialize the LED display
void led_display_init(void);

// shift the ball from left to right
void led_display_shift_left(void);

// shift the ball from right to left
void led_display_shift_right(void);

//  flash the rightmost LED 3 times (for missR)
void led_display_flash_right_loss(void);

//o flash the leftmost LED 3 times (for missL)
void led_display_flash_left_loss(void);

#endif