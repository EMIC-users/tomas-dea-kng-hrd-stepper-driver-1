
/*==================[inclusions]=============================================*/

#include "inc/StepperDriver_Motor.h"

/*==================[internal data]=========================================*/

static uint32_t stepCount = 0;
static uint32_t stepMax = STEPPER_Motor_DEFAULT_MAX_STEPS;
static uint8_t  ustepRelation = 1;
static uint16_t moveRemaining = 0;
static uint32_t semiperiodMs = 5;
static uint32_t lastStepTime = 0;
static uint8_t  homeState = 4;  // 0-3: calibrating, 4: relative only
static uint8_t  homeDir = 0;
static uint8_t  limitPrev = 1;

/*==================[external functions]====================================*/

void StepperDriver_Motor_init(void)
{
    // Control pins as outputs
    HAL_GPIO_PinCfg(Step, GPIO_OUTPUT);
    HAL_GPIO_PinCfg(Dir, GPIO_OUTPUT);
    HAL_GPIO_PinCfg(MS1, GPIO_OUTPUT);
    HAL_GPIO_PinCfg(MS2, GPIO_OUTPUT);
    HAL_GPIO_PinCfg(SLP, GPIO_OUTPUT);

    // Limit switch as input
    HAL_GPIO_PinCfg(LimitSw, GPIO_INPUT);

    // Initial state
    HAL_GPIO_PinSet(Step, GPIO_LOW);
    HAL_GPIO_PinSet(Dir, GPIO_LOW);
    HAL_GPIO_PinSet(MS1, GPIO_LOW);
    HAL_GPIO_PinSet(MS2, GPIO_LOW);
    HAL_GPIO_PinSet(SLP, GPIO_HIGH); // Active (not sleeping)

    stepCount = 0;
    moveRemaining = 0;
    semiperiodMs = 1000 / (STEPPER_Motor_DEFAULT_SPEED * 2);
}

void StepperDriver_Motor_setMicrostep(uint8_t microsteps)
{
    ustepRelation = microsteps;
    switch (microsteps)
    {
        case 1:  // Full step
            HAL_GPIO_PinSet(MS1, GPIO_LOW);
            HAL_GPIO_PinSet(MS2, GPIO_LOW);
            break;
        case 2:  // Half step
            HAL_GPIO_PinSet(MS1, GPIO_HIGH);
            HAL_GPIO_PinSet(MS2, GPIO_LOW);
            break;
        case 4:  // Quarter step
            HAL_GPIO_PinSet(MS1, GPIO_LOW);
            HAL_GPIO_PinSet(MS2, GPIO_HIGH);
            break;
        case 8:  // Eighth step
            HAL_GPIO_PinSet(MS1, GPIO_HIGH);
            HAL_GPIO_PinSet(MS2, GPIO_HIGH);
            break;
    }
    stepMax = 200 * ustepRelation; // 200 full steps = 1 revolution
}

void StepperDriver_Motor_setSpeed(uint16_t stepsPerSecond)
{
    if (stepsPerSecond == 0) stepsPerSecond = 1;
    if (stepsPerSecond > 500) stepsPerSecond = 500;
    semiperiodMs = 1000 / (stepsPerSecond * 2);
    if (semiperiodMs == 0) semiperiodMs = 1;
}

void StepperDriver_Motor_move(uint8_t direction, uint16_t steps)
{
    if (direction == 2)
    {
        // Toggle direction
        HAL_GPIO_PinToggle(Dir);
    }
    else
    {
        HAL_GPIO_PinSet(Dir, direction ? GPIO_HIGH : GPIO_LOW);
    }
    moveRemaining = steps;
}

void StepperDriver_Motor_sleep(uint8_t state)
{
    switch (state)
    {
        case 0: HAL_GPIO_PinSet(SLP, GPIO_HIGH); break;  // Wake
        case 1: HAL_GPIO_PinSet(SLP, GPIO_LOW);  break;  // Sleep
        case 2: HAL_GPIO_PinToggle(SLP); break;
    }
}

void StepperDriver_Motor_goHome(uint8_t direction)
{
    homeDir = direction;
    homeState = direction ? 1 : 0;
    HAL_GPIO_PinSet(Dir, direction ? GPIO_HIGH : GPIO_LOW);
    moveRemaining = 0xFFFF; // Move until limit switch
}

void StepperDriver_Motor_goTo(uint32_t position)
{
    if (homeState != 2 && homeState != 3) return; // Must be homed first

    if (position > stepMax) position = stepMax;

    if (position > stepCount)
    {
        HAL_GPIO_PinSet(Dir, GPIO_HIGH);
        moveRemaining = position - stepCount;
    }
    else if (position < stepCount)
    {
        HAL_GPIO_PinSet(Dir, GPIO_LOW);
        moveRemaining = stepCount - position;
    }
}

void StepperDriver_Motor_poll(void)
{
    // Check limit switch
    uint8_t limitCurrent = HAL_GPIO_PinGet(LimitSw);
    if (limitCurrent == 0 && limitPrev == 1)
    {
        // Limit switch activated
        if (homeState == 0 || homeState == 1)
        {
            moveRemaining = 0;
            stepCount = 0;
            homeState = homeDir ? 3 : 2;
        }

        StepperDriver_Motor_onLimitSwitch();
    }
    limitPrev = limitCurrent;

    // Step pulse generation
    if (moveRemaining > 0)
    {
        uint32_t now = getSystemMilis();
        if (now - lastStepTime >= semiperiodMs)
        {
            lastStepTime = now;
            HAL_GPIO_PinToggle(Step);

            // Count on falling edge
            if (HAL_GPIO_PinGet(Step) == 0)
            {
                if (moveRemaining != 0xFFFF)
                    moveRemaining--;

                // Track absolute position
                if (homeState == 2 || homeState == 3)
                {
                    if (HAL_GPIO_PinGet(Dir))
                        stepCount++;
                    else if (stepCount > 0)
                        stepCount--;
                }
            }
        }
    }
}

