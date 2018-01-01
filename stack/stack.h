#include <libfdr/jval.h>
#include <libfdr/dllist.h>


typedef Dllist Stack;


Stack createStack();


void push(Stack stack, Jval val);


Jval pop(Stack stack);

void actionStack(Stack stack, void (*action)(Jval));
