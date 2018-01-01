#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int *list, int i, int j)
{
  int temp = list[i];
  list[i] = list[j];
  list[j] = temp;
}

void quickSort(int *list, int l, int r)
{
  if( l >= r) return;
  int i = l;
  int j = r - 1 ;
  int p = l-1;
  int q = r;
  int pivot = list[r];
  while(1)
    {
      while(list[i] < pivot) i++;
      while(list[j] > pivot && j > l) j--;
      if(i >= j) break;
      swap(list, i, j);
      if(list[i] == pivot)
	{
	  p++;
	  swap(list, i, p);
	}
      if(list[j] == pivot)
	{
	  q--;
	  swap(list, j, q);
	};
      i++;
      j--;
    };
  int k = 0;
  for(k = l; k <= p; k++)
    {
      swap(list, k, j);
      j--;
    }
  for(k = r; k >= q; k--)
    {
      swap(list, k, i);
      i++;
    };
  quickSort(list, l, j);
  quickSort(list, i, r);
}

void printList(int *list, int num)
{
  int i;
  for(i = 0; i< num; i++)
    {
      printf("%d\n", list[i]);
    };
}


int main()
{
  srand(time(NULL));
  int *list = (int *)malloc(sizeof(int) * 1000);
  int i;
  int num = 10;
  for (i = 0; i< num; i++)
    {
      list[i] = rand()%30;
    };
  printList(list, num);
  printf("After sort: \n");
  quickSort(list, 0, num -1);
  printList(list, num);
  return 0;
}
