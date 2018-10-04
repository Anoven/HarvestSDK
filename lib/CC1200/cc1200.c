/*	@file cc1200.c
 *
 *	@brief
 *
 */
#include <stdio.h>
#include "stm32f10x_spi.h"
#include "cc1200.h"
#include "spi.h"
#include "pins.h"
#include "cc1200_spi.h"
#define MAX_DATA_LENGTH 128
static cc1200_status_t cc1200_status;
volatile uint8_t rx_buffer[128];
volatile uint8_t rx_bytes;
volatile uint8_t packet_available = 0;
volatile uint8_t crc_ok = 0;

void cc1200_init() {
	spi2_init(0);
	//printf("spi init done \n\r");
	cc1200_reset();
	//printf("reset done \n\r");
	cc1200_write_preferred_settings();
	cc1200_set_address();
    //calibrate radio
    cc1200_spi_strobe(CC120X_SCAL);

    cc1200_calibrate_RC_osc();
	//cc1200_int_enable(); //now done in main
}

void cc1200_reset() {
	// hardware reset with reset pin
	GPIO_ResetBits(CC1200_Reset_Port, CC1200_Reset_Pin);
	//delay(10000);
	GPIO_SetBits(CC1200_Reset_Port, CC1200_Reset_Pin);
	//delay(10000);

	// software reset with command strobe
	//printf("before SXRES stroble \n\r");
	cc1200_spi_strobe(CC120X_SRES);
	//printf("after SXRES stroble \n\r");
	cc1200_select();
	cc1200_wait_miso();
	cc1200_unselect();
}

