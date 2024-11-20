
#include "pwm_pin.h"
#include "pwm_methods.h"
#include "pico/stdlib.h"
#include "stdio.h"
#include "ic.h"
#include "timer.h"

uint16_t pwm_level = 0x8000;

// Kp = Ku / 1.7, Ki = (Kp * 2) / Pu, Kd = (Kp * Pu) / 8;

int target_rpm = 2000; // target-rate Set the desired rotation speed in RPM.
int p;                 // p proportional-gain Set the PID proportional gain.
int i;                 // i integral-gain Set the PID integral gain.
int d;                 // d derivative-gain Set the PID derivative gain.

int check_rpm(int rpm)
{
  if (rpm > 2700)
  {
    rpm = 2700;
  }
  if (rpm < 0)
  {
    rpm = 0;
  }
  return rpm;
}
int Ki = 0;
int Ku = 4;
float Pu;
int Kp = 3;
int Kd = 0;

// Function to calculate PID coefficients based on Ku and Pu
void calculate_pid_coefficients()
{

  Pu = 60 / ((float)target_rpm);
  printf("Calculated PID Coefficients:\n");
  printf("Ku: %d, Pu: %.2f \n", Ku, Pu);
  Kp = (float)Ku / 1.7;
  Ki = (Kp * 2) / Pu;
  Kd = (Kp * Pu) / 8.0;

  printf("Kp: %.2f, Ki: %.2f, Kd: %.2f\n", Kp, Ki, Kd);
}

// When stead state found with kp then rename it as ku and use the following equation
// Oscillation period is Pu
// int Kp = Ku / 1.7, Ki = (Kp * 2) / Pu, Kd = (Kp * Pu) / 8;
int control_system()
{
  static int rpm_prev = 0; // Persistent previous RPM value
  static int integral = 0; // Persistent integral term
  static int error_prev = 0;

  uint32_t rpm = ic_getrpm(); // Get the current RPM
  printf("rpm=%u\n", rpm);

  int error = target_rpm - rpm;        // Proportional term (difference between target and current)
  int derivative = error - error_prev; // Rate of change of error

  // Update the integral term
  integral += error;

  // Clamp the integral to avoid windup
  int integ_max = 250;
  int integ_min = -250;
  if (integral > integ_max)
  {
    integral = integ_max;
  }
  else if (integral < integ_min)
  {
    integral = integ_min;
  }

  // Calculate the PID output

  int pwm_factored_level = (Kp * error) + (Ki * integral) - (Kd * derivative);
  // Damping factor for oscillations
  if (abs(error) < 100)
  {                            // Adjust threshold as needed
    pwm_factored_level *= 0.8; // Reduce response slightly for small errors
  }

  // Adjust and clamp the PWM level
  pwm_level = pwm_level + pwm_factored_level;

  if (pwm_level > 0xFFFF)
  {
    pwm_level = 0xFFFF;
  }
  else if (pwm_level < 0)
  {
    pwm_level = 0;
  }
  pwm_pin_set_level(pwm_level);
  // Update previous values
  rpm_prev = rpm;
  error_prev = error;

  sleep_ms(500); // Update every second
}

enum States
{
  Init,
  Ctrl
} state; // Enumeration for states

void Tick()
{
  switch (state)
  {
  case Init: // Perform initialization logic (e.g., reset variables)
    pwd_init();
    ic_init();
    //calculate_pid_coefficients();
    // Transition to Control state after initialization
    state = Ctrl;
    break;

  case Ctrl: // Control logic - adjusts the system based on sensor input
    control_system();
    // Remain in control state for continuous operation
    state = Ctrl;
    break;

  default:
    state = Init;
    break;
  }
}

// Function to process incoming UART commands
void process_uart_command(char *linebuf)
{
  int rpm, gain;

  // Skip leading spaces (useful if there's space between the command and the number)
  while (*linebuf == ' ')
  {
    linebuf++;
  }

  if (linebuf[0] == 's')
  { // Set target RPM
    if (sscanf(linebuf + 1, "%d", &rpm) == 1)
    { // Skip one character (the command letter)
      target_rpm = check_rpm(rpm);
      //calculate_pid_coefficients();
      printf("Target RPM set to: %d\n", target_rpm);
    }
    else
    {
      printf("Invalid RPM value.\n");
    }
  }
  else if (linebuf[0] == 'p')
  { // Set proportional gain
    if (sscanf(linebuf + 1, "%d", &gain) == 1)
    {
      Kp = gain;
      //calculate_pid_coefficients();
      printf("Proportional gain set to: %d\n", Kp);
    }
    else
    {
      printf("Invalid proportional gain value.\n");
    }
  }
  else if (linebuf[0] == 'k')
  { // Set Ku gain
    if (sscanf(linebuf + 1, "%d", &gain) == 1)
    {
      Ku = gain;
      //calculate_pid_coefficients();
      printf("Proportional gain set to: %d\n", Ku);
    }
    else
    {
      printf("Invalid proportional gain value.\n");
    }
  }
  else if (linebuf[0] == 'i')
  { // Set integral gain
    if (sscanf(linebuf + 1, "%d", &gain) == 1)
    {
      Ki = gain;
      //calculate_pid_coefficients();
      printf("Integral gain set to: %d\n", Ki);
    }
    else
    {
      printf("Invalid integral gain value.\n");
    }
  }
  else if (linebuf[0] == 'd')
  { // Set derivative gain
    if (sscanf(linebuf + 1, "%d", &gain) == 1)
    {
      Kd = gain;
      //calculate_pid_coefficients();
      printf("Derivative gain set to: %d\n", Kd);
    }
    else
    {
      printf("Invalid derivative gain value.\n");
    }
  }
  else
  {
    printf("Invalid command.\n");
  }
}

int main()
{
  char linebuf[100];
  int line_index = 0; // Index for the buffer
  stdio_init_all();
  while (1)
  {

    Tick();

    if (uart_is_readable(uart0))
    {
      char c = getchar(); // Read a character

      // If we receive a carriage return, process the command
      if (c == '\r')
      {
        linebuf[line_index] = '\0'; // Null-terminate the string
        if (line_index > 0)
        {
          process_uart_command(linebuf); // Process the command
        }
        else
        {
          printf("No command received.\n");
        }
        line_index = 0; // Reset the buffer index for the next command
      }
      else
      {
        // Store the character in the buffer, if it's not full
        if (line_index < sizeof(linebuf) - 1)
        {
          linebuf[line_index++] = c;
          putchar(c); // Echo the received character
        }
        else
        {
          printf("\nCommand too long. Try again.\n");
          line_index = 0; // Reset the buffer on overflow
        }
      }
    }
  }
}