#ifndef FSM_H
#define FSM_H
#include "stdbool.h"

//Variables 
static int serve;
static bool dir_right; // direction dictates which way it moves (true for right, false for left)
static bool win; //left = 0, right = 1
// Function to initialize the FSM
void fsm_init(void);

// Function to run the FSM logic
void fsm_run();

static int initial_server; 
#endif