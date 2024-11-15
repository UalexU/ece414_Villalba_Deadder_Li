#include "pico/stdlib.h"
#include "stdio.h"

#ifndef PWD_METHODS_H
#define PWD_METHODS_H

int32_t min(uint32_t a, uint32_t b);

int32_t max(uint32_t a, uint32_t b);

int pwd_init();

extern uint16_t pwm_level; 

#endif