#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <stdio.h>
#include "pico/stdlib.h"
#include <stdint.h> 


char get_button(int16_t x, int16_t y);
void calculator_fsm();

typedef enum state{
    INIT,
    ADD,
    SUB,
    MULT,
    DIV,
    EQUAL
}state;

#endif