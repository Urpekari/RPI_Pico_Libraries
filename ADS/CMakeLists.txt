project(ADS)

add_executable(ADS
    src/example.cpp
    src/ADS.cpp
    )

target_include_directories(ADS PUBLIC
	inc
)

set(CMAKE_CXX_STANDARD 17)

# pull in common dependencies
target_link_libraries(ADS
	pico_stdlib
	hardware_i2c
	)

# create map/bin/hex file etc.
pico_add_extra_outputs(ADS)

# add url via pico_set_program_url
example_auto_set_url(ADS)

# enable usb output, disable uart output
pico_enable_stdio_usb(ADS 1)
pico_enable_stdio_uart(ADS 0)
