#include "main.h"

/* System frequency global variable (from system_stm32f0xx.c) */
extern uint32_t SystemCoreClock;

int main( void )
{   
    uint32_t ledTicks;

    /* Initialize HAL resources (systick is also enabled here and it
       generates a 1ms interrupt since it works as a time base for HAL) */
    HAL_Init();

    /* Initialize Board LED */
    LED_Init();
    
    /* NOTE: system frequency has been updated to 16MHz, refer to HAL_MspInit() */

    /* Get initial ledTicks counter */
    ledTicks = HAL_GetTick();

    while ( 1 )
    { 
      /* If 500 milliseconds have passed */
      if ( ( HAL_GetTick() - ledTicks ) >= LED_DELAY_500 )
      {  
         /* Toggle LED */
         HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 );

         /* update ledTicks counter */
         ledTicks = HAL_GetTick();
      }
    }

    return 0;
}

void LED_Init( void )
{
    GPIO_InitTypeDef GPIOA_Handler = { 0U };

    /* Enable GPIOA clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Configure GPIOA5 as output (LED on BOARD) */
    GPIOA_Handler.Pin   = GPIO_PIN_5;
    GPIOA_Handler.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIOA_Handler.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init( GPIOA, &GPIOA_Handler );
}
