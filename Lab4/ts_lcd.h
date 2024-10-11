#ifndef TS_LCD_H
#define TS_LCD_H
#include "pico/stdlib.h"
#include "TouchScreen.h"
#include "TFTMaster.h"



bool get_ts_lcd(uint16_t *px, uint16_t *py);
void ts_lcd_init();
uint32_t interpolateX(uint16_t px);
uint32_t interpolateY(uint16_t py);

#endif