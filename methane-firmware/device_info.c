/*
 * device_info.c 
 * 
 * DEVICE_GROUP : identifier for set of devices in set [10,20,30,...]  
 * DEVICE_ID    : device id within device group in range [1,8]
 * DEVICE_TYPE  : identifies whether this device is the basestation or
 *                a sensor node
 */

#include <msp430.h>
#include "device_info.h"

void device_set_id(uint16_t id) {
	int16_t *fram_ptr = (int16_t *)DEVICE_ID_ADDR;
	*fram_ptr = id;
}

uint16_t device_get_id(void) {
	uint16_t *fram_ptr;
	fram_ptr = (uint16_t *)DEVICE_ID_ADDR;
	return *fram_ptr;
}

void device_set_type(uint16_t type) {
	int16_t *fram_ptr = (int16_t *)DEVICE_TYPE_ADDR;	
	*fram_ptr = type;
}

uint16_t device_get_type(void) {
	uint16_t *fram_ptr;
	fram_ptr = (uint16_t *)DEVICE_TYPE_ADDR;
	return *fram_ptr;
}

void device_set_group(uint16_t group) {
	int16_t *fram_ptr = (int16_t *)DEVICE_GROUP_ADDR;	
	*fram_ptr = group;
}

uint16_t device_get_group(void) {
	uint16_t *fram_ptr;
	fram_ptr = (uint16_t *)DEVICE_GROUP_ADDR;
	return *fram_ptr;
}

void device_set_read_pointer(uint16_t read){
    	int16_t *fram_ptr = (int16_t *)BUFFER_READ;
	*fram_ptr = read;
}

uint16_t device_get_read_pointer(void){
    	uint16_t *fram_ptr;
	fram_ptr = (uint16_t *)BUFFER_READ;
	return *fram_ptr;
}

void device_set_write_pointer(uint16_t write){
    	int16_t *fram_ptr = (int16_t *)BUFFER_WRITE;
	*fram_ptr = write;
}

uint16_t device_get_write_pointer(void){
    	uint16_t *fram_ptr;
	fram_ptr = (uint16_t *)BUFFER_WRITE;
	return *fram_ptr;
}
