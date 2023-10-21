#include "stm32f0xx.h"

void SysTick_Handler( void )
{
    /* increment systick global counter variable */
    HAL_IncTick();
}
