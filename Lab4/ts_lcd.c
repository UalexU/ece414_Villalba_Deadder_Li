<<<<<<< HEAD
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "TouchScreen.h"
#include "TFTMaster.h"
#include "stdbool.h"



=======
#include "ts_lcd.h"
>>>>>>> e551af2207879834732a1464d6af130d8327fa8b
// This function shall return true when a finger 
// or stylus has been placed on the display; 
bool get_ts_lcd(uint16_t *px, uint16_t *py){
    if (){
        
    }
}

<<<<<<< HEAD
void ts_lcd_init(){
    adc_init();
    //initialize screen
    tft_init_hw();
    tft_begin();
    tft_setRotation(3); 
    tft_fillScreen(ILI9340_BLACK);  
}
=======
void ts_lcd_init(); //initialization function 
>>>>>>> e551af2207879834732a1464d6af130d8327fa8b
