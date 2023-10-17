#include "stm32f0xx.h"

/* This function is called by HAL_SPI_Init() in order to initialize
   the low-level resources in regards to the specified SPI handler */
void HAL_SPI_MspInit( SPI_HandleTypeDef *hspi )
{   
    GPIO_InitTypeDef GPIOA_Handler = { 0U };

    /* Enable GPIOA clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Configure GPIOA4 as output (SPI1_CS) */
    GPIOA_Handler.Pin   = GPIO_PIN_4;
    GPIOA_Handler.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIOA_Handler.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init( GPIOA, &GPIOA_Handler );

    /* Configure GPIO pins in alternate mode for SPI1.
       GPIOA5 = SPI1_SCK
       GPIOA6 = SPI1_MISO
       GPIOA7 = SPI1_MOSI */
    GPIOA_Handler.Pin       = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIOA_Handler.Mode      = GPIO_MODE_AF_PP;
    GPIOA_Handler.Alternate = GPIO_AF0_SPI1;
    HAL_GPIO_Init( GPIOA, &GPIOA_Handler );

    /* disable CS */
    HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, GPIO_PIN_SET );
}
