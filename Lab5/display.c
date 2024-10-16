#include "ts_lcd.h"
#include "TFTMaster.h"
#include <inttypes.h>
#include "TouchScreen.h"
#include <stdbool.h>
#include <stdio.h>






void draw_cursor(uint32_t x, uint32_t y){
    tft_drawFastHLine( interpolateX(x)-15, interpolateY(y), 30, ILI9340_BLUE);
    tft_drawFastVLine( interpolateY(x), interpolateY(y)-15, 30, ILI9340_BLUE);
}
