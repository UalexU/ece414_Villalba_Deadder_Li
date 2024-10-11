/*
 * File:   touch_main.c
 * Author: Matthew Watkins
 * Ported to Pico by John Nestor
 * Modified by Alex and Gabby DeAdder DeSubstractor
 *
 * Description: Prints out the detected position (x, y) of a press on the
 * touchscreen as well as the pressure (z).
 *
 * IMPORTANT: For this example to work, you need to make the following
 * connections from the touchpad to the Pico:
 *  Y+ => ADC1/GP27 (Pin 32)
 *  Y- => GP21 (Pin 27)
 *  X+ => GP22 (Pin 29)
 *  X- => ADC0/GP26 (Pin 31)
 *
 */

#include "ts_lcd.h"
#include "TFTMaster.h"
#include <inttypes.h>
#include "TouchScreen.h"
#include <stdbool.h>
#include <stdio.h>

int main()
{
    char buffer[30];
    ts_lcd_init();
    uint32_t x_value;
    uint32_t y_value;

    uint16_t x, y; 
    uint16_t px = &x;
    uint16_t py = &y;

    while (1)
    {
        if (get_ts_lcd(px, py))
        {
            if ((px != NULL) && (py != NULL)) // Checks the pointers aren't NULL
            {
                tft_fillScreen(ILI9340_BLACK);
                // Crosshair:
                tft_drawLine(*px - 5, *py, *px + 5, *py, ILI9340_YELLOW);
                tft_drawLine(*px, *py - 5, *px, *py + 5, ILI9340_YELLOW);
                // Location of press displayed as text:
                sprintf(buffer, "Last location pressed was: %d, %d", *px, *py);
                tft_setCursor(10, 10);
                tft_writeString(buffer);
            }
        }
        else
        {
            tft_fillScreen(ILI9340_BLACK);
            // Crosshair:
            tft_drawLine(*px - 5, *py, *px + 5, *py, ILI9340_YELLOW);
            tft_drawLine(*px, *py - 5, *px, *py + 5, ILI9340_YELLOW);
            // Last location pressed displayed as text:
            sprintf(buffer, "Last location pressed was: %d, %d", *px, *py);
            tft_setCursor(10, 10);
            tft_writeString(buffer);
        }
        sleep_ms(250); // Added to prevent excessive flickering
    
    }
    return 1; 
}
