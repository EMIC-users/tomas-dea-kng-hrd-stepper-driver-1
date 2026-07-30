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
    setTime1(3000, 'A');
}


void etOut1()
{
    seq = seq + 1;
    switch (seq)
    {
        case 1:
            pI2C("SEQ\t1-cfg");
            StepperDriver_Motor_sleep(0);
            StepperDriver_Motor_setMicrostep(8);
            StepperDriver_Motor_setSpeed(150);
            break;
        case 2:
            pI2C("SEQ\t2-abre400");
            StepperDriver_Motor_move(1, 400);
            break;
        case 3:
            pI2C("SEQ\t3-cierra400");
            StepperDriver_Motor_move(0, 400);
            break;
        case 4:
            pI2C("SEQ\t4-abre200");
            StepperDriver_Motor_move(1, 200);
            break;
        case 5:
            pI2C("SEQ\t5-cierra200");
            StepperDriver_Motor_move(0, 200);
            break;
        case 6:
            pI2C("SEQ\t6-fin");
            setTime1(0, 'T');
            break;
    }
}


void StepperDriver_Motor_onLimitSwitch()
{
    LEDs_Led2_state(1);
    pI2C("HOME\t1");
}



