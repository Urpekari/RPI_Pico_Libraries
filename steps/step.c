/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

bool togglePin(uint8_t pin, bool pinState);

int main() {

    const uint8_t stepper_enable = 13;
    const uint8_t stepper_stepClk = 14;
    const uint8_t stepper_stepDir = 15;

    bool stepperEnable = true;
    bool stepClkState = false;
    bool stepDirState = true;

    gpio_init(stepper_enable);
    gpio_set_dir(stepper_enable, GPIO_OUT);
    gpio_init(stepper_stepClk);
    gpio_set_dir(stepper_stepClk, GPIO_OUT);
    gpio_init(stepper_stepDir);
    gpio_set_dir(stepper_stepDir, GPIO_OUT);

    gpio_put(stepper_enable, stepperEnable);
    gpio_put(stepper_stepDir, stepDirState);

    while (true) {
        stepClkState = togglePin(stepper_stepClk, stepClkState);
        sleep_ms(5);
    }
}

bool togglePin(uint8_t pin, bool pinState){
    pinState = !pinState;
    gpio_put(pin, pinState);
    return pinState;
}
