#ifndef HW_SERIAL_H
#define HW_SERIAL_H

template<typename T_STORAGE>
struct UCA0 {
	T_STORAGE &_recv_buffer;

	inline void init(const unsigned long baud) {
		const unsigned long baud_rate_20_bits = (F_CPU + (baud >> 1))/baud; // Bit rate divisor

		UCA0CTL1 |= UCSSEL_2; // use SMCLK for USCI clock
		UCA0BR0 = (baud_rate_20_bits >> 4) & 0xFF;      // Low byte of whole divisor
		UCA0BR1 = (baud_rate_20_bits >> 12) & 0xFF;     // High byte of whole divisor
		UCA0MCTLW = ((baud_rate_20_bits << 4) & 0xF0) | UCOS16;
		UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
		UCA0IE |= UCRXIE; // Enable USCI_A0 RX interrupt
	}

	inline bool empty() {
		return _recv_buffer.empty();
	}

	inline int recv() {
		while(empty());
		return _recv_buffer.pop_front();
	}

	void xmit(unsigned char c) {
		while (!(UCA0IFG & UCTXIFG))
			; // USCI_A0 TX buffer ready?

		UCA0TXBUF = (unsigned char) c; // TX -> RXed character
	}

	void xmit(const char *s) {
		while (*s) {
			xmit(*s);
			++s;
		}
	}
};

volatile unsigned char command_len = 0;
char command[100];
volatile unsigned char command_present = 0;

void __attribute__((interrupt (USCI_A0_VECTOR))) USCI0RX_ISR() {
	char c = UCA0RXBUF;
	switch(c) {
		case '\n':
			command[command_len] = '\0';
			command_len = 0;
			command_present = 1;
			break;
		case '\x7f':
		case '\b':
			if(command_len>0) {
				command_len--;	
			}
			break;
		default:
			command[command_len++] = c;
			break;
	}
	//uart_buffer.push_back(c);

}
#endif /* HW_SERIAL_H */
