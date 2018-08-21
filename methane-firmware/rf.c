#include "rf.h"
#include "spi.h"
#include <msp430.h>
#include <stdio.h>
#include "bitop.h"

#define select_rf() clear_bit(OUT(RF_CS_PORT),RF_CS)
#define unselect_rf() set_bit(OUT(RF_CS_PORT),RF_CS)
#define wait_miso() while(test_bit(IN(RF_SPIIO_PORT),RF_MISO))
#define wait_tx_sync() while(test_bit(IN(RF_TX_GDO_PORT),RF_TX_GDO))
#define wait_tx_done() while(!test_bit(IN(RF_TX_GDO_PORT),RF_TX_GDO))
#define wait_rx_sync() while(test_bit(IN(RF_RX_GDO_PORT),RF_RX_GDO))
#define wait_rx_done() while(!test_bit(IN(RF_RX_GDO_PORT),RF_RX_GDO))
#define delay(n) __delay_cycles(n)

#include "pins.h"
#include "spi.h"

struct PACKET rx_packet;

char rf_settings[0x30] = {
	0x2E,               // GDO2 output pin configuration.                     
	0x2E,               // GDO1 output pin configuration.
	0x2E,               // GDO0 output pin configuration.
	0x07,               // RXFIFO and TXFIFO thresholds.
	0xD3,               // Sync word, high byte
	0x91,               // Sync word, low byte
	0xFF,               // Packet length.                                     
	0x04,               // Packet automation control.                         
	0x45,               // Packet automation control.
	0x00,               // Device address.
	0x00,               // Channel number.
	0x0C,               // Frequency synthesizer control.
	0x00,               // Frequency synthesizer control.
	0x21,               // Frequency control word, high byte.
	0x6B,               // Frequency control word, middle byte.
	0x24,               // Frequency control word, low byte.
	0x1A,               // Modem configuration.
	0x71,               // Modem configuration.
	0x03,               // Modem configuration.
	0x21,               // Modem configuration.
	0xE5,               // Modem configuration.
	0x71,               // Modem deviation setting (when FSK modulation is enabled).
	0x07,               // Main Radio Control State Machine configuration.
	0x30,               // Main Radio Control State Machine configuration.    
	0x18,               // Main Radio Control State Machine configuration.
	0x1D,               // Frequency Offset Compensation Configuration.
	0x1C,               // Bit synchronization Configuration.
	0x47,               // AGC control.
	0x40,               // AGC control.
	0xB0,               // AGC control.
	0x00,               // High byte Event 0 timeout
	0x00,               // Low byte Event 0 timeout
	0xF8,               // Wake On Radio control
	0xB7,               // Front end RX configuration.
	0x10,               // Front end RX configuration.
	0xE9,               // Frequency synthesizer calibration.
	0x2A,               // Frequency synthesizer calibration.
	0x00,               // Frequency synthesizer calibration.
	0x1F,               // Frequency synthesizer calibration.
	0x00,               // RC oscillator configuration
	0x00,               // RC oscillator configuration  
	0x59,               // Frequency synthesizer calibration control
	0x7F,               // Production test
	0x3F,               // AGC test
	0x88,               // Various test settings.
	0x31,               // Various test settings.
	0x09                // Various test settings.
};

void rf_write_settings(void) {
	rf_spi_write_burst_reg(0x00, rf_settings, 0x30); 
}

// PATABLE (10 dBm output power)
char paTable[] = {0xC0};
char paTableLen = 1;

void rf_spi_write_reg(char addr, char value) {
	select_rf();
	wait_miso();
	rf_spi_send_receive(addr);
	rf_spi_send_receive(value);
	unselect_rf();
}

void rf_spi_write_burst_reg(char addr, char *buffer, char count) {
	unsigned int i;

	select_rf();
	wait_miso(); 
	rf_spi_send_receive((addr | CC1101_WRITE_BURST)); // Send address

	for (i = 0; i < count; i++) {
		rf_spi_send_receive(buffer[i]);                  // Send data
	}

	unselect_rf();
}

