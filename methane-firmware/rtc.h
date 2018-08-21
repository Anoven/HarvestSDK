#ifndef RTC_H
#define RTC_H

#include <msp430.h>

void rtc_init(char *);
void rtc_print_time(void);
void rtc_set_alarm(unsigned char interval);
#endif // RTC_H
