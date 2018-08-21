#include "dma.h"
#include <msp430.h>

void dma_print(const char *message, int length) {
 
  DMACTL0 = DMA0TSEL_15;
  DMA0SA = (unsigned long) &message[0];
  DMA0DA = (unsigned long) &UCA0TXBUF;
  DMA0SZ = length;
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMAEN + DMAIE + DMALEVEL + DMASRCBYTE + DMADSTBYTE;
  
  __bis_SR_register(LPM0_bits + GIE);  
  
}


void dma_print_no_sleep(const char *message, int length) {
 
  DMACTL0 = DMA0TSEL_15;
  DMA0SA = (unsigned long) &message[0];
  DMA0DA = (unsigned long) &UCA0TXBUF;
  DMA0SZ = length;
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMAEN + DMAIE + DMALEVEL + DMASRCBYTE + DMADSTBYTE;
  
}
