#include <libfdr/jval.h>
#include <libfdr/dllist.h>


typedef Dllist Stack;



Stack createStack();

void push(Stack stack, int val);

int pop(Stack stack);

void actionStack(Stack stack, void (*action)(int));
