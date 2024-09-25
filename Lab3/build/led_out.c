#include "pico/stdlib.h" // Standard library for the Pico SDK
#include <led_out.h>     // Include for custom LED control header (assuming this exists)
#include <stdint.h>
#include <stdbool.h>
// Create a bitmask for GPIO pins 9 to 2 (00000011 11111100 in binary)
// This indicates that GPIO pins 9 to 2 are the ones we want to control
// const uint32_t MASK_9_2 = 0x000003fc;
const uint32_t MASK_9_2 = (1 << 10) - 1;

// Initialize the LED output pins
void led_out_init()
{

    // Initialize all GPIO pins in the mask (pins 9 to 2)
    gpio_init_mask(MASK_9_2);

    // Set the direction of the GPIO pins in the mask to output, so we can control the LEDs
    gpio_set_dir_out_masked(MASK_9_2);
}

// Write to the LED pins based on the current value of `outval`
void led_out_write(uint8_t a)
{

    uint32_t shifted_value = (a << 2) & MASK_9_2;
    // gpio_put_masked(MASK_9_2, a << 2);
    gpio_put_masked(MASK_9_2, shifted_value);
}
