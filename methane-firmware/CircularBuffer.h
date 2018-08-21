/*
 * Circular Buffer Implementation
 */

/*
 * A circular buffer data structure. A read/write counter is used to track the
 * capacity of the buffer remaining.
 */

/* Ring Buffer Data Structure *************************************************/
#include <msp430.h>

typedef struct CircularBuffer_t {
    unsigned int Read;
    unsigned int Write;
    unsigned int Count;
    unsigned int Size;
    CircularBuffer_element *Buf;
} CircularBuffer_t;

/* Functions ******************************************************************/

/*
 * Determines whether the buffer is empty
 */
unsigned int CircularBufferIsEmpty(volatile CircularBuffer_t *buf)
{
	unsigned int empty;
	
  //__bic_SR_register(GIE);
	empty = (buf->Count == 0);
 //__bis_SR_register(GIE);

	return empty;
}

/*
 * Determines whether the buffer is full
 */
unsigned int CircularBufferIsFull(volatile CircularBuffer_t *buf)
{
	unsigned int full;

	//_disable_interrupts(); // prevent inconsistent reads
	full = (buf->Count == buf->Size-1);
	//_enable_interrupts();
    if (full)
    {
        buf->Read=buf->Write+1;
    }
	return full;
}

/*
 * Inserts an element into the buffer, overwriting the oldest element if the
 * buffer is full.
 */
void CircularBufferWrite(volatile CircularBuffer_t *buf, CircularBuffer_element elem)
{
	if(!CircularBufferIsFull(buf))
    {
        buf->Count++;
    }
	
    buf->Buf[buf->Write] = elem;
	buf->Write = (buf->Write == (buf->Size - 1)) ? 0 : buf->Write + 1; //update buf pointer 
   
}

/*
 * Reads an element from the buffer.
 */
CircularBuffer_element CircularBufferRead(volatile CircularBuffer_t *buf)
{
    CircularBuffer_element b;
        if(!CircularBufferIsEmpty(buf))
    {
        buf->Count--;
        b = buf->Buf[buf->Read];
        buf->Read = (buf->Read == (buf->Size - 1)) ? 0 : buf->Read + 1;
    }

    return b;
}
