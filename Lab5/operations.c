#include "ts_lcd.h"
#include "TFTMaster.h"
#include <inttypes.h>
#include "TouchScreen.h"
#include <stdbool.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include <stdint.h>
#include "operations.h"

bool operator_press = false;
bool operand_press = false;
int char_convert;
char current_operator;
char buffer[30];
int result = 0; //so many global variables bro we're cooked
state_t current_state;

char get_button(int16_t x, int16_t y)
{
    char button_pressed;

    if (x < 80 && x > 11)
    {
        if (y > 43 && y < 90)
        {
            button_pressed = '7';
            char_convert = button_pressed - '7'; // converting to int
            operand_press = true;
        }
        else if (y > 96 && y < 145)
        {
            button_pressed = '4';
            char_convert = button_pressed - '4';
            operand_press = true;
        }
        else if (y > 148 && y < 196)
        {
            button_pressed = '1';
            char_convert = button_pressed - '1';
            operand_press = true;
        }
        else if (y > 200 && y < 240)
        {
            button_pressed = '0';
            int char_convert = button_pressed - '0';
            operand_press = true;
        }
        else
            button_pressed = ' ';
    }

    else if (x < 156 && x > 85)
    {
        if (y > 43 && y < 90)
        {
            button_pressed = '8';
            char_convert = button_pressed - '8';
            operand_press = true;
        }
        else if (y > 96 && y < 145)
        {
            button_pressed = '5';
            char_convert = button_pressed - '5';
            operand_press = true;
        }
        else if (y > 148 && y < 196)
        {
            button_pressed = '2';
            char_convert = button_pressed - '2';
            operand_press = true;
        }
        else if (y > 200 && y < 240)
        {
            button_pressed = 'C';
        }
        else
            button_pressed = ' ';
    }

    else if (x < 230 && x > 161)
    {
        if (y > 43 && y < 90)
        {
            button_pressed = '9';
            char_convert = button_pressed - '9';
            operand_press = true;
        }
        else if (y > 96 && y < 145)
        {
            button_pressed = '6';
            char_convert = button_pressed - '6';
            operand_press = true;
        }
        else if (y > 148 && y < 196)
        {
            button_pressed = '3';
            char_convert = button_pressed - '3';
            operand_press = true;
        }
        else if (y > 200 && y < 240)
        {
            button_pressed = '=';
            current_operator = button_pressed;
            operator_press = true;
        }
        else
            button_pressed = ' ';
    }

    else if (x < 308 && x > 236)
    {
        if (y > 43 && y < 90)
        {
            button_pressed = '+';
            operator_press = true;
            current_operator = button_pressed;
        }
        else if (y > 96 && y < 145)
        {
            button_pressed = '-';
            operator_press = true;
            current_operator = button_pressed;
        }
        else if (y > 148 && y < 196)
        {
            button_pressed = 'x';
            operator_press = true;
            current_operator = button_pressed;
        }
        else if (y > 200 && y < 240)
        {
            button_pressed = '/';
            operator_press = true;
            current_operator = button_pressed;
        }
        else
            button_pressed = ' ';
    }
    else
        button_pressed = ' ';

    return button_pressed;
}


void calculator_init(void)
{
    current_state= INIT; // start in init state
}

void calculator_fsm()
{
    char current_operator;
    int num1; // store operands
    int num2;
    bool num1_pressed = false;
    bool num2_pressed = false; // ensure that num1 and 2 have been pressed before moving to the next state

    switch (current_state)
    {
    case INIT:
        if (operand_press)
        {
            char_convert = num1;
            num1_pressed = true;
            operand_press = false; // set it back to false
            current_state= NUM;
        }
        break;

    case NUM:
        if (operator_press && num1_pressed)
        {
            current_state = OPERATOR;
            operator_press = false;
        }
        break;

    case OPERATOR: // at this point num1 and an operator have been pressed
        if (operand_press)
        {
            num2 = char_convert;   // store the next operand
            num2_pressed = true;
            operand_press = false; // set back to false
           current_state= CALCULATOR;
        }
        break;

    case CALCULATOR:
        if (num1_pressed && num2_pressed)
        {
            
            // calculations
            switch (current_operator)
            {
            case '+': // add
                result = num1 + num2;
                current_state = EQUALS;
                break;
            case '-': // subtract
                result = num1 - num2;
               current_state = EQUALS;
                break;
            case 'x': // multiply
                result = num1 * num2;
                current_state = EQUALS;
                break;
            case '/': // divide -- need to work on divide by 0.
                result = num1 / num2;
                current_state = EQUALS;
                break;
            }
        }
        break;

    case EQUALS:
        if (current_operator == '=' && operand_press)
        {
            tft_setCursor(20, 20);
            tft_setTextColor(ILI9340_WHITE);
            sprintf(buffer, "button: %c", result);
            tft_writeString(buffer);
             current_state = INIT; 
        }
        break;
    }
}
