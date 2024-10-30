#include "ts_lcd.h"
#include "TFTMaster.h"
#include <inttypes.h>
#include "TouchScreen.h"
#include <stdbool.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include <stdint.h>
#include "operations.h"
#include "uart.h"

bool operator_press = false;
bool operand_press = false;
int char_convert;
char current_operator;
char buffer[30];
char text_displayed[20]; // String of text
int result = 0;          // so many global variables bro we're cooked
state_t current_state;
int num1 = 0; // initialize num1
int num2 = 0; // initialize num2
bool equal_press = false;
bool clear_press = false;
bool num2Track =  false;

char get_button(int16_t x, int16_t y)
{
    char button_pressed = ' ';

    if (x < 80 && x > 11)
    {
        if (y > 43 && y < 90)
        {
            button_pressed = '7';
        }
        else if (y > 96 && y < 145)
        {
            button_pressed = '4';
        }
        else if (y > 148 && y < 196)
        {
            button_pressed = '1';
        }
        else if (y > 200 && y < 240)
        {
            button_pressed = '0';
        }
    }
    else if (x < 156 && x > 85)
    {
        if (y > 43 && y < 90)
        {
            button_pressed = '8';
        }
        else if (y > 96 && y < 145)
        {
            button_pressed = '5';
        }
        else if (y > 148 && y < 196)
        {
            button_pressed = '2';
        }
        else if (y > 200 && y < 240)
        {
            button_pressed = 'C';
            clear_press = true;
        }
    }
    else if (x < 230 && x > 161)
    {
        if (y > 43 && y < 90)
        {
            button_pressed = '9';
        }
        else if (y > 96 && y < 145)
        {
            button_pressed = '6';
        }
        else if (y > 148 && y < 196)
        {
            button_pressed = '3';
        }
        else if (y > 200 && y < 240)
        {
            button_pressed = '=';
            equal_press = true;
        }
    }
    else if (x < 308 && x > 236)
    {
        if (y > 43 && y < 90)
        {
            button_pressed = '+';
        }
        else if (y > 96 && y < 145)
        {
            button_pressed = '-';
        }
        else if (y > 148 && y < 196)
        {
            button_pressed = 'x';
        }
        else if (y > 200 && y < 240)
        {
            button_pressed = '/';
        }
    }

    if (button_pressed != ' ')
    {
        if (button_pressed >= '0' && button_pressed <= '9')
        {
            char_convert = button_pressed - '0'; // conversion to int
            operand_press = true;
        }
        else if (button_pressed == '+' || button_pressed == '-' || button_pressed == 'x' || button_pressed == '/')
        {
            operator_press = true;
            current_operator = button_pressed;
        }
    }

    return button_pressed;
}
bool num1_stored;
bool num2_stored;


void calculator_init()
{
    current_state = INIT; // start in init state
    num1 = 0;             // reset num1
    num2 = 0;             // reset num2
    uart_print_fsm_state("INIT");
    num1_stored = false; // reset num1 stored
    num2_stored = false; // reset num2 stored
}

void calculator_fsm()
{
    switch (current_state)
    {
    case INIT:
        if (operand_press)
        {
            current_state = NUM;
            num1_stored = true;
            num1 = char_convert;
        }
        else if (operator_press)
        {
           // current_state = OPERATOR;
          //  num1_stored = false;
            current_state = INIT;
        }
        break;

    case NUM:
        if (operator_press && num1_stored)
        {
            current_state = OPERATOR;
           // num1_stored = false;
            
        }
        break;

    case OPERATOR:
        if (operand_press && num1_stored ) //&& num1_sored
        { 
            num2_stored = true;
           
            //num2 = char_convert;
            if (equal_press && num2_stored)
            {
                 num2 = char_convert;
                 current_state = EQUALS;
               // num1 = num1 * 10 + num2; //right now this condition isnt being met
            }
         
        }

        else if (equal_press)
        {
            current_state = EQUALS;
        }
        break;

    case EQUALS:
        switch (current_operator)
        {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case 'x':
            result = num1 * num2;
            break;
        case '/':
            result = num1 / num2;
            break;
        }
        current_state = DISPLAY;
        break;

    case DISPLAY:
        tft_setCursor(100, 15); 
        tft_setTextColor(ILI9340_WHITE);
        sprintf(buffer, "    %d", result);
        tft_writeString(buffer);
        current_state = CLEAR;
        break;

    case CLEAR:
        if (clear_press)
        {
           
            tft_setCursor(100, 15);
            tft_setTextColor(ILI9340_BLACK); 
            sprintf(buffer, "    "); 
            tft_writeString(buffer); 

          
            num1 = 0;
            num2 = 0;
            result = 0;

           
            tft_setTextColor(ILI9340_WHITE); 
            sprintf(buffer, "    "); 
            tft_writeString(buffer);

            
            current_state = INIT; 
            clear_press = false;
            operator_press = false; 
            operand_press = false;
            equal_press = false; 
        }
        break; 
    }
}




    

