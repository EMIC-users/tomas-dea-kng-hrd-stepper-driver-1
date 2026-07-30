
#ifndef STEPPERDRIVER_Motor_H_
#define STEPPERDRIVER_Motor_H_

/*==================[inclusions]=============================================*/

#include <stdint.h>
#include "gpio.h"
#include "systemTimer.h"

/*==================[macros]=================================================*/

#define STEPPER_Motor_DEFAULT_MAX_STEPS  1600
#define STEPPER_Motor_DEFAULT_SPEED      100

/*==================[init/poll]==============================================*/

void StepperDriver_Motor_init(void);

void StepperDriver_Motor_poll(void);

/*==================[functions]=============================================*/

void StepperDriver_Motor_setMicrostep(uint8_t microsteps);

void StepperDriver_Motor_setSpeed(uint16_t stepsPerSecond);

void StepperDriver_Motor_move(uint8_t direction, uint16_t steps);

void StepperDriver_Motor_sleep(uint8_t state);

void StepperDriver_Motor_goHome(uint8_t direction);

void StepperDriver_Motor_goTo(uint32_t position);

/*==================[events]================================================*/

extern void StepperDriver_Motor_onLimitSwitch(void);

/*==================[end of file]============================================*/
#endif

