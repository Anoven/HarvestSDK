#ifndef SPI_H
#define SPI_H
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "pins.h"
#include "stm32f10x_dma.h"

//slave rx buffer size
#define RXTXBufferSize 8



void spi1_init(unsigned int clocksettings);
//void spi2_init(unsigned int clocksettings);
void SPI_Slave_and_DMA_Configuration(void);

unsigned char rf_spi_send_receive(unsigned char send);
void cc1200_select( void );
void cc1200_unselect( void );
void cc1200_wait_miso( void );

#endif



