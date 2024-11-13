project(multisteps)

add_executable(multisteps
        src/MULTISTEPS.cpp
        src/example.cpp
        )

target_include_directories(multisteps PUBLIC
inc
)

set(CMAKE_CXX_STANDARD 17)

# pull in common dependencies
target_link_libraries(multisteps pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(multisteps)

# add url via pico_set_program_url
example_auto_set_url(multisteps)

# enable usb output, disable uart output
pico_enable_stdio_usb(multisteps 1)
pico_enable_stdio_uart(multisteps 0)
