#include "usci_uart.h"

extern UCA0<uart_buffer_t> uart; 
void printf(char* buffer) {
	uart.xmit(buffer);	
}
