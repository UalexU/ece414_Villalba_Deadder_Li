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


uint16_t x, y;
uint16_t *px, *py;
int main()
{
    struct TSPoint p;
                p.x = 0;
                p.y = 0;
                p.z = 0;
    char buffer[30];
    ts_lcd_init();
    uint32_t x_value;
    uint32_t y_value;
    
    

    while (1)
    {
        
        // get input values:

        getPoint(&p);

        tft_fillScreen(ILI9340_BLACK);
        

        //if its touched, then write the location: 
        if(get_ts_lcd(&p.z)){ 
        

                
                tft_setCursor(40, 40);
                tft_setTextColor(ILI9340_WHITE); tft_setTextSize(2);


                tft_setTextColor(ILI9340_BLACK);
                tft_writeString(buffer);
                
    
                tft_setCursor(40, 40);
                tft_setTextColor(ILI9340_WHITE);
                sprintf(buffer,"x: %d, y: %d", interpolateX(p.y), interpolateY(p.x)); 
                tft_writeString(buffer); 
   
                y_value = interpolateY(p.x);
                x_value = interpolateX(p.y);

                
            
        } else{
            tft_setCursor(40,40);
            tft_setTextColor(ILI9340_WHITE);
            sprintf(buffer,"x: %d, y: %d",x_value, y_value); //TOCHECK
            tft_writeString(buffer);

            //print the old cursor 
        }
        sleep_ms(200);

        tft_fillCircle(x_value, y_value, 15, ILI9340_BLUE); 
        //tft_drawLine( x_value - 10, y_value-10,  x_value + 10, y_value+10, ILI9340_BLUE);
        //tft_drawLine( y_value-10,  x_value-10, y_value+10, x_value+10, ILI9340_BLUE);
        
    }
    return 1; 
}
