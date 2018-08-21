/*	@file cc1200.c
 *
 *	@brief
 *
 */

#include <msp430.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cc1200.h"
#include "spi.h"
#include "cc1200_spi.h"
#include "pins.h"
#include "bitop.h"
#include "clock.h"
#include "portmacros.h"
#include "device_info.h"
//#include "acc.h"
#include "config.h"
//#include "vibration.h"

#define MAX_DATA_LENGTH 128

static cc1200_status_t cc1200_status;
volatile uint8_t rx_buffer[130];
volatile uint8_t rx_bytes;
volatile uint8_t packet_available = 0;
volatile uint8_t crc_ok = 0;

void cc1200_echo_request(void) {

}

void cc1200_echo_reply(void) {

}

void cc1200_init(void) {
	
    rf_spi_init(UCCKPL*0+UCCKPH*1);
    cc1200_reset();
	 
    cc1200_write_preferred_settings();
    cc1200_set_address();
	
    //cc1200_int_enable();
       
    
}

void cc1200_int_enable(void) {

    set_bit(IE(RF_GPIO_PORT),RF_GPIO0);
    clear_bit(IFG(RF_GPIO_PORT),RF_GPIO0);

    set_bit(IE(RF_GPIO_PORT),RF_GPIO2);
    clear_bit(IFG(RF_GPIO_PORT),RF_GPIO2);
       
}

void cc1200_int_disable(void) {
	clear_bit(IE(RF_GPIO_PORT),RF_GPIO0);
}

void cc1200_reset(void) {
	clear_bit(OUT(RF_RESET_PORT),RF_RESET);
	delay(10 ms);
	set_bit(OUT(RF_RESET_PORT),RF_RESET);
	delay(10 ms);

	cc1200_spi_strobe(CC120X_SRES);

	cc1200_select();
	cc1200_wait_miso();
	cc1200_unselect();
}

void cc1200_write_preferred_settings() {
	for(int i=0; i<sizeof(preferredSettings)/sizeof(registerSetting_t); i++) {
		// extended registers take the form 0x2FXX where XX is the offset
		// in the extended register space
		if(preferredSettings[i].addr&0xFF00) {
			cc1200_spi_write_extended_reg(preferredSettings[i].addr&0x00FF,preferredSettings[i].data);
		}
		else {
			cc1200_spi_write_reg(preferredSettings[i].addr,preferredSettings[i].data);
		}
	}
}

void cc1200_set_address() {
	cc1200_spi_write_reg(CC120X_DEV_ADDR,device_get_id()+device_get_group());
}

void cc1200_enter_rx() {
	cc1200_enter_idle();
	cc1200_idle_rx();
	cc1200_status = CC120X_STATE_RX;
	return;
}

void cc1200_enter_idle() {
	cc1200_rx_idle();
	cc1200_status = CC120X_STATE_IDLE;
	return;
}

void cc1200_enter_sleep() {
	cc1200_rx_idle();
	cc1200_status = CC120X_STATE_IDLE;
	return;
}

void cc1200_set_output_power() {

}

uint8_t cc1200_load_packet(uint8_t * data) {
	uint8_t len = *data;

	cc1200_enter_idle();
	//cc1200_spi_strobe(CC120X_SFSTXON);

	if(!(len > (MAX_DATA_LENGTH-2))) {
		cc1200_write_tx_fifo(data,(len+1));
		return 1;
	}
	else {
		return 0;	
	}
}

uint8_t cc1200_send_loaded_packet() {
	cc1200_enter_idle();
	cc1200_spi_strobe(CC120X_SFSTXON); // enable frequency synthesizer


	cc1200_spi_strobe(CC120X_STX);

	//TODO enter lpm 3 to save energy

	// wait for exit from TX state
	//while(cc1200_spi_read_extended_reg(CC120X_MARCSTATE) == 51){
	//printf("%u\n",	cc1200_spi_read_extended_reg(CC120X_MARCSTATE));
	//}

	packet_available = 0;
	while(!packet_available);
	packet_available = 0;
	return 1;
}

