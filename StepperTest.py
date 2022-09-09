from machine import Pin, PWM, ADC
import utime
import _thread

# Maximum frequency the motor can withstand before stalling
# Tested for NEMA 11s @8.2V (Li-Ion -> Current not a problem)
fMax = 1850  
# Minimum frequency could be anything, just don't keep the clock pin high for 3 hours.
fMin = 500
stepFreq = 0

pot = ADC(28)
potPos = 0

totalSteps = 0;

stby = Pin(2, Pin.OUT)
stepClk = Pin(3, Pin.OUT)
direction = Pin(4, Pin.OUT)

EN = Pin(5, Pin.OUT)
M0 = Pin(6, Pin.OUT)
M1 = Pin(7, Pin.OUT)
M2 = Pin(8, Pin.OUT)

# Setting the resolution of each motor, all 0s is the lowest resolution.
M0.value(0 )
M1.value(0)
M2.value(0)

# Standby low will run no current through the motor
stby.value(1)

# Enable set low will disable the motor.
EN.value(1)

print("Ready")

def readPot():
    global potPos
    global totalSteps
    while True:
        potPos = (pot.read_u16())
        print("Pot: " +  str(potPos) + "\t Freq x10: " + str(10 *stepFreq) + "\t Steps this direction: " + str(totalSteps))
        # print(1000/(stepFreq + 1))
        utime.sleep_ms(25)
        
_thread.start_new_thread(readPot,   ())

# Micropython doesn't have a native linear interpolation function so I have to sodding make my own now smh
def map(inputVal_, inMin_, inMax_, outMin_, outMax_):
    return((inputVal_ - inMin_) * (outMax_ - outMin_) / (inMax_ - inMin_) + outMin_)

while True:
    # print(potPos)
    # ADCs are rubbish they require delays between readings.
    # Fortunately we're going to be using delays for the fucking stepper motor so we're good.
    
    # Sets the step clock to 0 at the start of every cycle
    stepClk.value(0)
    
    if potPos > 35500:
        EN.value(1)
        stepFreq = round(map(potPos, 35500, 64000, fMin, fMax))
        direction.value(0)
    elif potPos < 30000:
        EN.value(1)
        stepFreq = round(map(potPos, 1000, 30000, fMax, fMin))
        direction.value(1)
    else:
        EN.value(0)
        totalSteps = 0
    
        
    if stepFreq > (fMax - 1):
            stepFreq = fMax
    elif stepFreq < (fMin + 1):
            stepFreq = fMin
            
    utime.sleep_ms(round(1000/stepFreq))
    stepClk.value(1)
    totalSteps = totalSteps + 1

