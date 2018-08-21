#ifndef FRAM_H
#define FRAM_H

#include <stdint.h>

void fram_write(uint16_t address, uint8_t value);
uint16_t fram_read(uint16_t address); 

#endif
