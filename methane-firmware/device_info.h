#ifndef DEVICE_INFO_H
#define DEVICE_INFO_H

#include <stdint.h>

#define DEVICE_TYPE_RECEIVER 0x01
#define DEVICE_TYPE_SENSOR 0x02

#define DEVICE_ID_ADDR 0x1800
#define DEVICE_TYPE_ADDR 0x1802
#define DEVICE_GROUP_ADDR 0x1804

#define BUFFER_READ 0x1806
#define BUFFER_WRITE 0x1808

void device_set_id(uint16_t id);
uint16_t device_get_id(void);
void device_set_type(uint16_t type);
uint16_t device_get_type(void);
void device_set_group(uint16_t group);
uint16_t device_get_group(void);

void device_set_read_pointer(uint16_t read);
uint16_t device_get_read_pointer(void);

void device_set_write_pointer(uint16_t write);
uint16_t device_get_write_pointer(void);
#endif
