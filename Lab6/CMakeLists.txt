cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(PID)

pico_sdk_init()

add_executable(PID)

target_sources(PID PRIVATE 
    ic_pio.c
    PID.c
    pwm_methods.c
    pwm_pin.c
    timer.c
    )

target_link_libraries(PID PRIVATE 
    pico_stdlib
    hardware_pwm 
    hardware_pio
    pico_bootsel_via_double_reset
    )

pico_add_extra_outputs(PID)