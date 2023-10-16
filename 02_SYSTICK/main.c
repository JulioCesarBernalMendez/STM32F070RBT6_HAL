#include "main.h"

int main( void )
{   
    /* initialize HAL resources */
    HAL_Init();

    /* note: systick peripheral is initialized when HAL_Init() is called 
             and it's configured to generate a 1ms interrupt */

    /* Initialize GPIOA (pin 5 as output) */
    GPIOA_Init();

    while ( 1 )
    {
        /* wait for 1 sec */
        HAL_Delay( 1000U );

        /* toggle GPIOA5 output state */
        HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 );
    }

    return 0;
}

void GPIOA_Init( void )
{
    GPIO_InitTypeDef GPIOA_Handler = { 0U };

    /* Enable GPIOA clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Initialize GPIOA5 as output */
    GPIOA_Handler.Pin   = GPIO_PIN_5;
    GPIOA_Handler.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIOA_Handler.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init( GPIOA, &GPIOA_Handler );
}
