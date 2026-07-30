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
uint8_t seq = 0;
uint16_t paso = 0;

void onReset()
{
    LEDs_Led1_state(1);
    pI2C("BOOT\t1");
    setTime1(1500, 'T');
}


void etOut1()
{
    StepperDriver_Motor_sleep(0);
    StepperDriver_Motor_setMicrostep(8);
    StepperDriver_Motor_setSpeed(150);
    pI2C("LISTO\t1");
}


void StepperDriver_Motor_onLimitSwitch()
{
    LEDs_Led2_state(1);
    pI2C("HOME\t1");
}


void eI2C(char* tag, const streamIn_t* const msg)
{
    if (strncmp(tag, "ABRIR", 5) == 0)
    {
        paso = streamIn_t_ptr_to_uint16_t((streamIn_t*)msg);
        pI2C("PREA\t%u", paso);
        StepperDriver_Motor_move(1, paso);
        pI2C("POSA\t%u", paso);
    }
    else if (strncmp(tag, "CERRAR", 6) == 0)
    {
        paso = streamIn_t_ptr_to_uint16_t((streamIn_t*)msg);
        pI2C("PREC\t%u", paso);
        StepperDriver_Motor_move(0, paso);
        pI2C("POSC\t%u", paso);
    }
    else if (strncmp(tag, "IRA", 3) == 0)
    {
        paso = streamIn_t_ptr_to_uint16_t((streamIn_t*)msg);
        pI2C("PREI\t%u", paso);
        StepperDriver_Motor_goTo(paso);
        pI2C("POSI\t%u", paso);
    }
    else
    {
        /* default case - no action */
    }
}



