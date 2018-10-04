#ifndef CC1200_SPI_H
#define CC1200_SPI_H

#define CC1200_SPI_READ 0x80
#define CC1200_SPI_WRITE 0x00
#define CC1200_SPI_WRITE_BURST 0x40
#define CC1200_SPI_READ_BURST 0xC0

void cc1200_spi_write_reg(unsigned char addr, unsigned char value); 
void cc1200_spi_write_extended_reg(unsigned char addr, unsigned char value);
void cc1200_spi_write_burst_reg(unsigned char addr, unsigned char *buffer, unsigned char count); 
unsigned char cc1200_spi_read_reg(unsigned char addr); 
unsigned char cc1200_spi_read_extended_reg(unsigned char addr);
void cc1200_spi_read_burst_reg(unsigned char addr, unsigned char *buffer, unsigned char count);
unsigned char cc1200_spi_read_status(unsigned char addr);
unsigned char cc1200_spi_strobe(unsigned char strobe);

#endif
