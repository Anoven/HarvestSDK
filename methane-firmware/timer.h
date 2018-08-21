#ifndef TIMER_H
#define TIMER_H

#include <msp430.h>

void timer_init(unsigned int interval) {
	TA0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
	TA0CCR0 = interval;
	TA0CTL = TASSEL__ACLK | MC__UP;          // SMCLK, UP mode
}

#endif
