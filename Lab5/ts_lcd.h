#ifndef TS_LCD_H
#define TS_LCD_H
#include "pico/stdlib.h"
#include "TouchScreen.h"
#include "TFTMaster.h"



bool get_ts_lcd(uint16_t *pz);
void ts_lcd_init();
void display(char buffer[30]); 
uint32_t interpolateX(uint32_t px);
uint32_t interpolateY(uint32_t py);

#endif