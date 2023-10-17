#include "main.h"

/* GPIOA4: SPI1_CS
   GPIOA5: SPI1_SCK
   GPIOA6: SPI1_MISO
   GPIOA7: SPI1_MOSI */

/* SPI1 handler structure */
SPI_HandleTypeDef SPI1_Handler;

/* structure that indicates status of peripheral */
HAL_StatusTypeDef HAL_Status;

int main( void )
{   
    uint8_t msj[ 6 ] = "Hello";

    /* initialize HAL resources (systick is also enabled here and it
       generates a 1ms interrupt since it works as a time base for HAL) */
    HAL_Init();

    /* initialize SPI1 peripheral */
    SPI1_Init();

    /* send SPI dummy data for SCK line to settle */
    HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, GPIO_PIN_RESET );  /* enable CS */
    HAL_SPI_Transmit( &SPI1_Handler, &msj[ 5 ], 1U, 1000U );
    HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, GPIO_PIN_SET );    /* disable CS */

    while ( 1 )
    {   
        /* send string (including NULL character) over SPI1 */
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, GPIO_PIN_RESET );    /* enable CS */
        HAL_SPI_Transmit( &SPI1_Handler, msj, 6U, 1000U ); /* send current char */
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, GPIO_PIN_SET );      /* disable CS */

        /* wait 1 sec */
        HAL_Delay( 1000U );
    }

    return 0;
}

void SPI1_Init( void )
{
    /* Enable SPI1 clock */
    __HAL_RCC_SPI1_CLK_ENABLE();

    /* Configure SPI1 high-level resources */
    SPI1_Handler.Instance               = SPI1;
    SPI1_Handler.Init.Mode              = SPI_MODE_MASTER;
    SPI1_Handler.Init.Direction         = SPI_DIRECTION_2LINES;
    SPI1_Handler.Init.DataSize          = SPI_DATASIZE_8BIT;
    SPI1_Handler.Init.CLKPolarity       = SPI_POLARITY_LOW;
    SPI1_Handler.Init.CLKPhase          = SPI_PHASE_1EDGE;
    SPI1_Handler.Init.NSS               = SPI_NSS_HARD_INPUT;
    SPI1_Handler.Init.NSSPMode          = SPI_NSS_PULSE_ENABLE;
    SPI1_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2; /* SYSCLK = 8MHZ (default), SPI = PCLK (= SYSCLK ) / 2 = 4MHz */
    SPI1_Handler.Init.FirstBit          = SPI_FIRSTBIT_MSB;
    SPI1_Handler.Init.TIMode            = SPI_TIMODE_DISABLE;
    SPI1_Handler.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
    HAL_SPI_Init( &SPI1_Handler );
}
