#include <stdio.h>	
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#ifndef MAX
#define MAX 1000
#endif


void printList(int a[], int num){
	for (int i = 0; i < num; i++)
	{
		printf("%d\t", a[i]);
	}
	printf("\n");
}

void initList(int list[]){
	int num = MAX;
	// time_t start, end;
	
	for (int i = 0; i < num; i++)
	{
		list[i] = rand()%100;
	}

}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int *list1 = (int*)malloc(sizeof(int) * MAX);
	initList(list1);
	clock_t s;

	printf("Before sorting:\n");
	// printList(list1,MAX);

	printf("Quick Soft 2 Ways:\n");
	s = clock();
	quickSoft2Ways(list1, 0, MAX - 1);
	printf("Time diff:%lf\n",(float)(clock() - s)/CLOCKS_PER_SEC );
	// printList(list1,MAX);
	free(list1);


	int *list2 = (int*)malloc(sizeof(int) * MAX);

	initList(list2);
	printf("Before sorting:\n");
	// printList(list2,MAX);
	printf("Quick Soft 3 Ways:\n");
	s = clock();
	quickSoft3Ways(list2, 0, MAX - 1);
	printf("Time diff:%lf\n",(float)(clock() - s)/CLOCKS_PER_SEC );
	// printList(list2,MAX);

	free(list2);
	return 0;
}