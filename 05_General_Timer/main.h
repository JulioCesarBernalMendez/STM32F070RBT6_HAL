#ifndef MAIN_H
#define MAIN_H

    #include "stm32f0xx.h"

    void TIM3_Init( void );
    void LED_Init( void );

    void TIM3_Delay_us( uint32_t us );

    #define LED_DELAY_500  500U

#endif
