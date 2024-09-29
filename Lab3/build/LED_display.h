#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include <stdbool.h>

// Variables 
//#define RIGHT_LED 0x200 // GPIO 9 (0010 0000 0000)
//#define LEFT_LED 0x04  // GPIO 2 (0000 0100)
#define RIGHT_LED 0x80 // GPIO 9 (0010 0000 0000)
#define LEFT_LED 0x01  // GPIO 2 (0000 0100)



// nitialize the LED display
int random_server(void);

// shift the ball from left to right
void led_display_shift_left(void);

// shift the ball from right to left
void led_display_shift_right(void);

//  flash the rightmost LED 3 times (for missR)
void led_display_flash_right_loss(void);

// o flash the leftmost LED 3 times (for missL)
void led_display_flash_left_loss(void);

void led_display_left_serve(void);

void led_display_right_serve(void);

#endif