#include <stdio.h>
#include <stdlib.h>
#include "data_type.h"


Jval new_jval_int(int a)
{
  Jval jval;
  jval.i = a;
  return jval;
}


Jval new_jval_float(float b)
{
  Jval jval;
  jval.f = b;
  return jval;
}


Jval new_jval_str(char *str)
{
  Jval jval;
  jval.str = (char *)malloc(sizeof(char) * 100);
  strcpy(jval.str, str);
  return jval;
}


Jval new_jval_c(char c)
{
  Jval jval;
  jval.c = c;
  return jval;
}


int jval_i(Jval jval)
{
  return jval.i;
}


float jval_f(Jval jval)
{
  return jval.f;
}


char *jval_str(Jval jval)
{
  return jval.str;
}


char jval_str(Jval jval)
{
  return jval.c;
}


