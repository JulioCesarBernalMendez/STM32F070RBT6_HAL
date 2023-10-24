#include "main.h"

/* System frequency global variable (from system_stm32f0xx.c) */
extern uint32_t SystemCoreClock;

/* TIM3 handler structure */
TIM_HandleTypeDef TIM3_Handler;

int main( void )
{   
    /* Initialize HAL resources (systick is also enabled here and it
       generates a 1ms interrupt since it works as a time base for HAL) */
    HAL_Init();

    /* initialize TIM3 (1us time base) */
    TIM3_Init();

    /* Initialize Board LED */
    LED_Init();
    
    /* NOTE: system frequency has been updated to 48MHz, refer to HAL_MspInit() */

    while ( 1 )
    {
        /* Toggle LED */
        HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 );

        /* wait 100 us */
        TIM3_Delay_us( 100U );
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

void TIM3_Init( void )
{
    /* Enable TIM3 clock */
    __HAL_RCC_TIM3_CLK_ENABLE();

    TIM3_Handler.Instance = TIM3;
    /* For more details about PCLK = 48MHz please refer to hal_msp.c and the STM32F070RB clock_tree diagram */
    TIM3_Handler.Init.Prescaler         = 0x17U;              /* CK_CNT period = (1 / PCLK)(PSC + 1) = (1 / 48MHz)(23 + 1) = 0.5us */
    TIM3_Handler.Init.CounterMode       = TIM_COUNTERMODE_UP; /* Counter counts up (counts from 0 up to the auto-reload value) */
    TIM3_Handler.Init.Period            = 0x01U;              /* TIM3 reload value, when TIM3 counts to ARR + 1 (= 1 + 1 = 2), (0.5us)(2) = 1us has passed */
    TIM3_Handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init( &TIM3_Handler );                       /* Initialize TIM3 in time base mode */
}

/* NOTE: there's no HAL for TIMx timebase in polling mode (only interrupt mode), therefore if
         polling mode is desired, the TIMx update event flag must be manually evaluated and cleared
         using bare metal (lines 77 and 83 respectively) */
void TIM3_Delay_us( uint32_t us )
{
    uint32_t wait;

    /* start TIM3 */
    HAL_TIM_Base_Start( &TIM3_Handler );

    /* generate 'us' microseconds delay */
    for ( wait = 0U; wait < us; wait++ )
    {   
        /* wait for TIM3 update interrupt flag (1us) */
        while ( ( TIM3->SR & TIM_SR_UIF ) != TIM_SR_UIF )
        {
            /* do nothing */
        }

        /* clear TIM3 update interrupt flag */
        TIM3->SR &= ~TIM_SR_UIF;
    }
}
