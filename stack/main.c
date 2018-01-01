#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void printInt(Jval jval)
{
  printf("%d\n", jval_i(jval));
}

int main()
{
  Stack stack = createStack();
  push(stack, new_jval_i(5));
  push(stack, new_jval_i(10));
  push(stack, new_jval_i(15));
  push(stack, new_jval_i(20));
  push(stack, new_jval_i(8));
  push(stack, new_jval_i(12));

  actionStack(stack, &printInt);

  pop(stack);

  printf("pop1 \n");
  actionStack(stack, &printInt);

  pop(stack);
  printf("pop2\n");
  actionStack(stack, &printInt);

  pop(stack);
  printf("pop3\n");
  actionStack(stack, &printInt);

  return 0;
}
