#include <libfdr/dllist.h>


typedef Dllist Queue;


Queue createQueue(){
  Queue queue = new_dllist();
  return queue;
}

void freeQueue(Queue queue)
{
  if(queue == NULL)
    {
      printf("Error on queue\n");
      return;
    };
  free_dllist(queue);
  return ;
}


void enQueue(Queue queue, Jval jval)
{
  dll_append(queue, jval);
}


Jval deQueue(Queue queue)
{
  Dllist root_node = dll_first(queue);
  Jval node = dll_val(root_node);
  dll_delete_node(root_node);
  return node;
}


void enQueueP(Queue queue, Jval value, int (*compareNode)(Jval, Jval))
{
  if(queue == NULL)
    {
      printf("null queue \n");
      return;
    };

  if(dll_empty(queue))
    {
      enQueue(queue, value);
      return;
    };

  Dllist ptr;
  dll_traverse(ptr, queue)
    {
      if(compare_node(value, dll_val(ptr)) > 0)
	{
	  dll_append(
  
  
