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

/* User Variables */
uint16_t pct = 0;
uint16_t pasos = 0;
uint8_t cfg = 0;

void onReset()
{
    LEDs_Led1_state(1);
    pI2C("PABOOT\t1");
    setTime1(1500, 'T');
}


void etOut1()
{
    if (cfg == 0)
    {
        StepperDriver_Motor_sleep(0);
        StepperDriver_Motor_setMicrostep(8);
        StepperDriver_Motor_setSpeed(50);
        cfg = 1;
        StepperDriver_Motor_goHome(0);
    }
    else
    {
        pI2C("PAPOS\t%u", pct);
    }
}


void StepperDriver_Motor_onLimitSwitch()
{
    StepperDriver_Motor_goTo(300);
    LEDs_Led2_state(1);
    pct = 37;
    pI2C("PAHOME\t1");
    setTime1(2000, 'A');
}


void eI2C(char* tag, const streamIn_t* const msg)
{
    if (strncmp(tag, "PAREF", 5) == 0)
    {
        pct = streamIn_t_ptr_to_uint16_t((streamIn_t*)msg);
        if (pct > 100)
        {
            pct = 100;
        }
        pasos = pct * 8;
        StepperDriver_Motor_goTo(pasos);
    }
    else
    {
        /* default case - no action */
    }
}



