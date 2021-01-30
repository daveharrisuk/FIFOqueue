# FIFOqueue
Arduino FIFO ring buffer queue

//usage...
FIFOqueue que(16);

  gue.put(123);
  while( que.available() > 0 )
  { 
    doSomething( que.get() );
  }  

 // if que length not 8, 16, 32, 64, 128, it silently creates length 8 
