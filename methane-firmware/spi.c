#include <msp430.h>
#include "bitop.h"

void spi_UCA1_init(unsigned int clocksettings) {
	// Put state machine in reset
	UCA1CTLW0 = UCSWRST;
	
	// 3-pin, 8-bit SPI master, MSB
	UCA1CTLW0 |= UCMST + UCSYNC + UCMSB + clocksettings;
	
	// SMCLK
	UCA1CTLW0 |= UCSSEL_2;
	
	UCA1BR0 = 0x04;
	UCA1BR1 = 0;
	
	UCA1MCTLW = 0; //No modulation
	
	//Start SPI hardware
	clear_bits(UCA1CTLW0,UCSWRST);
}

unsigned char spi_UCA1_send_receive(unsigned char send) {
	UCA1TXBUF=send;
	
	///wait until it recieves
	while (!(UCA1IFG&UCRXIFG));
	
	return UCA1RXBUF;
}

void spi_UCB0_init(unsigned int clocksettings) {
	// Put state machine in reset
	UCB0CTLW0 = UCSWRST;
	
	// 3-pin, 8-bit SPI master, MSB
	UCB0CTLW0 |= UCMST + UCSYNC + UCMSB + clocksettings;
	
	// SMCLK
	UCB0CTLW0 |= UCSSEL_2;
	
	UCB0BR0 = 0x04;
	UCB0BR1 = 0;
	
	//Start SPI hardware
	clear_bits(UCB0CTLW0,UCSWRST);
}

unsigned char spi_UCB0_send_receive(unsigned char send) {
	UCB0TXBUF=send;
	
	///wait until it recieves
	while (!(UCB0IFG&UCRXIFG));
	
	return UCB0RXBUF;
}
