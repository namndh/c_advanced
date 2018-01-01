#include <stdio.h>
#include <stdlib.h>
#include <libfdr/dllist.h>
#include <libfdr/jval.h>
#include "stack.h"


Stack createStack()
{
  Stack stack = new_dllist();
  return stack;
}



void push(Stack stack, int val)
{
  dll_prepend(stack, new_jval_i(val));
}


int pop(Stack stack)
{
  Stack first = dll_first(stack);
  Jval val = dll_val(first);
  dll_delete_node(first);
  return jval_i(val);
}

void actionStack(Stack stack, void (*action)(int))
{
  Stack ptr;
  dll_traverse(ptr, stack)
    {
      action(jval_i(dll_val(ptr)));
    };
}
