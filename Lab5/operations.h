#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <stdio.h>
#include "pico/stdlib.h"
#include <stdint.h> 


char get_button(int16_t x, int16_t y);
void calculator_fsm();
void calculator_init();
typedef enum {
    INIT,
    NUM,
    NUM2,
    OPERATOR,
    CALCULATOR,
    EQUALS,
    CLEAR,
    DISPLAY,
    ERROR
}state_t;

#endif