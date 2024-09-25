#ifndef FSM_H
#define FSM_H

// Enum to represent the different FSM states
typedef enum {
    INIT,       // Initial state: assign serve and light the corresponding LED
    WAITPUSHL,  // Waiting for the left player to press (ball moving to the left)
    WAITPUSHR,  // Waiting for the right player to press (ball moving to the right)
    MISSL,      // Left player missed, rightmost LED flashes
    MISSR       // Right player missed, leftmost LED flashes
} FSM_State;

// Function to initialize the FSM
void fsm_init(void);

// Function to run the FSM logic
void fsm_run(int btn1,int btn2);

#endif