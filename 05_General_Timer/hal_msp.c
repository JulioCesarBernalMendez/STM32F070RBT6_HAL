#include "stm32f0xx.h"

/* This function is called by HAL_Init() */
void HAL_MspInit(void)
{
   /* Enable PLL, use HSI (= 8MHz) as its time source, subsequently configure
      AHB and APB prescalers in order to generate a 48MHz system frequency */

   RCC_OscInitTypeDef Osc_Handler = { 0U };
   RCC_ClkInitTypeDef Clk_Handler = { 0U };

   Osc_Handler.OscillatorType = RCC_OSCILLATORTYPE_HSI;          /* HSI is the oscillator to be configured */
   Osc_Handler.HSIState       = RCC_HSI_ON;                      /* Enable HSI */
   Osc_Handler.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT; /* Default HSI Trimming value (HSITRIM) */
   Osc_Handler.PLL.PLLState   = RCC_PLL_ON;                      /* Enable PLL */
   Osc_Handler.PLL.PLLSource  = RCC_CFGR_PLLSRC_HSI_PREDIV;      /* HSI / PREDIV (see next 2 lines) as PLL clock source (this feeds the PLLMUL) */
   /* Divide clock at PLLSRC mux (HSI) by 4 (= HSI / 4 = 8MHz / 4 = 2MHz) */
   Osc_Handler.PLL.PREDIV     = RCC_PREDIV_DIV1;                 /* ( PLL clock before PLLMUL ) = HSI (=8MHz) / 1 = 8MHz */
   Osc_Handler.PLL.PLLMUL     = RCC_PLL_MUL6;                    /* Multiply by 6, this results in a PLLCLK output = 48MHz */
   HAL_RCC_OscConfig( &Osc_Handler );

   Clk_Handler.ClockType      = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1; /* SYSCLK, HCLK and PCLK are the clocks to be configured */
   Clk_Handler.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;         /* Use PLLCLK (48MHz) as source clock for SYSCLK */
   Clk_Handler.AHBCLKDivider  = RCC_SYSCLK_DIV1;                 /* Do not divide SYSCLK, therefore HCLK = SYSCLK (=48MHz) / 1 = 48MHz */
   Clk_Handler.APB1CLKDivider = RCC_HCLK_DIV1;                   /* Do not divide HCLK, therefore PCLK = HCLK (=48MHz) / 1 = 48MHz */
   HAL_RCC_ClockConfig( &Clk_Handler, FLASH_LATENCY_0 );

   /* NOTE: when HAL_RCC_ClockConfig() is called, it also automatically adjusts the
            SysTick reload value for the 1ms timeout to occur needed by the HAL libraries */
}
