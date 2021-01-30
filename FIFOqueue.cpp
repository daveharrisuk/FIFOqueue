/*file: FIFOqueue.cpp
 *---------------------------------------------------------------------
 *
 * fast and compact FIFO buffer queue class
 * 
 * class definitions
 * 
 * Author: Dave Harris. Andover, UK.    © Dave Harris 2021
*/

#include "FIFOqueue.h"


FIFOqueue::FIFOqueue( uint8_t len )  /* Constructor method          */
{
  buflen = len;                      /* buflen = 8, 16, 32, 64, 128 */
  
  val = 0;
  for( uint8_t i = 0; i < 8; i++ )      /* count the bits in buflen */
  {
    val += ( len >> i ) & 0b00000001;   /* shift & expose just LSB  */
  }
  if( ( val != 1 ) || ( buflen < 8 ) )  /* is not a valid length    */
  {
    buflen = 8;                         /* default buffer length    */
    errorCount++;                       /* fail silently            */
  }
  
  MASK = buflen - 1;          /* buflen = 8, 01000, so mask = 00111 */
  
  buffer = new uint8_t[ buflen ];     /* make a new array           */
};


uint8_t FIFOqueue::length()
{
  return MASK;         /* mask = buflen -1 (is an always empty byte)*/
};


void FIFOqueue::put( uint8_t v ) 
{
  noInterrupts();
  nexthead = ( head + 1 ) & MASK;   /* increment & overflow to 0    */
  
  if( nexthead == tail )    /* queue is full!                       */
  {                         /* Caller should check emptySlots() > 0 */
    interrupts();
    errorCount++;           /* silently fail.                       */
    return;
  }

  buffer[head] = v;         /* add the value                        */
  
  head = nexthead;          /* update the head index                */
  interrupts();
};


uint8_t FIFOqueue::get()
{
  noInterrupts();
  if( head == tail )        /* queue is empty!                      */
  {                         /* Caller should check available() > 0  */
    interrupts();
    errorCount++;           /* silently fail.                       */
    return 255;
  }
  val = buffer[tail];
  
  tail = ( tail + 1 ) & MASK;  /* increment and overflow to 0       */
  
  interrupts();
  return val;      
};


uint8_t FIFOqueue::available()
{
  noInterrupts();
  
  if( head >= tail )
  {
      val = head - tail; 
  }
  else
  {
      val = MASK + 1 - tail + head;
  }
  interrupts();
  return val;
};


uint8_t FIFOqueue::emptySlots()
{
  return MASK - available();   /* mask = buflen -1                 */
}


/* ---------------------- EoF FIFOqueue.cpp ---------------------- */
