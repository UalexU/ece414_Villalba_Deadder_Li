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
#include "hardware/uart.h"
#include "operations.h"
#include <stdint.h>

#define UART_ID uart0
#define BAUD_RATE 115200

uint16_t x, y;
uint16_t *px, *py;
int main()
{
    struct TSPoint p;
    p.x = 0;
    p.y = 0;
    p.z = 0;
    // char buffer[30];
    ts_lcd_init();
    stdio_init_all();
    uint16_t x_value;
    uint16_t y_value;
    char buffer[30];
    uart_init(UART_ID, BAUD_RATE);
    tft_setTextSize(3);

    while (1)
    {

        // get input values:

        getPoint(&p);

        // if its touched, then write the location:
        if (get_ts_lcd(&p.z))
        {

            tft_fillScreen(ILI9340_BLACK);
            y_value = interpolateY(p.x);
            x_value = interpolateX(p.y);
            printf("printf demands to be seen and heard!\n\n");

            // Debuggin position
            tft_setCursor(20, 20);
            tft_setTextColor(ILI9340_WHITE);
            sprintf(buffer, "button: %c", get_button(x_value, y_value));
            tft_writeString(buffer);

            // Get button
            // get_button(x_value, y_value);
        }
        else
        {
            tft_setCursor(20, 20);
            tft_setTextColor(ILI9340_WHITE);
            sprintf(buffer, "button: %c", get_button(x_value, y_value));
            tft_writeString(buffer);
        }

        //     //print the old cursor
        // }
        // tft_fillCircle(x_value, y_value, 15, ILI9340_BLUE);
        tft_drawLine(x_value - 15, y_value - 15, x_value + 15, y_value + 15, ILI9340_BLUE);
        tft_drawLine(x_value - 15, y_value + 15, x_value + 15, y_value - 15, ILI9340_BLUE);
        // calculator_fsm();
        display();
        sleep_ms(100);
    }
    return 1;
}
