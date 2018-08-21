#include <msp430.h>

#include "pins.h"

void pins_init() {
	// LED
	set_bit(DIR(LED_PORT),LED);
	clear_bit(OUT(LED_PORT),LED);
	
	// UART
	set_bit(DIR(UART_PORT),UART_TX);
	set_bit(OUT(UART_PORT),UART_TX);

	set_bit(SEL1(UART_PORT),UART_TX);
	set_bit(SEL1(UART_PORT),UART_RX);

	clear_bit(DIR(UART_PORT),UART_RX);


	//RF SPI
	set_bit(DIR(RF_SPIIO_PORT),RF_MOSI);
	clear_bit(SEL0(RF_SPIIO_PORT),RF_MOSI);
	set_bit(SEL1(RF_SPIIO_PORT),RF_MOSI);

	clear_bit(DIR(RF_SPIIO_PORT),RF_MISO);
	clear_bit(SEL0(RF_SPIIO_PORT),RF_MISO);
	set_bit(SEL1(RF_SPIIO_PORT),RF_MISO);

	set_bit(DIR(RF_SCK_PORT),RF_SCK);
	clear_bit(SEL0(RF_SCK_PORT),RF_SCK);
	set_bit(SEL1(RF_SCK_PORT),RF_SCK);

	set_bit(DIR(RF_CS_PORT),RF_CS);
	set_bit(OUT(RF_CS_PORT),RF_CS);
        
        
        
        set_bit(DIR(TEMP_DATA_PORT),TEMP_DATA);
	set_bit(OUT(TEMP_DATA_PORT),TEMP_DATA);
}
