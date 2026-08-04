#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "inc/userFncFile.h"
#include "inc/systemTimer.h"
#include "inc/led_Led1.h"
#include "inc/led_Led2.h"
#include "inc/timer_api1.h"
#include "inc/StepperDriver_Motor.h"
#include "inc/conversionFunctions.h"
#include "inc/EMICBus.h"

void onReset()
{
    LEDs_Led1_state(1);
    pI2C("PABOOT\t1");
    setTime1(1500, 'T');
}


void etOut1()
{
    StepperDriver_Motor_sleep(0);
    StepperDriver_Motor_setMicrostep(8);
    StepperDriver_Motor_setSpeed(50);
    StepperDriver_Motor_goHome(0);
    pI2C("PAGOHOME\t1");
}


void StepperDriver_Motor_onLimitSwitch()
{
    StepperDriver_Motor_goTo(300);
    LEDs_Led2_state(1);
    pI2C("PAHOME\t1");
}



