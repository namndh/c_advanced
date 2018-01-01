#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <libfdr/jval.h>
#include <libfdr/dllist.h>


typedef Dllist Queue;


Queue createQueue();

void freeQueue(Queue queue);

void enQueue(Queue queue, Jval jval);

Jval deQueue(Queue queue);

void enQueueP(Queue queue, Jval value, int (*compareNode)(Jval, Jval));

void actionQueue(Queue queue, void (*actionValue)(Jval));


#endif
      
  
  
