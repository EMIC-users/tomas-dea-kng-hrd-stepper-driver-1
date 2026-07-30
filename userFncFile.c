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
    setTime1(1500, 'T');
}


void etOut1()
{
    StepperDriver_Motor_sleep(0);
    StepperDriver_Motor_setMicrostep(8);
    StepperDriver_Motor_setSpeed(150);
    pI2C("INIT\t1");
    StepperDriver_Motor_goHome(0);
}


void StepperDriver_Motor_onLimitSwitch()
{
    LEDs_Led1_state(0);
    LEDs_Led2_state(1);
    pI2C("HOME\t1");
}


void eI2C(char* tag, const streamIn_t* const msg)
{
    if (strncmp(tag, "PASO", 4) == 0)
    {
        if (streamIn_t_ptr_to_uint16_t((streamIn_t*)msg) <= 800)
        {
            StepperDriver_Motor_goTo(streamIn_t_ptr_to_uint32_t((streamIn_t*)msg));
            pI2C("ECOPASO\t$r", msg);
        }
    }
    else if (strncmp(tag, "ABRIR", 5) == 0)
    {
        if (streamIn_t_ptr_to_uint16_t((streamIn_t*)msg) <= 800)
        {
            StepperDriver_Motor_move(1, streamIn_t_ptr_to_uint16_t((streamIn_t*)msg));
            pI2C("ECOABRIR\t$r", msg);
        }
    }
    else if (strncmp(tag, "CERRAR", 6) == 0)
    {
        if (streamIn_t_ptr_to_uint16_t((streamIn_t*)msg) <= 800)
        {
            StepperDriver_Motor_move(0, streamIn_t_ptr_to_uint16_t((streamIn_t*)msg));
            pI2C("ECOCERR\t$r", msg);
        }
    }
    else
    {
        /* default case - no action */
    }
}



