project(press)

add_executable(press PRESS.cpp PRESS.h)

target_include_directories(press PUBLIC 
    inc
)

set(CMAKE_CXX_STANDARD 17)

# pull in common dependencies and additional i2c hardware support
target_link_libraries(press pico_stdlib hardware_i2c PRESS.h)


pico_enable_stdio_usb(press 1)
pico_enable_stdio_uart(press 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(press)

# add url via pico_set_program_url
example_auto_set_url(press)