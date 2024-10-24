#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "TouchScreen.h"
#include "TFTMaster.h"
#include "stdbool.h"
#include "stdint.h"
#include "ts_lcd.h"

void ts_lcd_init()
{
    adc_init();
    // initialize screen
    tft_init_hw();
    tft_begin();
    tft_setRotation(3);
    tft_fillScreen(ILI9340_BLACK);
    tft_setCursor(40, 40);
    tft_setTextColor(ILI9340_WHITE); 
    tft_setTextSize(2);
    
}

// This function shall return true when a finger
// or stylus has been placed on the display;
bool get_ts_lcd(uint16_t *pz)
{
    if (*pz < 1500)
        return true;
    return false;
}

uint32_t interpolateX(uint32_t py)
{
    uint32_t y_pos = 0;

    y_pos = (py) * (380) / (3600 - 0) - 60; // Interpolation

    return (320 - y_pos);
}

uint32_t interpolateY(uint32_t px)
{
    uint32_t x_pos = 0;

    x_pos = (px) * (300) / (3400 - 0) - 60; // Interpolation

    return (x_pos);
}
