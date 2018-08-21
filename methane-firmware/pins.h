#pragma once

#include "bitop.h"
#include "config.h"
#include "portmacros.h"

// LED
#define LED_PORT 1
#define LED 0

//UCA0
#define UART_PORT 2
#define UART_TX 0
#define UART_RX 1


// CC1200 915MHz RF 
#define RF_SPIIO_PORT 1
#define RF_MOSI 6
#define RF_MISO 7

#define RF_SCK_PORT 2
#define RF_SCK 2

#define RF_CS_PORT 1
#define RF_CS 5

#define RF_GPIO_PORT 1
#define RF_GPIO0 3
#define RF_GPIO2 4

#define TEMP_DATA_PORT 2
#define TEMP_DATA 4

#define RF_RESET_PORT 3
#define RF_RESET 4

#define acc_spi_send_receive spi_UCB0_send_receive
#define acc_spi_init spi_UCB0_init

#define rf_spi_init spi_UCB0_init
#define rf_spi_send_receive spi_UCB0_send_receive 


void pins_init();
