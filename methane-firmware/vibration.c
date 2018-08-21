#include <string.h>
#include <stdlib.h>
#include "vibration.h"
#include "acc.h"
#include "cc1200.h"
#include "cc1200_spi.h"
#include "device_info.h"
#include "clock.h"
#include "printf.h"

uint8_t rx_buffer[130];
//extern struct acc_data_struct acc_data;
extern uint8_t packet_available;
uint8_t pkt_seq = 0;

uint8_t sensor_send_data_packet(struct DELTA_PACKET *data,uint8_t count) {
	uint8_t tx_success;
	uint8_t byte_count = count*3;
	
	struct ACC_DATA_PACKET packet;//*packet = malloc(sizeof(struct ACC_DATA_PACKET));
	packet.header.len = 9+byte_count;
	packet.header.dst = RECEIVER_ID;
	packet.header.src = device_get_id()+device_get_group();
	packet.header.type = DATA;
	packet.count = count;
	packet.x0 = data->x0;
	packet.y0 = data->y0;
	packet.z0 = data->z0;
	
	

	for(uint8_t i=0; i<byte_count; i++) {
		packet.data[i] = data->data[i];	
	}
	
	//uint8_t buf[sizeof(packet)];
	//memcpy(buf,&packet,sizeof(packet));
		
	tx_success = cc1200_send_packet((unsigned char *) &packet);
	return tx_success;
}

int8_t sensor_receive_packet(void) {
	struct CC1200_PACKET *packet;

	// wait for radio to leave tx state
	while(cc1200_spi_read_extended_reg(CC120X_MARCSTATE)==51);
	
	cc1200_wait_for_rx(2 ms);

	if(cc1200_receive_packet()) {
		packet = (struct CC1200_PACKET *) rx_buffer;
		//printf("[%d] %d %d \n",packet->src,packet->dst,packet->type);
		return packet->type;	
	}
	else {
		cc1200_enter_idle();
		return -1;	
	}
}
