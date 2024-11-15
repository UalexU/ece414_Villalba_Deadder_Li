
#include "stdio.h"
#include "pico/stdlib.h"
#include "pwm_pin.h"
#include "pwm_methods.h"

int32_t max (uint32_t a, uint32_t b) {
    if (a > b) return a;
    else return b;
}

int32_t min (uint32_t a, uint32_t b) {
    if (a < b) return a;
    else return b;
}

//uint16_t pwm_level = 0x8000;  // start with a 50% duty cycle

int pwd_init() {
    
    //stdio_init_all();
    printf("Setting OC limit to %x\n", pwm_level);
    pwm_pin_init(pwm_level);
    
}
