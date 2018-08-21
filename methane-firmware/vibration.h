#ifndef VIBRATION_H
#define VIBRATION_H

#include <stdint.h>
//#include "acc.h"
//#include "calibration.h"
#define SAMPLES_PER_DOWNLOAD 10000
#define PACKETS_PER_DOWNLOAD 500
#define SAMPLES_PER_PACKET 20

#define MAX_ATTEMPTS 200

#define RECEIVER_ID 10

// packet types to determine what to do when receiving a message
#define DATA 0x01
#define START 0x02
#define REQUEST 0x03
#define ACK 0x04
#define DOWNLOAD 0x05
#define CALIBRATE 0x06
#define START_SENDING 0x07
#define STOP_SENDING 0x0A
#define OP 0x0B
#define CHANGE_FREQUENCY 0x0C
#define NACK 0x0D
#define DOWNLOAD_ACK 0x0E
#define SET_CALIBRATION 0x0F
#define GET_CALIBRATION 0x10
#define RESET_OP 0X11


struct DELTA_PACKET {
	uint16_t x0;
	uint16_t y0;
	uint16_t z0;
	int8_t data[39*3];
};

struct HEADER {
	uint8_t len;
	uint8_t dst;
	uint8_t src;
	uint8_t type;
};

struct COMMAND_PACKET {
	uint8_t len;
	uint8_t dst;
	uint8_t src;
	uint8_t type;
};

struct ACC_DATA_PACKET {
	struct HEADER header;
	uint8_t count;
	uint16_t x0;
	uint16_t y0;
	uint16_t z0;
	uint8_t data[117];
};

struct ACC_DOWNLOAD_PACKET {
	struct HEADER header;
	uint16_t seq;
	uint8_t data[120];
};
/*
struct CALIBRATION_VALUES { //defined in calibration.h
	uint16_t x_slope_h;
	uint16_t x_slope_l;
	uint16_t x_offset_h;
	uint16_t x_offset_l;
	uint16_t y_slope_h;
	uint16_t y_slope_l;
	uint16_t y_offset_h;
	uint16_t y_offset_l;
	uint16_t z_slope_h;
	uint16_t z_slope_l;
	uint16_t z_offset_h;
	uint16_t z_offset_l;
};
*/
/*
struct CALIBRATION_PACKET {
	struct HEADER header;
	struct CALIBRATION_VALUES calibration;
};
*/
struct OP_TIME_PACKET {
	struct HEADER header;
	uint16_t op_time;
};

struct CHANGE_FREQUENCY_PACKET{
	struct HEADER header;
	unsigned char freq_1;
	unsigned char freq_2;
};

void sensor_read_all(void);
uint8_t sensor_send_data_packet(struct DELTA_PACKET *data, uint8_t count);
void sensor_wait_for_start(void);
int8_t sensor_receive_packet(void);

#endif
