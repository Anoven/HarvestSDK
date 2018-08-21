#include "acc.h"
#include "vibration.h"

void delta_encode(unsigned char * buffer, struct DELTA_PACKET *packet, int length) {	
	struct acc_data_struct *acc_struct_buffer = (struct acc_data_struct *) buffer;
	
	struct acc_data_struct last = acc_struct_buffer[0];
	
	// save the first value to recreate the rest
	packet->x0 = last.x;
	packet->y0 = last.y;
	packet->z0 = last.z;
	
	//printf("x0=%d y0=%d z0=%d\n",packet.x0,packet.y0,packet.z0);
	
	int j=0;
	
	for(int i=1; i<length; i++) {
		struct acc_data_struct current = acc_struct_buffer[i];
		
		// record the difference between the current and last
		// as a signed char
		packet->data[j++] = current.x-last.x;
		packet->data[j++] = current.y-last.y;
		packet->data[j++] = current.z-last.z;
		
		//printf("x=%d y=%d z=%d\n",packet.data[j-3],packet.data[j-2],packet.data[j-1]);
		
		last = current;
	}
}
