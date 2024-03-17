project(step)

add_executable(step
        src/STEPS.cpp
        src/example.cpp
        )

target_include_directories(step PUBLIC
inc
)

set(CMAKE_CXX_STANDARD 17)

# pull in common dependencies
target_link_libraries(step pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(step)

# add url via pico_set_program_url
example_auto_set_url(step)

# enable usb output, disable uart output
pico_enable_stdio_usb(step 1)
pico_enable_stdio_uart(step 0)
