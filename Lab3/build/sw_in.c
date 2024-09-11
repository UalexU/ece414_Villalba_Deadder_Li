#include "sw_in.h"
#include <stdbool.h>

void sw_in_init(){
    gpio_init(SW1_PIN);
    gpio_init(SW2_PIN);
    gpio_set_dir(SW1_PIN, GPIO_IN); // set 
    gpio_set_dir(SW2_PIN, GPIO_IN); // set 
    gpio_pull_up(SW1_PIN); 
    gpio_pull_up(SW2_PIN);
}

bool sw_in_read1(){
    return gpio_get(SW1_PIN) == 0;  // Return true if pin is low (switch closed)
}

bool sw_in_read2(){
    return gpio_get(SW2_PIN) == 0;  // Return 1 if pin is low (switch closed)
}