uint8_t cc1200_send_packet(uint8_t * data) {
	uint8_t len = *data;

	cc1200_enter_idle();
	cc1200_spi_strobe(CC120X_SFSTXON); // enable frequency synthesizer

	if(!(len > (MAX_DATA_LENGTH-2))) {
		cc1200_write_tx_fifo(data,(len+1));

		cc1200_status = CC120X_STATE_TX;

		packet_available = 0;
		cc1200_spi_strobe(CC120X_STX);

		//TODO enter lpm 3 to save energy

		// wait for exit from TX state
		//while(cc1200_spi_read_extended_reg(CC120X_MARCSTATE) == 51){
		//printf("%u\n",	cc1200_spi_read_extended_reg(CC120X_MARCSTATE));
		//}

		while(!packet_available);
		packet_available = 0;
		return 1;
	}
	else {
		return 0;
	}
}


int cc1200_receive_packet() {
	uint8_t marcstate;

	rx_bytes = cc1200_spi_read_extended_reg(CC120X_NUM_RXBYTES);

	if(rx_bytes != 0) {
		marcstate = cc1200_spi_read_extended_reg(CC120X_MARCSTATE);

		if((marcstate & 0x1F) == RX_FIFO_ERROR) {
			cc1200_spi_strobe(CC120X_SFRX);
		}
		else {
			cc1200_read_rx_fifo(rx_buffer,rx_bytes);
			if(rx_buffer[rx_bytes-1] & 0x80) {
				return 1;
			}
			else {
				cc1200_spi_strobe(CC120X_SFRX);
				return 0;
			}
		}
	}
	else {
		//delay(5 ms); // to do -- why do i need this delay?
		return 0;
	}
	
	// if somehow we got here, something went terribly wrong
	return 0;
}

void cc1200_write_tx_fifo(uint8_t *data, uint8_t len) {
	cc1200_spi_write_burst_reg(0x3F, data, len);
	return;
}

void cc1200_read_rx_fifo(uint8_t *data, uint8_t len) {
	for(int i=0; i<len; i++) {
		data[i] = cc1200_spi_read_reg(0xBF);
	}
}

void cc1200_rx_idle(void) {
	// send idle strobe
	cc1200_spi_strobe(CC120X_SIDLE);

	// wait for cc1200 in idle state
	while(cc1200_spi_strobe(CC120X_SNOP) & 0xF0);

	return;
}

void cc1200_idle_rx(void) {
	// strobe into RX mode
	cc1200_spi_strobe(CC120X_SRX);
	return;
}

void cc1200_debug(void) {
	printf("CC1200 Register Configuration\n");
	printf("=============================\n");
	
	for(int i=0; i<0x2F; i++) {
		printf("0x%02X: 0x%02X\n",i,cc1200_spi_read_reg(i));
	}
	for(int i=0; i<0x40; i++) {
		printf("0x%02X: 0x%02X\n",i,cc1200_spi_read_extended_reg(i));
	}
	printf("=============================\n");
}

uint8_t cc1200_wait_for_rx(uint32_t timeout) {
	crc_ok = 0;
	
	if(timeout > 0) {
		while(!crc_ok)
		{
			if(timeout-- <= 0) {
				// timed out before receiving packet
				cc1200_spi_strobe(CC120X_SFRX);
				cc1200_enter_idle();
				return 0;
			}
		}
	}
	else {
		while(!crc_ok);	
	}
	
	// broke loop from CRC ok interrupt
	crc_ok = 0;
	cc1200_enter_idle();
	return 1;
}

void cc1200_xmit_preamble(){
	cc1200_spi_strobe(CC120X_STX);
	delay(30000 ms);
	cc1200_spi_strobe(CC120X_SIDLE);
	
}

void cc1200_change_frequency(unsigned char freq_1,unsigned char freq_2){
	cc1200_spi_strobe(CC120X_SIDLE);
	cc1200_spi_write_extended_reg(CC120X_FREQ1&0x00FF,freq_1);
	cc1200_spi_write_extended_reg(CC120X_FREQ2&0x00FF,freq_2);
	
}
