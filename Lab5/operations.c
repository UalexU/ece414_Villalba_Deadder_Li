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
int result = 0; // so many global variables bro we're cooked
state_t current_state;
int num1 = 0; // initialize num1
int num2 = 0; // initialize num2

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

void calculator_init()
{
    current_state = INIT; // start in init state
    num1 = 0;             // reset num1
    num2 = 0;             // reset num2
    uart_print_fsm_state("INIT"); 
    

}

void calculator_fsm()
{
    
    switch (current_state)
    {
    case INIT:
    
        if (operand_press)
        {
            num1 = char_convert; // start building num1
            current_state = NUM;
            operand_press = false; // reset
            uart_print_fsm_state("NUM"); 
        }
        break;

    case NUM:
        if (operand_press)
        {
            num1 = num1 * 10 + char_convert; // build num1
            sprintf(text_displayed, "%d", num1); // Add the number to be displayed
            //uart_debug(text_displayed); 
            operand_press = false;           // reset
            
        }
        else if (operator_press)
        {
            current_state = OPERATOR;
            operator_press = false; // reset
            uart_print_fsm_state("OPERATOR"); 
        }
        break;

    case OPERATOR:
        if (operand_press)
        {
            num2 = char_convert; // start building num2
            current_state = NUM2;
            uart_print_fsm_state("NUM2"); 
            operand_press = false; // reset
        }
        break;

    case NUM2:
        if (operand_press)
        {
            num2 = num2 * 10 + char_convert; // build num2
            operand_press = false;           // reset
        }
        else if (operator_press)
        {
            current_state = CALCULATOR; 
            uart_print_fsm_state("CALCULATOR"); 
            operator_press = false;     // reset
        }
        break;

    case CALCULATOR:
        // ensure we have both numbers and an operator
        if (current_operator && num1 != 0 && num2 != 0)
        {
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
                if (num2 != 0)
                {
                    result = num1 / num2;
                }
                else
                {
                    //work on this 9imlazuy)
                }
                break;
            }
            current_state = EQUALS; // move to equals state
            uart_print_fsm_state("EQUALS"); 
        }
        break;

    case EQUALS:
        if (operator_press && current_operator == '=')
        {
            tft_setCursor(20, 20);
            tft_setTextColor(ILI9340_WHITE);
            sprintf(buffer, "Result: %d", result);
            tft_writeString(buffer);
            current_state = INIT; // reset for new calculation
            uart_print_fsm_state("INIT"); 
            num1 = 0;             // reset num1
            num2 = 0;             // reset num2
            result = 0;           // reset result
        }
        break;
    }
}
