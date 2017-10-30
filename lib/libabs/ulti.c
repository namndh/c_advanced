#include "ulti.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void swap(void *list, size_t size_data ,int i, int j)
{
  const void *temp_point = list;
  void *temp_memory = malloc(size_data);
  memcpy(temp_memory, (temp_point + i * size_data), size_data);
  memcpy((list + i * size_data) , (temp_point + j* size_data), size_data);
  memcpy((list + j * size_data), temp_memory, size_data);
}


void quick_sort(void *list, size_t size_data, int l, int r, int (*compare)(void *, void *))
{
  if(l >= r)return;
  int i = l;
  int j = r - 1;
  int p = l - 1;
  int q = r;
  while(1)
    {
      while(compare(list + i * size_data, list + r * size_data) < 0)
	i++;
      while(compare(list + j * size_data, list + r * size_data) > 0 && j > l)
	j--;
      if ( i >= j) break;
      swap(list, size_data, i , j);
      if( compare(list + i * size_data, list + r * size_data) == 0)
	{
	  p++;
	  swap(list, size_data, i, p);
	}
      if( compare(list + j * size_data, list + r * size_data) == 0)
	{
	  q--;
	  swap(list, size_data, j, q);
	};
      i++;
      j--;
    };
  int k = 0;
  for(k = l; k <= p; k++)
    {
      swap(list, size_data, j, k);
      j--;
    };
  for(k = r; k >= q; k--)
    {
      swap(list, size_data, i , k);
      i++;
    };
  quick_sort(list, size_data, l, j, compare);
  quick_sort(list, size_data, i, r, compare);
}
