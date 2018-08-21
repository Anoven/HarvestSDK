#ifndef CLOCK_H
#define CLOCK_H


#define seconds *F_CPU
#define ms *(F_CPU/1000)
#define us *(F_CPU/1000000)
#define delay __delay_cycles

void init_clocks();
void init_24MHz();
#endif
