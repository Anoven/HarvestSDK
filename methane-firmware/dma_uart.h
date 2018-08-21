#ifndef DMA_UART_H 
#define DMA_UART_H

#include <string.h>

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
	DMACTL0 = DMA0TSEL_15;
  }
  
  inline bool empty() {
	return _recv_buffer.empty();
  }
  
  inline int recv() {
	while(empty());
	return _recv_buffer.pop_front();
  }
  
  void xmit(unsigned char c) {
	DMA0SA = (unsigned long) &c;
	DMA0DA = (unsigned long) &UCA0TXBUF;
	DMA0SZ = 1;
	DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMALEVEL + DMASRCBYTE + DMADSTBYTE + DMAEN + DMAIE;
	__bis_SR_register(LPM0_bits + GIE);  
  }
  
  void xmit(const char *s) {
	DMA0SA = (unsigned long) &s[0];
	DMA0DA = (unsigned long) &UCA0TXBUF;
	DMA0SZ = sizeof(*s);
	DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMALEVEL + DMASRCBYTE + DMADSTBYTE + DMAEN + DMAIE;
	__bis_SR_register(LPM0_bits + GIE);  
  }
};

volatile unsigned char command_len = 0;
char command[100];
volatile unsigned char command_present = 0;

void __attribute__((interrupt (USCI_A0_VECTOR))) USCI0RX_ISR() {
  char c = UCA0RXBUF;
  uart_buffer.push_back(c);
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=DMA_VECTOR
__interrupt void DMA0_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(DMA_VECTOR))) DMA0_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(DMAIV)
  {
	case  0: break;                          // No interrupt
	case  2:
	  DMACTL0 = 0; 
	  __bic_SR_register_on_exit(LPM0_bits); 
	  break;                                 // DMA0IFG
	case  4: break;                          // DMA1IFG
	case  6: break;                          // DMA2IFG
	case  8: break;                          // Reserved
	case 10: break;                          // Reserved
	case 12: break;                          // Reserved
	case 14: break;                          // Reserved
	case 16: break;                          // Reserved
	default: break;
  }
}
#endif /* HW_SERIAL_H */
