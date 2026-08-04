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
uint8_t fase = 0;
uint16_t paAct = 0;
uint16_t paRef = 0;
uint16_t cnt = 0;
uint8_t movia = 0;

void onReset()
{
    LEDs_Led1_state(1);
    pI2C("BOOT\t1");
    setTime1(1500, 'T');
}


void etOut1()
{
    switch ((uint8_t)(fase))
    {
        case 0:
            StepperDriver_Motor_sleep(0);
            StepperDriver_Motor_setMicrostep(2);
            StepperDriver_Motor_setSpeed(100);
            pI2C("PACONF\t1");
            fase = 1;
            cnt = 0;
            setTime1(100, 'A');
            break;
        case 1:
            StepperDriver_Motor_move(0, 1);
            cnt = cnt + 1;
            if (cnt >= 200)
            {
                fase = 4;
                pI2C("PAERR\tnohome");
            }
            break;
        case 2:
            StepperDriver_Motor_move(1, 1);
            cnt = cnt + 1;
            if (cnt >= 10)
            {
                paAct = 0;
                paRef = 0;
                movia = 0;
                fase = 3;
                pI2C("PAPOS\t0");
            }
            break;
        case 3:
            if (paAct < paRef)
            {
                StepperDriver_Motor_move(1, 1);
                paAct = paAct + 1;
                movia = 1;
            }
            else
            {
                if (paAct > paRef)
                {
                    StepperDriver_Motor_move(0, 1);
                    paAct = paAct - 1;
                    movia = 1;
                }
                else
                {
                    if (movia == 1)
                    {
                        pI2C("PAPOS\t%u", paAct);
                        movia = 0;
                    }
                }
            }
            break;
    }
}


void StepperDriver_Motor_onLimitSwitch()
{
    if (fase == 1)
    {
        fase = 2;
        cnt = 0;
        LEDs_Led2_state(1);
        pI2C("PAHOME\t1");
    }
}


void eI2C(char* tag, const streamIn_t* const msg)
{
    if (strncmp(tag, "PAREF", 5) == 0)
    {
        paRef = streamIn_t_ptr_to_uint16_t((streamIn_t*)msg);
        if (paRef > 100)
        {
            paRef = 100;
        }
    }
    else if (strncmp(tag, "HOMEAR", 6) == 0)
    {
        LEDs_Led2_state(0);
        cnt = 0;
        fase = 1;
    }
    else if (strncmp(tag, "ESTOP", 5) == 0)
    {
        paRef = 0;
    }
    else if (strncmp(tag, "FALLO", 5) == 0)
    {
        paRef = 0;
    }
    else
    {
        /* default case - no action */
    }
}



