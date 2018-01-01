#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"


Queue createQueue()
{
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


void enQueue(Queue queue, int value)
{
  dll_append(queue, new_jval_i(value));
}


int deQueue(Queue queue)
{
  Dllist root = dll_first(queue);
  Jval val = dll_val(root);
  dll_delete_node(root);
  return jval_i(val);
}


/* void enQueueP(Queue queue, Jval value, int (*compareNode)(Jval, Jval)) */
/* { */
/*   if(queue == NULL) */
/*     { */
/*       printf("null queue \n"); */
/*       return; */
/*     }; */

/*   if(dll_empty(queue)) */
/*     { */
/*       enQueue(queue, value); */
/*       return; */
/*     }; */

/*   Dllist ptr; */
/*   dll_traverse(ptr, queue) */
/*     { */
/*       if(compareNode(value, dll_val(ptr)) > 0) */
/* 	{ */
/* 	  dll_insert_b(ptr, value); */
/* 	  break; */
/* 	}; */
/*     }; */
/* } */


/* void actionQueue(Queue queue, void (*actionValue)(int)) */
/* { */
/*   Queue ptr; */
/*   dll_traverse(ptr, queue) */
/*     { */
/*       actionValue(new_jval_i(ptr->val)); */
/*     }; */
/* } */





      

      
  
  
