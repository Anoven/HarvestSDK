#include <msp430.h>
#include "rtc.h"
#include <stdio.h>
#include "device_info.h"
#include <msp430fr5969.h>



void rtc_init(char *datetime) {
    RTCCTL01_H = 0xA5;                   

    RTCCTL01_L = RTCTEVIE + RTCAIE; //alarm interrupt enable                    
    RTCCTL01 = 0x60;//RTCHOLD; //| RTCMODE;
          
    
    while(!RTCCTL01_L&RTCRDYIFG);
    
    RTCYEAR = datetime[0]+2000;                       
    RTCMON = datetime[1];                           
    RTCDAY = datetime[2];                          
    RTCDOW = datetime[3];                          
    RTCHOUR = datetime[4];                         
    RTCMIN = datetime[5];                          
    RTCSEC = datetime[6];                          

    RTCAMIN = 0x82; //
    RTCAHOUR = 0;
    RTCADOW =0;
    RTCADAY =0;
    // Start RTC calendar mode
    //RTCCTL01 &= ~RTCHOLD;
    RTCCTL01 = 0x20;
    
}

void rtc_print_time(void) {
	while(!RTCCTL01_L&RTCRDYIFG);
	printf("%04d-%02d-%02d %02d:%02d:%02d\n",RTCYEAR,RTCMON,RTCDAY,RTCHOUR,RTCMIN,RTCSEC);		
}

void rtc_set_alarm(unsigned char interval){
    RTCAMIN = 0x80|((RTCMIN+1)%59); //
    RTCAHOUR = 0;
    RTCADOW =0;
    RTCADAY =0;  
}


