# Shift Register Controller

SN74HC595 shift register controller

## Parameters
###The main constructor takes 3 parameters:

**dataPin** = Pin 14 of the IC
This determines what goes on the outputs.

**latchPin** = Pin 12 of the IC
Enables the outputs when set high.

**clkPin** = Pin 11 of the IC
This determines when the next bit is sent on the dataPin.
