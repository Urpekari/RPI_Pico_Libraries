project(accelerometer)

add_executable(accelerometer
    src/accelerometer.cpp
    src/example.cpp
    )

target_include_directories(accelerometer PUBLIC
	inc
)

set(CMAKE_CXX_STANDARD 17)

# pull in common dependencies
target_link_libraries(accelerometer
	pico_stdlib 
	hardware_i2c
	)

# create map/bin/hex file etc.
pico_add_extra_outputs(accelerometer)

# add url via pico_set_program_url
example_auto_set_url(accelerometer)

# enable usb output, disable uart output
pico_enable_stdio_usb(accelerometer 1)
pico_enable_stdio_uart(accelerometer 0)