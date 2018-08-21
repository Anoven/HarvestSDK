#include <msp430.h>
#include "fram.h"

void fram_write(uint16_t address, uint8_t value) {
	int16_t *fram_ptr = (int16_t *)address;
	*fram_ptr = value;
}

uint16_t fram_read(uint16_t address) {
	uint16_t *fram_ptr;
	fram_ptr = (uint16_t *)address;
	return *fram_ptr;
}
