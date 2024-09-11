cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(Lab2)

pico_sdk_init()

add_executable(Lab2
        main.c
    	led_out.c
    	sw_in.c
        )

# pull in common dependencies
target_link_libraries(Lab2 pico_stdlib pico_bootsel_via_double_reset)

# Specify include directories
target_include_directories(Lab2 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# create map/bin/hex file etc.
pico_add_extra_outputs(Lab2)

