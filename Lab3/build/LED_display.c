#include "led_display.h"
#include "led_out.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include <stdlib.h>
#include "timer.h"
#include "uart.h"


int random_server()
{
    static int last_server = 1; // Track the last server (1 for right, 0 for left)
    // Use the current timer value to make a pseudo-random decision
    uint32_t current_time = rand();
    int initial_server = (current_time % 2) ^ last_server; // XOR with last_server to alternate
    return initial_server;

}

// Continuously shift the ball from rightmost to leftmost
void led_display_shift_left(void)
{
    uint16_t outval = RIGHT_LED;
    while (outval <= LEFT_LED)
    {
        uart_debug();
        led_out_write(outval);
        sleep_ms(get_current_delay());
        outval <<= 1;
        uart_puts(UART_ID, "Right Player Lost the Point\n");
    }
}
void led_display_left_serve(void)
{
    led_out_write(LEFT_LED); // Light the leftmost LED

}

// Set the right player to serve
void led_display_right_serve(void)
{
    led_out_write(RIGHT_LED); // Light the rightmost LED
}

// shift the ball from left to right (starting at the leftmost LED)
void led_display_shift_right(void)
{
    uint16_t outval = LEFT_LED;
    while (outval >= RIGHT_LED)
    {
        led_out_write(outval);
        sleep_ms(get_current_delay());
        outval >>= 1;
    }
}

// Flash the rightmost LED 3 times when the left player misses
void led_display_flash_right_loss(void)
{
    for (int i = 0; i < 3; i++)
    {
        led_out_write(RIGHT_LED); // Flash the rightmost LED
        sleep_ms(200);
        led_out_write(RIGHT_LED); // Flash the rightmost LED
        sleep_ms(200);
        led_out_write(RIGHT_LED); // Flash the rightmost LED
        sleep_ms(200);
        led_out_write(0);
        sleep_ms(500);
    }
}

// Flash the leftmost LED 3 times when the right player misses
void led_display_flash_left_loss(void)
{
    for (int i = 0; i < 3; i++)
    {
        led_out_write(LEFT_LED); // Flash the leftmost LED
        sleep_ms(200);           // Wait for 200ms
        led_out_write(LEFT_LED); // Flash the leftmost LED
        sleep_ms(200);           // Wait for 200ms
        led_out_write(LEFT_LED); // Flash the leftmost LED
        sleep_ms(200);           // Wait for 200ms
        led_out_write(0);        // Turn off all LEDs
        sleep_ms(500);           // Wait for 200ms
    }
}