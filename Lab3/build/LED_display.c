#include "led_display.h"
#include "led_out.h"  
#include "hardware/uart.h"
#include "pico/stdlib.h"

#define LEFT_LED 0x01   // leftmost LED (GPIO 2)
#define RIGHT_LED 0x80  // rightmost LED (GPIO 9)


#define UART_ID uart0

// Initialize the LED display
void led_display_init(void) {
    led_out_init(); 
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
    uart_puts(UART_ID, "Left Player Loses a Point\n");  // Send the UART message
}

// Flash the leftmost LED 3 times when the right player misses
void led_display_flash_left_loss(void) {
    for (int i = 0; i < 3; i++) {
        led_out_write(LEFT_LED);  // Flash the leftmost LED
        sleep_ms(200);  // Wait for 200ms
        led_out_write(0);  // Turn off all LEDs
        sleep_ms(200);  // Wait for 200ms
    }
    uart_puts(UART_ID, "Right Player Loses a Point\n");  // Send the UART message
}