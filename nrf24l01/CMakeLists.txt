project(nrf24l01)

add_executable(nrf24l01
        src/NRF24.cpp
        )

target_include_directories(nrf24l01 PUBLIC
	inc
)

set(CMAKE_CXX_STANDARD 17)

# pull in common dependencies
target_link_libraries(nrf24l01 pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(nrf24l01)

# add url via pico_set_program_url
example_auto_set_url(nrf24l01)

# enable usb output, disable uart output
pico_enable_stdio_usb(nrf24l01 1)
pico_enable_stdio_uart(nrf24l01 0)
