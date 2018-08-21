/****************************************************************************** 
 * MARACA: Industrial Vibration Sensor 
 * Harvest Robotics
 * Last Modified: 2015/10/01
 * 
 * main.cpp 
 * 
 ******************************************************************************/

#include <msp430.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"
#include "clock.h"
#include "pins.h"
#include "spi.h"
#include "ds1820.h"
#include "cc1200.h"
#include "cc1200_spi.h"
#include "device_info.h"
#include "vibration.h"
#include "interrupt.h"
#include "timer.h"
#include "term.h"
#include "led.h"
#include "fram.h"
#include "rtc.h"    
#ifdef __cplusplus
}
#endif

struct methane_data_struct{
    uint16_t methane;
    uint16_t temp;
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
};
#define CircularBuffer_element methane_data_struct
#include "CircularBuffer.h"
#define METHANE_BUFFER_SIZE 2000
CircularBuffer_t methane_buffer;
__attribute__((section(".fram_vars"))) static struct methane_data_struct methane_buffer_storage[METHANE_BUFFER_SIZE];

#include "ringbuffer.h"
typedef  ringbuffer<char, 64> uart_buffer_t;

uart_buffer_t uart_buffer = { 0, 0, { 0 } };

#include "usci_uart.h"
UCA0<uart_buffer_t> uart = { uart_buffer };

int putchar(int c) {
	uart.xmit((char)c);
	return 1;
}

struct methane_data_struct methane_data;

volatile unsigned char rtc_alarm=0;

void chip_init(void) {
	WDTCTL = WDTPW + WDTHOLD; //Stop WDT

	pins_init();
	
        //Enable pins after powerup according to 8.3.1(page 310) from SLAU367B
	clear_bits(PM5CTL0,LOCKLPM5);
        
	// Configure one FRAM waitstate as required by the device datasheet for MCLK
	// operation beyond 8MHz _before_ configuring the clock system.
	FRCTL0 = FWPW | NACCESS_1;

	//Enable clock
	//init_clocks();
	init_24MHz();

	//Debug UART
	uart.init(115200);


	//Enable interrupts
	__bis_SR_register(GIE);
      	printf("MARACA Industrial Basestation\n");
        LED_ON();
	
        char datetime_rf[7]= {16,1,1,1,16,1,1};
        rtc_init(datetime_rf);
        
        cc1200_init();
	cc1200_debug();
        //device_set_id(0x00);
	//device_set_type(0x01);
	//device_set_group(10);
	
	
	//printf("* Revision 1.0a\n");
	//printf("* DEVICE GROUP=0x%02X\n",device_get_group());
	printf("* DEVICE ID=0x%02X\n",device_get_id());
	printf("* DEVICE TYPE=0x%02X\n",device_get_type());
	rtc_print_time();
        rtc_set_alarm(0);
        
        methane_buffer.Size = METHANE_BUFFER_SIZE;
        methane_buffer.Buf = methane_buffer_storage;
        
        
        
        //printf(MARKER);
}
//void sweep_rf(void);
extern uint8_t rx_buffer[];
//extern struct ACC_DATA_PACKET *packet;

int main(void) {

    chip_init();    
    uint16_t temp_raw;
    uint16_t methane=0;
    int i=0;
    
    while(1){
        
        if(rtc_alarm){
        
            if(DS1820_FindFirstDevice()){
                
                do{
                    temp_raw = DS1820_GetTempRaw();
                    printf(" raw temp is %u, %u \n", temp_raw,i++);
                }
                while(DS1820_FindNextDevice());   
                }
            methane_data.methane =0;
            methane_data.temp= temp_raw;
            methane_data.year = RTCYEAR-2000;
            methane_data.month = RTCMON;
            methane_data.day = RTCDAY;
            methane_data.hour = RTCHOUR;
            methane_data.min = RTCMIN;
            CircularBufferWrite(&methane_buffer,methane_data);
            device_set_write_pointer(methane_buffer.Write);
            rtc_alarm =0;
            
            if(methane_buffer.Count>3){
                
                
            }
            //delay(2000 ms);
            //rtc_print_time();

        }
	
    }
return 0;
    
}


