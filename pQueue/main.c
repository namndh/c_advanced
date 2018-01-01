//#include <libfdr/dllist.h>
#include <libllist/queue.h>
#include <stdio.h>
#include <stdlib.h>



int intCompareNode (Jval jval1, Jval jval2)
{
  return jval_i(jval1) - jval_i(jval2);
}

void printInt(Jval jval)
{
  printf("%d\n", jval_i(jval));
}



int main()
{
  Queue queue = createQueue();
  enQueueP(queue, new_jval_i(4), &intCompareNode);
  enQueueP(queue, new_jval_i(8), &intCompareNode);
  enQueueP(queue, new_jval_i(5), &intCompareNode);
  enQueueP(queue, new_jval_i(9), &intCompareNode);
  enQueueP(queue, new_jval_i(11), &intCompareNode);
  enQueueP(queue, new_jval_i(10), &intCompareNode);


  actionQueue(queue, &printInt);


  printf("dequeue 1\n");
  deQueue(queue);
  actionQueue(queue, &printInt);

  printf("dequeue 2\n");
  deQueue(queue);
  actionQueue(queue, &printInt);

  printf("dequeue 3\n");
  deQueue(queue);
  actionQueue(queue, &printInt);


  

  return 0;

}



