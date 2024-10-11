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

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "TouchScreen.h"
#include "TFTMaster.h"
#include "ts_lcd.h"

int main()
{
    char buffer[30];
    ts_lcd_init();
    uint32_t x_value;
    uint32_t y_value;

    struct TSPoint p;
    p.x = 0;
    p.y = 0;
    p.z = 0;

    while (1)
    {

        getPoint(&p);
        tft_fillScreen(ILI9340_BLACK);
        // If screen touched
        if (get_ts_lcd(&p.z))
        {
            tft_setCursor(20, 100);
            tft_setTextColor(ILI9340_WHITE);
            tft_setTextSize(2);

            // erase old text

            tft_setTextColor(ILI9340_BLACK);
            tft_writeString(buffer);

            tft_setCursor(20, 100);
            tft_setTextColor(ILI9340_WHITE);
            sprintf(buffer, "x: %d, y: %d", interpolateX(p.y), interpolateY(p.x));
            tft_writeString(buffer);


            x_value = interpolateX(p.y); 
            y_value = interpolateY(p.x);
            sleep_ms(50);
        }
        else{
            tft_setCursor(20, 100);
            tft_setTextColor(ILI9340_WHITE);
            sprintf(buffer,"x: %d, y: %d", x_value, y_value); //TOCHECK
            tft_writeString(buffer);

        }

        tft_drawFastHLine(x_value-10, y_value, 20, ILI9340_BLUE);
        tft_drawFastVLine(x_value, y_value-10, 20, ILI9340_BLUE);
    }
    return 1; 
}
