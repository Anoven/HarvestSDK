
#include "cc1200.h"
#include <msp430.h>
#include <stdlib.h>
#include "rtc.h"

#define RF_RX_INT_PIN 0x0C
#define RF_CRC_INT_PIN 0x0A
#define ACC_DATA_INT_PIN 10

extern volatile unsigned char packet_available;
extern volatile unsigned char crc_ok;
extern volatile unsigned char rtc_alarm;



// Port 3 interrupt service routine
void __attribute__((interrupt (PORT3_VECTOR))) Port_3(void) 
{
// 	switch(P3IV) {
// 		case RF_RX_INT_PIN: 
// 			clear_bit(IFG(RF_GPIO0_PORT),RF_GPIO0);
// 			packet_available = 1;
// 			break; // P1.5
// 	}
}



// Timer0_A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer0_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
	// wake up after timer interval to restart requesting data from
	// sensors
	TA0IV = 0;
	__bic_SR_register_on_exit(LPM0_bits); 
}


volatile uint16_t rtc_events = 0;
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(RTC_VECTOR))) RTC_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch (RTCIV)
	{
		case RTCIV_NONE:      break;
		case RTCIV_RTCRDYIFG: break;
		case RTCIV_RTCTEVIFG: 
                    printf("rtc events");                
                    rtc_events++;
                    break;
		case RTCIV_RTCAIFG:   
                    rtc_set_alarm(0);
                    rtc_alarm =1;
                    printf("alarm \n");
                    break;
		case RTCIV_RT0PSIFG:  break;
		case RTCIV_RT1PSIFG:  break;
		case RTCIV_RTCOFIFG:  break;
	}
}


