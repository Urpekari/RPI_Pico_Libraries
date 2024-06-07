cmake_minimum_required(VERSION 3.13)

set(PROGRAM_NAME RP2040-APCPP)
set(PICO_BOARD pico_w)

include(pico_sdk_import.cmake)

project(RP2040-APCPP)

pico_sdk_init()


#add_library(big $<TARGET_OBJECTS:press>)

add_executable(${PROGRAM_NAME}
    src/main.cpp
    src/htmldata.c
    src/PRESS.cpp
)

target_include_directories(${PROGRAM_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
) 

target_link_libraries(${PROGRAM_NAME}
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
    pico_stdlib
    hardware_i2c
)

pico_enable_stdio_usb(${PROGRAM_NAME} TRUE)
pico_enable_stdio_uart(${PROGRAM_NAME} FALSE)

pico_add_extra_outputs(${PROGRAM_NAME})