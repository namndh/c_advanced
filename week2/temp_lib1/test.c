#include <stdio.h>
#include <stdlib.h>
#include "data_type.h"
#include "Binary_Tree.h"
#include <time.h>


int int_compare(void *a, void *b)
{
  //  printf("a = %d\n", *(int *)a);
  //printf("b = %d\n", *(int *)b);
  return *(int *)a - *(int *)b;
}

void print_int(void *a)
{
  printf("%d\n", *(int *)a);
}


int main()
{
  srand(time(NULL));
  int data = 5;
  Tree tree = make_tree(&data, sizeof(int));
  int num = 20;
  int i;
  for(i = 0; i < num; i++)
    {
      int temp = rand()% 30;
      printf("%d\n", temp);
      insert_data(&tree, &temp, sizeof(int) ,&int_compare);
    };
  printf("________________________\n");
  inorder_traversal(tree, &print_int);
  return 0;
}
  
