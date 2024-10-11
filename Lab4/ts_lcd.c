#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "TouchScreen.h"
#include "TFTMaster.h"
#include "stdbool.h"

#include "ts_lcd.h"

void ts_lcd_init(){
    stdio_init_all();
    adc_init();
    //initialize screen
    tft_init_hw();
    tft_begin();
    tft_setRotation(0); 
    tft_fillScreen(ILI9340_BLACK);  
    tft_setTextSize(2);
    tft_setTextColor2(ILI9340_WHITE);
    
    
}

// This function shall return true when a finger 
// or stylus has been placed on the display; 
bool get_ts_lcd(uint16_t *px, uint16_t *py)
{

    struct TSPoint p;
    getPoint(&p);
    if (!(p.z < 20000))
    {
        return false;
    }
    else
    {
        *px = (p.x * (ILI9340_TFTWIDTH)) / 4100;
        *py = (p.y * (ILI9340_TFTHEIGHT)) / 3800;
        return true;
    }
}

uint32_t interpolateX(uint16_t px){
    uint32_t x_pos = 0; 

    x_pos = (px)*(320)/(4096 -0); // Interpolation

    return (320 - x_pos); 
}

uint32_t interpolateY(uint16_t py){
    uint32_t y_pos = 0; 

    y_pos = (py)*(240)/(2730 -0); // Interpolation

    return (y_pos); 
}





