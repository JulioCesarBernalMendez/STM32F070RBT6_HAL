#include "stm32f0xx.h"

void SysTick_Handler( void )
{
    /* increment systick global timer */
    HAL_IncTick();
}
