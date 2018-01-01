#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <libfdr/jval.h>
#include <libfdr/dllist.h>


typedef Dllist Queue;



Queue createQueue();


void freeQueue(Queue queue);


void enQueue(Queue queue, int value);


int deQueue(Queue queue);

#endif
      
  
  
