#include <msp430.h>
#include "clock.h"
#include "bitop.h"
#include "portmacros.h"

void init_clocks() {
	// XT1, XT2 Setup
	CSCTL0_H = CSKEY >> 8; //Unlock CS registers
	CSCTL2 = SELA__LFXTCLK | SELS__HFXTCLK | SELM__HFXTCLK; //ACLK=LF, MCLK=SMCLK=HF
	CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1; //Set all dividers to 1
	CSCTL4 = LFXTDRIVE_0 | HFXTDRIVE_0 | HFFREQ_3; //LF=high current(TODO why?), HF=high current(TODO why?), HF over 16MHz
	//CSCTL4 &= ~(LFXTOFF | HFXTOFF); //Make sure xtals are on, why was this here? TODO
	set_bits(CSCTL4,LFXTOFF|HFXTOFF|VLOOFF); //Make sure xtals turn off when not needed(like in LPM)
	do {
		CSCTL5 &= ~(LFXTOFFG | HFXTOFFG); //Clear XT1 fault flag
		SFRIFG1 &= ~OFIFG;
	} while (SFRIFG1&OFIFG); //Test oscillator fault flag
	CSCTL0_H = 0; //Lock CS registers
}

void init_24MHz() {
	// Startup clock system with max DCO setting ~8MHz
	CSCTL0_H = CSKEY >> 8;                    // Unlock clock registers
	CSCTL1 = DCOFSEL_6 | DCORSEL;             // Set DCO to 24MHz
	CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;
	CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // set all dividers
	CSCTL4 = LFXTDRIVE_0;
	CSCTL0_H = 0;                             // Lock CS registers
}
