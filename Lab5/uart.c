#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "uart.h"

// Rename the uart_init function to avoid conflict
void my_uart_init(void)
{
    // Set the correct pins for UART
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Initialize UART
    uart_init(UART_ID, BAUD_RATE); // Call the SDK's uart_init
    stdio_init_all();              // Initialize stdio for debugging
}

// Print the current FSM state
void uart_print_fsm_state(const char *state)
{
    uart_puts(UART_ID, "Current FSM State: ");
    uart_puts(UART_ID, state);
    uart_puts(UART_ID, "\n");
}

// Print message indicating the left player should serve
void uart_print_left_serve(void)
{
    uart_puts(UART_ID, "Left Player Serve\n");
}

// Print message indicating the right player should serve
void uart_print_right_serve(void)
{
    uart_puts(UART_ID, "Right Player Serve\n");
}

// Print message indicating the left player lost
void uart_print_left_loss(void)
{
    uart_puts(UART_ID, "Left Player Lost the Point\n");
}

// Print message indicating the right player lost
void uart_print_right_loss(void)
{
    uart_puts(UART_ID, "Right Player Lost the Point\n");
}

void uart_debug(const char *string)
{
    uart_puts(UART_ID, string);
}