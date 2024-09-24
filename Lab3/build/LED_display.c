#include "led_display.h"
#include "led_out.h"  
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include "hardware/timer.h" 

#define LEFT_LED 0x01   // leftmost LED (GPIO 2)
#define RIGHT_LED 0x80  // rightmost LED (GPIO 9)


void led_display_init(void) {
    static int last_server = 1;  // Track the last server (1 for right, 0 for left)
    
    // Use the current timer value to make a pseudo-random decision
    uint32_t current_time = timer_get_count(timer_hw); //timer_get_count(timer_hw) returns the current timer value in microseconds.
    int initial_server = (current_time % 2) ^ last_server;  // XOR with last_server to alternate

    if (initial_server == 0) {
        // Left player serves
        led_display_left_serve();  // Light the leftmost LED
    } else {
        // Right player serves
        led_display_right_serve();  // Light the rightmost LED
    // Update last server
    last_server = initial_server;
    }
}

// Continuously shift the ball from leftmost to right most 
void led_display_shift_left(void) {
    uint8_t outval = LEFT_LED;  // Start with the leftmost LED
    // Shift the ball all the way to the rightmost LED
    while (outval <= RIGHT_LED) {
        led_out_write(outval);  
        sleep_ms(200);  
        outval <<= 1; 
    }
}
void led_display_left_serve(void) {
    led_out_write(LEFT_LED);  // Light the leftmost LED
}

// Set the right player to serve
void led_display_right_serve(void) {
    led_out_write(RIGHT_LED);  // Light the rightmost LED
}

// shift the ball from right to left (starting at the rightmost LED)
void led_display_shift_right(void) {
    uint8_t outval = RIGHT_LED;  // Start with the rightmost LED

    // Shift the ball all the way to the leftmost LED
    while (outval >= LEFT_LED) {
        led_out_write(outval);  
        sleep_ms(200);  
        outval >>= 1;  
    }
}

// Flash the rightmost LED 3 times when the left player misses
void led_display_flash_right_loss(void) {
    for (int i = 0; i < 3; i++) {
        led_out_write(RIGHT_LED);  // Flash the rightmost LED
        sleep_ms(200);  
        led_out_write(0);  
        sleep_ms(200);  
    }
}

// Flash the leftmost LED 3 times when the right player misses
void led_display_flash_left_loss(void) {
    for (int i = 0; i < 3; i++) {
        led_out_write(LEFT_LED);  // Flash the leftmost LED
        sleep_ms(200);  // Wait for 200ms
        led_out_write(0);  // Turn off all LEDs
        sleep_ms(200);  // Wait for 200ms
    }
}