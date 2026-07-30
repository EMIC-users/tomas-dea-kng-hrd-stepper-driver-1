#include <xc.h>
#include "inc/led_Led2.h"
#include "inc/gpio.h"
#include "inc/systemTimer.h"

void LEDs_Led2_init (void)
{
	HAL_GPIO_PinCfg(Led2, GPIO_OUTPUT);
}

void LEDs_Led2_state(uint8_t status)
{
	switch (status)
	{
		case 0:
			HAL_GPIO_PinSet(Led2, GPIO_LOW); // es mal
			break;
		case 1:
			HAL_GPIO_PinSet(Led2, GPIO_HIGH);
			break;
		case 2:
			if (HAL_GPIO_PinGet(Led2))
            {
				HAL_GPIO_PinSet(Led2,GPIO_LOW);
			}
			else 
			{
				HAL_GPIO_PinSet(Led2,GPIO_HIGH);
			}
			break;
	}
}



