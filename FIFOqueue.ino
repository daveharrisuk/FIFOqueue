/*file: FIFOqueue.ino
 *---------------------------------------------------------------------
 *
 * test FIFOqueue class
 * 
 * Author: Dave Harris. Andover, UK.    © Dave Harris, Jan 2021
*/

#include "FIFOqueue.h"

// create global que object

FIFOqueue que( 8 ); /* new que of length 8 (actual size = length -1) */


void printStatus()
{
  Serial.print("\t errorCount=");
  Serial.print( que.errorCount );
  Serial.print(", available=");
  Serial.print( que.available() );
  Serial.print(", emptySlots="); 
  Serial.println( que.emptySlots() );
}


void setup() 
{
  Serial.begin(115200);
  Serial.print("\n-----test FIFOqueue que(8), length=");
  Serial.println( que.length() );

  printStatus();

  for( uint8_t i = 100; i < que.length() + 100; i++ )
  {
    que.put( i );
    Serial.print("put>"); Serial.println( i ); // put 100 to 106
    printStatus();
  }
  // queue is now full...
  
  Serial.println("put>123 fails as 0 emptySlots");
  que.put( 123 );
  printStatus();
    
  Serial.print("get="); Serial.println( que.get() );
  printStatus();
  Serial.print("get="); Serial.println( que.get() );
  printStatus();
  Serial.print("get="); Serial.println( que.get() );
  printStatus();
  Serial.print("get="); Serial.println( que.get() );
  printStatus();
  
  Serial.println("put>200");
  que.put( 200 );
  
  printStatus();
 
  Serial.print("get="); Serial.println( que.get() );
  
  printStatus();
   
  Serial.println("put>201");
  que.put( 201 );
  
  printStatus();

  while( que.available() > 0 ) // get the rest of entries
  {
    Serial.print("get="); Serial.println( que.get() );
    printStatus();
  }
          
  Serial.print("get fails as 0 available ="); 
  Serial.println( que.get() );
  
  printStatus();
}

void loop() 
{
  
}

/* -------------------------------EoF------------------------------ */

