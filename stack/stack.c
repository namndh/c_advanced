#include <stdio.h>
#include <stdlib.h>
#include <libfdr/dllist.h>
#include <libfdr/jval.h>


typedef Dllist Stack;


Stack createStack()
{
  Stack stack = new_dllist();
  return stack;
}



void push(Stack stack, Jval val)
{
  dll_prepend(stack, val);
}


Jval pop(Stack stack)
{
  Stack first = dll_first(stack);
  Jval val = dll_val(first);
  dll_delete_node(first);
  return val;
}

void actionStack(Stack stack, void (*action)(Jval))
{
  Stack ptr;
  dll_traverse(ptr, stack)
    {
      action(dll_val(ptr));
    };
}
