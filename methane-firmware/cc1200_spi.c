/*
 * 
 * 
 */

#include <msp430.h>
#include <stdio.h>
#include "cc1200_spi.h"
#include "cc1200.h"
#include "pins.h"
#include "bitop.h"
#include "spi.h"

void cc1200_spi_write_reg(unsigned char addr, unsigned char value) {
	cc1200_select();
	cc1200_wait_miso();
	
	rf_spi_send_receive(addr | CC1200_SPI_WRITE);
	rf_spi_send_receive(value);
	
	cc1200_wait_miso();
	cc1200_unselect();
}

void cc1200_spi_write_extended_reg(unsigned int addr, unsigned char value) {
	cc1200_select();
	cc1200_wait_miso();
	
	rf_spi_send_receive(0x2F | CC1200_SPI_WRITE);
	rf_spi_send_receive(addr);
	rf_spi_send_receive(value);
	
	cc1200_wait_miso();
	cc1200_unselect();
}

void cc1200_spi_write_burst_reg(unsigned char addr, unsigned char *buffer, unsigned char count) {
	cc1200_select();
	cc1200_wait_miso();
	
	rf_spi_send_receive(addr | CC1200_SPI_WRITE_BURST);
	
	for(int i=0; i<count; i++) {
		rf_spi_send_receive(buffer[i]);	
	}
	
	cc1200_wait_miso();
	cc1200_unselect();
}

unsigned char cc1200_spi_read_reg(unsigned char addr) {
	char result;
	
	cc1200_select();
	cc1200_wait_miso();
	
	rf_spi_send_receive(addr|CC1200_SPI_READ);
	result = rf_spi_send_receive(0x00);
	
	cc1200_wait_miso();
	cc1200_unselect();
	
	return result;
}

unsigned char cc1200_spi_read_extended_reg(unsigned int addr) {
	char result;
	
	cc1200_select();
	cc1200_wait_miso();
	
	rf_spi_send_receive(0x2F|CC1200_SPI_READ);
	rf_spi_send_receive(addr);
	result = rf_spi_send_receive(0x00);
	
	cc1200_wait_miso();
	cc1200_unselect();
	
	return result;
}

void cc1200_spi_read_burst_reg(unsigned char addr, unsigned char *buffer, unsigned char count) {
	cc1200_select();
	cc1200_wait_miso();
	
	rf_spi_send_receive((addr | CC1200_SPI_READ_BURST));
	
	for(int i=0; i<count; count++) {
		buffer[i] = rf_spi_send_receive(0x00);	
	}
	
	cc1200_wait_miso();
	cc1200_unselect();
}

unsigned char cc1200_spi_read_status(unsigned char addr) {
	unsigned char status;
	
	cc1200_select();
	cc1200_wait_miso();
	
	rf_spi_send_receive(addr | CC1200_SPI_READ_BURST);
	status = rf_spi_send_receive(0x00);
	
	cc1200_wait_miso();
	cc1200_unselect();
	
	return status;
}

unsigned char cc1200_spi_strobe(unsigned char strobe) {
	unsigned char result;
	cc1200_select();
	cc1200_wait_miso();
	
	result = rf_spi_send_receive(strobe);
	
	cc1200_wait_miso();
	cc1200_unselect();

	return result;
}
