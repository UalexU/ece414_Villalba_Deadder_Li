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

void display(){
    char buffer[31];  
    assert(sizeof(buffer) > 30);  // Make sure buffer is at least 30
    int x = 5;
    int y = (240 - 10) / 5;
    int x_text, y_text, x_offset, y_offset = 0;
    x_offset = 75;
    y_offset = 50;
    x_text = 8;
    y_text = 7;
    int total_x, total_y; // This values are the parameters in the rectangle and logical functions

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {


            total_x = 10 + i * x_offset; 
            total_y = (240 - 20) / 5 + j * y_offset; 

            if (i == 1 && j == 3)
            {
                tft_fillRoundRect(total_x, total_y, 320 / 5 + 8, 240 / 5, 10, ILI9340_RED);
                tft_setTextColor(ILI9340_BLACK);
                tft_setCursor((total_x) + (320 / 5 + 8) / 2 - x_text, (total_y) + (240 / 5) / 2 - y_text);

                sprintf(buffer, "C");  // Write "C" into the buffer
                tft_writeString(buffer);
            }
            else if (i == 2 && j == 3)
            {
                tft_fillRoundRect(total_x, total_y, 320 / 5 + 8, 240 / 5, 10, ILI9340_BLUE);
                tft_setTextColor(ILI9340_BLACK);
                tft_setCursor((total_x) + (320 / 5 + 10) / 2 - x_text, (total_y) + (240 / 5) / 2 - y_text);

                sprintf(buffer, "=");  // Write "=" into the buffer

                tft_writeString(buffer);
            }
            else if (i == 3)
            {
                tft_fillRoundRect(total_x, total_y, 320 / 5 + 8, 240 / 5, 10, ILI9340_GREEN);
                tft_setTextColor(ILI9340_BLACK);

                // selecting an operator based on row
                char operator;
                switch (j)
                {
                case 0:
                    operator = '+';
                    break;
                case 1:
                    operator = '-';
                    break;
                case 2:
                    operator = 'x';
                    break;
                case 3:
                    operator = '/';
                    break;
                default:
                    operator = ' ';
                }

                tft_setCursor((total_x) + (320 / 5 + 8) / 2 - x_text, (total_y) + (240 / 5) / 2 - y_text);

                sprintf(buffer, "%c", operator);  // Write operator into the buffer

                tft_writeString(buffer);
            }
            else if (i == 0)
            {
                tft_fillRoundRect(total_x, total_y, 320 / 5 + 8, 240 / 5, 10, ILI9340_WHITE);
                tft_setTextColor(ILI9340_BLACK);
                char operand;
                switch (j)
                {
                case 0:
                    operand = '7';
                    break;
                case 1:
                    operand = '4';
                    break;
                case 2:
                    operand = '1';
                    break;
                case 3:
                    operand = '0';
                    break;
                default:
                    operand = ' ';
                }

                tft_setCursor((total_x) + (320 / 5 + 8) / 2 - x_text, (total_y) + (240 / 5) / 2 - y_text);

                sprintf(buffer, "%c", operand);  // write operand into the buffer

                tft_writeString(buffer);
            }
            else if (i == 1)
            {
                tft_fillRoundRect(total_x, total_y, 320 / 5 + 8, 240 / 5, 10, ILI9340_WHITE);
                tft_setTextColor(ILI9340_BLACK);
                char operand1;
                switch (j)
                {
                case 0:
                    operand1 = '8';
                    break;
                case 1:
                    operand1 = '5';
                    break;
                case 2:
                    operand1 = '2';
                    break;
                case 3:
                    operand1 = 'C';
                    break;
                default:
                    operand1 = ' ';
                }

                tft_setCursor((total_x) + (320 / 5 + 8) / 2 - x_text, (total_y) + (240 / 5) / 2 - y_text);

                sprintf(buffer, "%c", operand1);  // write operand into the buffer

                tft_writeString(buffer);
            }
            else if (i == 2)
            {
                tft_fillRoundRect(total_x, total_y, 320 / 5 + 8, 240 / 5, 10, ILI9340_WHITE);
                tft_setTextColor(ILI9340_BLACK);
                char operand2;
                switch (j)
                {
                case 0:
                    operand2 = '9';
                    break;
                case 1:
                    operand2 = '6';
                    break;
                case 2:
                    operand2 = '3';
                    break;
                case 3:
                    operand2 = '=';
                    break;
                default:
                    operand2 = ' ';
                }

                tft_setCursor((total_x) + (320 / 5 + 8) / 2 - x_text, (total_y) + (240 / 5) / 2 - y_text);

                sprintf(buffer, "%c", operand2);  // write operand into the buffer

                tft_writeString(buffer);
            }
            else
            {
                tft_fillRoundRect(total_x, total_y, 320 / 5 + 8, 240 / 5, 10, ILI9340_WHITE);
                tft_writeString(buffer);

            }
        }
    }

   
}