char rf_spi_read_reg(char addr) {
	char byte;

	select_rf();
	wait_miso(); 
	rf_spi_send_receive((addr | CC1101_READ_SINGLE));// Send address
	byte = rf_spi_send_receive(0);                            // Read data
	unselect_rf();

	return byte;
}

void rf_spi_read_burst_reg(char addr, char *buffer, char count) {
	select_rf();
	wait_miso(); 

	rf_spi_send_receive((addr | CC1101_READ_BURST));// Send address

	for(int i = 0; i < count; i++) {
		buffer[i] = rf_spi_send_receive(0);
	}
	unselect_rf();
}

char rf_spi_read_status(char addr) {
	char status;

	select_rf();
	wait_miso();
	rf_spi_send_receive((addr | CC1101_READ_BURST));
	status = rf_spi_send_receive(0);
	unselect_rf();

	return status;
}

void rf_spi_strobe(char strobe) {
	select_rf();
	wait_miso();
	rf_spi_send_receive(strobe);
	unselect_rf();
}

void rf_powerup_reset(void) {
	unselect_rf();
	delay(30);
	select_rf();
	delay(30);
	unselect_rf();
	delay(45);

	rf_spi_strobe(CC1101_SRES);
}

void rf_init(void) {
	rf_powerup_reset();
	rf_write_settings();                        
	rf_spi_write_burst_reg(CC1101_PATABLE, paTable, paTableLen);
	rf_set_address(0x09);
	rf_spi_strobe(CC1101_SIDLE);
}

void rf_reconfigure(unsigned char int_on) {
	if(int_on) {
		rf_settings[1] = 0x06;	
	}
	else {
		rf_settings[1] = 0x2E;	
	}
	
	rf_write_settings();
	rf_spi_strobe(CC1101_SIDLE);

	delay(100);	
}


void rf_sleep(void) {
	rf_spi_strobe(CC1101_SPWD);           
}

void rf_set_address(char address) {
	rf_spi_write_reg(0x09,address);	
}

void rf_receive(void) {
	rf_reconfigure(1);
	
	rf_spi_strobe(CC1101_SIDLE);           
	rf_spi_strobe(CC1101_SRX);           

	wait_rx_sync();
	wait_rx_done();

	if(rf_receive_packet()) {
		printf("Length %d\n", rx_packet.length);
		printf("RSSI %d\n", rx_packet.rssi);
		printf("Payload===\n");
		for(int i=0; i<rx_packet.length; i++) {
			printf("%d ", rx_packet.data[i]);	
		}
		printf("\n");
		printf("End===\n");
	}
	else {
		printf("RX failed\n");	
	}
	
	rf_reconfigure(0);
}

char buffer[] = {0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void rf_send(void) {
	rf_reconfigure(1);
	printf("SUCCESS %d\n",rf_send_packet(buffer,11));
	rf_reconfigure(0);
}

char rf_send_packet(char *buffer, char size) {
	// fill up txbuffer with packet bytes
	for(int i=0; i<size; i++) {
		rf_spi_write_reg(CC1101_TXFIFO, buffer[i]);
	}

	// make sure we are idle then go to tx mode
	rf_spi_strobe(CC1101_SIDLE);           
	wait_miso();
	rf_spi_strobe(CC1101_STX);           

	// wait for GDO1 to assert -- sync sent
	wait_tx_sync();

	// wait for GDO1 to deassert -- packet finished sending
	wait_tx_done();

	return 1;	// success
}

char rf_receive_packet(void) {
	char status[2];
	char pktLen;
	char length=32;

	if ((rf_spi_read_status(CC1101_RXBYTES) & CC1101_NUM_RXBYTES)) {
		pktLen = rf_spi_read_reg(CC1101_RXFIFO);

		if (pktLen <= length) {
			rf_spi_read_burst_reg(CC1101_RXFIFO, rx_packet.data, pktLen);
			rx_packet.length = pktLen;
			rf_spi_read_burst_reg(CC1101_RXFIFO, status, 2);

			rx_packet.rssi = status[0];
			return (char)((status[CC1101_LQI_RX]&CC1101_CRC_OK)!=0);
		} 
		else {
			rx_packet.length = pktLen;
			rf_spi_strobe(CC1101_SFRX);
			return 0;
		}
	}
	else {
		return 0;
	}
}
