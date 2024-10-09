#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "TouchScreen.h"
#include "TFTMaster.h"
#include "stdbool.h"



// This function shall return true when a finger 
// or stylus has been placed on the display; 
bool get_ts_lcd(uint16_t *px, uint16_t *py){
    if (){
        
    }
}

void ts_lcd_init(){
    adc_init();
    //initialize screen
    tft_init_hw();
    tft_begin();
    tft_setRotation(3); 
    tft_fillScreen(ILI9340_BLACK);  
}