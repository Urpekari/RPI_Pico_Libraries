cmake_minimum_required(VERSION 3.13)

set(PROGRAM_NAME PRESS)


pico_sdk_init()

add_executable(${PROGRAM_NAME}
    src/press.cpp 
)
#add_library(press OBJECT press.cpp)


target_include_directories(${PROGRAM_NAME} PUBLIC
    inc
)
target_link_libraries( ${PROGRAM_NAME}
    pico_stdlib
    hardware_i2c
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
)


