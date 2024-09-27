#ifndef UART_MODULE_H
#define UART_MODULE_H

// Initialize the UART communication
void my_uart_init(void);

// Print the current FSM state
void uart_print_fsm_state(const char *state);

// Print message indicating the left player should serve
void uart_print_left_serve(void);

// Print message indicating the right player should serve
void uart_print_right_serve(void);

// Print message indicating the left player lost
void uart_print_left_loss(void);

// Print message indicating the right player lost
void uart_print_right_loss(void);

void uart_debug(void);
#endif