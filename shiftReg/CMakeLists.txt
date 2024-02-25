add_executable(shiftReg
        src/SHIFTREG.cpp
        src/example.cpp
        )

target_include_directories(shiftReg PUBLIC
inc
)

# pull in common dependencies
target_link_libraries(shiftReg pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(shiftReg)

# enable usb output, disable uart output
pico_enable_stdio_usb(nrf 1)
pico_enable_stdio_uart(nrf 0)

# add url via pico_set_program_url
example_auto_set_url(shiftReg)
