project(joyC)

add_executable(joyC
    src/JOYC.cpp
    src/example.cpp
    )

target_include_directories(joyC PUBLIC
	inc
)

set(CMAKE_CXX_STANDARD 17)

# pull in common dependencies
target_link_libraries(joyC
	pico_stdlib
	hardware_i2c
	)

# create map/bin/hex file etc.
pico_add_extra_outputs(joyC)

# add url via pico_set_program_url
example_auto_set_url(joyC)

# enable usb output, disable uart output
pico_enable_stdio_usb(joyC 1)
pico_enable_stdio_uart(joyC 0)