void cc1200_write_preferred_settings() {
	printf("writing settings to cc1200 \n\r");
	for(uint8_t i=0; i<sizeof(preferredSettings)/sizeof(registerSetting_t); i++) {
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
	uint8_t addr = 0x0B;
	cc1200_spi_write_reg(CC120X_DEV_ADDR,addr);
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

	packet_available = 0;
	cc1200_spi_strobe(CC120X_STX);

	//TODO enter lpm 3 to save energy

	// wait for exit from TX state
	//while(cc1200_spi_read_extended_reg(CC120X_MARCSTATE) == 51){
	//printf("%u\n",	cc1200_spi_read_extended_reg(CC120X_MARCSTATE));
	//}

	printf("packet before = %d ,",packet_available);
	while(!packet_available);
	printf("after wait packet_avail = %d",packet_available);
	packet_available = 0;
	return 1;
}
uint8_t cc1200_send_packet(uint8_t *packet) {

	uint8_t marcstate;
	uint8_t len = *packet;

	cc1200_enter_idle();
	//marcstate = cc1200_spi_read_extended_reg(CC120X_MARCSTATE) & 0x1F;
	//printf("marcstate is %d ",marcstate);
	cc1200_spi_strobe(CC120X_SFSTXON); // enable frequency synthesizer
	//marcstate = cc1200_spi_read_extended_reg(CC120X_MARCSTATE) & 0x1F;
	//printf("marcstate is %d ",marcstate);
	if(!(len > (MAX_DATA_LENGTH-2))) {
		cc1200_write_tx_fifo(packet,(len+1));

		//marcstate = cc1200_spi_read_extended_reg(CC120X_MARCSTATE) & 0x1F;
		//printf("marcstate is %d ",marcstate);
		cc1200_status = CC120X_STATE_TX;

		packet_available = 0;
		cc1200_spi_strobe(CC120X_STX);
		//marcstate = cc1200_spi_read_extended_reg(CC120X_MARCSTATE) & 0x1F;
		//printf("marcstate is %d ",marcstate);
		//TODO enter lpm 3 to save energy

		// wait for exit from TX state
		//while(cc1200_spi_read_extended_reg(CC120X_MARCSTATE) == 51){
		//printf("%u\n",	cc1200_spi_read_extended_reg(CC120X_MARCSTATE));
		//}
		//packet_available = 1; //only for testing
		//printf("packet available = %d", packet_available);
		while(!packet_available);
		packet_available = 0;
		uint8_t marcstate = cc1200_spi_read_extended_reg(CC120X_MARCSTATE) & 0x1F;
        //printf("TX %d \n",marcstate);
		return 1;
	}
	else {
		printf("len=%d\n",len);
		return 0;
	}
}


uint8_t cc1200_receive_packet() {
	uint8_t marcstate;
	cc1200_enter_rx();
//	cc1200_spi_strobe(CC120X_SFRX);
	rx_bytes = cc1200_spi_read_extended_reg(CC120X_NUM_RXBYTES);
//	printf("num of bytes = %d    \n",rx_bytes);
	if(rx_bytes != 0) {
		marcstate = cc1200_spi_read_extended_reg(CC120X_MARCSTATE);

		if((marcstate & 0x1F) == RX_FIFO_ERROR) {
			cc1200_spi_strobe(CC120X_SFRX);
		}
		else {
			cc1200_read_rx_fifo(rx_buffer,rx_bytes);
			if(rx_buffer[rx_bytes-1] & 0x80) {
//				printf("packet good \n");
				return 1;
			}
			else {
				printf("crc error \n");
				cc1200_spi_strobe(CC120X_SFRX);
				return 0;
			}
		}
	}
	else {
//		printf("rx_bytes is 0\n\r");
		//delay(5 ms); // to do -- why do i need this delay?
		return 0;
	}
	
	// if somehow we got here, something went terribly wrong
	return 0;
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

uint8_t cc1200_wait_for_rx(uint16_t timeout) {
	cc1200_enter_rx();
	uint8_t marcstate = cc1200_spi_read_extended_reg(CC120X_MARCSTATE) & 0x1F;
    //printf("wait marcstate %d \n",marcstate);
//	crc_ok = 0;
	//uint32_t timeout_ms= timeout ms;
	uint32_t timeout_ms = xTaskGetTickCount();
	//printf("timeout = %u, timeout ms = %lu \n",timeout,timeout_ms);
    if(timeout_ms > 0) {
		while(!crc_ok)
		{
			if(xTaskGetTickCount() - timeout_ms > timeout) {
				// timed out before receiving packet
				printf(" crc timeout \n");

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


void cc1200_write_tx_fifo(uint8_t *data, uint8_t len) {
	cc1200_spi_write_burst_reg(0x3F, data, len);
	return;
}

void cc1200_read_rx_fifo(uint8_t *data, uint8_t len) {
	for(int i=0; i<len; i++) {
		data[i] = cc1200_spi_read_reg(0xBF);
	}
}


void cc1200_automatic_rx_poll_en(void){

	cc1200_spi_strobe(CC120X_SWOR);

}


void cc1200_calibrate_RC_osc(void){
	uint8_t temp;

    // Read current register value
    temp =cc1200_spi_read_reg(CC120X_WOR_CFG0);
    // Mask register bit fields and write new values
    temp = (temp & 0xF9) | (0x02 << 1);
    printf("temp is %u \r\n",temp);
    // Write new register value
	cc1200_spi_write_reg(CC120X_WOR_CFG0,temp);

    // Strobe IDLE to calibrate the RCOSC
    cc1200_spi_strobe(CC120X_SIDLE);

    // Disable RC calibration
    temp = (temp & 0xF9) | (0x00 << 1);
    cc1200_spi_write_reg(CC120X_WOR_CFG0,temp);
}

void cc1200_xmit_preamble(){
	cc1200_spi_strobe(CC120X_STX);
	//delay(30000 ms);
	cc1200_spi_strobe(CC120X_SIDLE);
	
}

void cc1200_change_frequency(unsigned char freq_1,unsigned char freq_2){
	cc1200_spi_strobe(CC120X_SIDLE);
	cc1200_spi_write_extended_reg(CC120X_FREQ1&0x00FF,freq_1);
	cc1200_spi_write_extended_reg(CC120X_FREQ2&0x00FF,freq_2);
	
}
