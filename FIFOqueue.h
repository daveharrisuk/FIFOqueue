/*file: FIFOqueue.h
 *------------------------------------------------------------------ 
 *
 * Arduino byte wide FIFO ring buffer queue class
 * 
 * class declaration
 * 
 * //usage...
 * FIFOqueue que(16);
 * gue.put(123);
 * while( que.available() > 0 )
 * { 
 *   doSomething( que.get() );
 * }  
 * 
 * # if length not 8, 16, 32, 64, 128, it silently creates length 8 
 * 
 * 
 * Author: Dave Harris. Andover, UK.    © Dave Harris 2021
*/
#ifndef FIFOqueue_h_  /* include guard */
#define FIFOqueue_h_


#include <Arduino.h>


class FIFOqueue
{
  private:
  
    uint8_t MASK;             /* buflen = 8, 00001000, so mask = 00000111   */

    uint8_t buflen;           /* buffer length = 8, 16, 32, 64 or 128.      */
  
    uint8_t * buffer;         /* null pointer. Constructor makes new array  */
  
    uint8_t head = 0;         /* queue head index                           */
    
    uint8_t tail = 0;         /* queue tail index                           */

    uint8_t nexthead = 0;     /* temp value for put()                       */

    uint8_t val = 0;          /* temp value for get()                       */

  public:

    uint16_t errorCount = 0;      /*  error count                           */
    
              
    FIFOqueue( uint8_t len = 8 ); /* Constructor. Make buffer[buflen]       */  
                               
    uint8_t get();                /* return oldest entry from queue         */
   
    void    put( uint8_t v );     /* put an entry in queue                  */

    uint8_t available();          /* return number of entries in queue      */

    uint8_t emptySlots();         /* return number of empty queue slots     */
    
    uint8_t length();             /* return maximum length of queue         */

};


#endif /* FIFOqueue_h_  */
/* -------------------------------EoF------------------------------ */
