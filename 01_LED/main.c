#include "main.h"

void GPIOA_Init( void );

int main( void )
{
    /* initialize GPIOA peripheral */
    GPIOA_Init();

    /* set GPIOA5 (board LED) HIGH */
    HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_SET );

    while ( 1 )
    {

    }

    return 0;
}

void GPIOA_Init( void )
{
    GPIO_InitTypeDef GPIOA_Handler;

    /* enable GPIOA clock */
     __HAL_RCC_GPIOA_CLK_ENABLE();

    /* configure GPIOA5 as output */
    GPIOA_Handler.Pin   = GPIO_PIN_5;
    GPIOA_Handler.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIOA_Handler.Pull  = GPIO_NOPULL;
    GPIOA_Handler.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init( GPIOA, &GPIOA_Handler );
}
