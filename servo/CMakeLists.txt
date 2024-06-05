project(servo)

add_executable(servo
        src/SERVO.cpp
        )

target_include_directories(servo PUBLIC
	inc
)

set(CMAKE_CXX_STANDARD 17)

# pull in common dependencies
target_link_libraries(servo pico_stdlib hardware_pwm)

# create map/bin/hex file etc.
pico_add_extra_outputs(servo)

# add url via pico_set_program_url
example_auto_set_url(servo)

# enable usb output, disable uart output
pico_enable_stdio_usb(servo 1)
pico_enable_stdio_uart(servo 0)
