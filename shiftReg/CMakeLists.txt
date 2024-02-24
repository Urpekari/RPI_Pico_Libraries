add_executable(shiftReg
        src/shiftReg.c
        )

# pull in common dependencies
target_link_libraries(shiftReg pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(shiftReg)

# add url via pico_set_program_url
example_auto_set_url(shiftReg)
