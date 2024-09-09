#include "pico/stdlib.h"         // Standard library for the Pico SDK
#include <led_out.h>             // Include for custom LED control header (assuming this exists)
#include <cstdint>
#include <stdbool.h>
    // Create a bitmask for GPIO pins 9 to 2 (00000011 11111100 in binary)
    // This indicates that GPIO pins 9 to 2 are the ones we want to control
    const uint8_t MASK_9_2 = 0x000003fc;
        
    // Start with the output value 0x1 (00000001 in binary), which represents the rightmost LED being on

    uint8_t outval = 0x1;
    // Direction flag to indicate whether the LED shift is moving left or right across the pins    
    bool dir_left = true;
// Initialize the LED output pins
void led_out_init() {
    




    // Initialize all GPIO pins in the mask (pins 9 to 2)
    gpio_init_mask(MASK_9_2);

    // Set the direction of the GPIO pins in the mask to output, so we can control the LEDs
    gpio_set_dir_out_masked(MASK_9_2);
}

// Write to the LED pins based on the current value of `outval`
void led_out_write(uint8_t a) {

    // Infinite loop to continuously shift LED outputs left and right
    while (true) {
        // Write the `outval` to GPIO pins 9 to 2 (shifted left by 2 bits to align with GPIO pins 9 to 2)
        // `outval << 2` ensures the value aligns with GPIO pin 2 onwards (skipping pins 0 and 1)
        gpio_put_masked(MASK_9_2, outval << 2);

        // Wait for 100 milliseconds before changing the LED pattern
        sleep_ms(100);

        // Check if we're shifting left
        if (dir_left) {
            // If the leftmost LED (outval = 0x80 or 10000000 in binary) is on, reverse direction
            if (outval == 0x80) {
                dir_left = false;        // Change direction to shift right
                outval = outval >> 1;    // Shift the value right for the next cycle
            }
            else {
                // Otherwise, keep shifting the value to the left (moving the lit LED to the left)
                outval = outval << 1;
            }
        }
        else {
            
            // If the rightmost LED (outval = 0x1 or 00000001 in binary) is on, reverse direction
            if (outval == 0x1) {
                dir_left = true;         
                outval = outval << 1;    // Shift the value left for the next cycle
            }
            else {
                // Otherwise, keep shifting the value to the right (moving the lit LED to the right)
                outval = outval >> 1;
            }
        }
    }
}
