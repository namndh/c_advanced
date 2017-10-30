#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#ifndef MAX
#define MAX 100
#endif

#ifndef MIN
#define MIN 10
#endif

#define SWAP(a, b, size)                        \
     do                                         \
     {                                          \
          register size_t __size = (size);      \
          register char *__a = (a), *__b = (b); \
          do                                    \
          {                                     \
               char __tmp = *__a;               \
               *__a++ = *__b;                   \
               *__b++ = __tmp;                  \
          } while (--__size > 0);               \
     } while (0)

void qs_3_gen(void *base, long int last_index, long int size, int  (*compar)(const void*, const void*)){
	if (last_index <= 0 ) return;
	char* base2 = (char*)base;
	long int i, p;
	long int j, q;
	long int k;
	long int pivot_index;

	i = p = -1;
	j = q = last_index;
	pivot_index = last_index;

	while(1){
		while(compar(&base2[size*pivot_index], &base2[size*(++i)]) > 0);
		while(compar(&base2[size*pivot_index], &base2[size*(--j)]) < 0)
			if (i == j) break;
		if ( i >= j) break;
		SWAP(&base2[size * i], &base2[size * j], size);

		if (compar(&base2[size*pivot_index], &base2[size*j]) == 0){
			SWAP(&base2[size*i], &base2[size*(++p)],size);
		}

		if (compar(&base2[size*pivot_index], &base2[size*j]) == 0) {
			SWAP(&base2[size*(--q)], &base2[size*j],size);
		}
	}

	SWAP(&base2[size * i], &base2[size*pivot_index],size);
	j = i - 1;
	i = i + 1;

	for(k = 0; k <= p; k++, j--){
		SWAP(&base2[size*k],&base2[size*j],size);
	}

	for(k = last_index-1; k >= q; k --, i++){
		SWAP(&base2[size*k],&base2[size*i],size);
	}

	qs_3_gen(base2, j, size, compar);
	qs_3_gen(&base2[size*i],last_index-i,size,compar);
}

int *create_array(int size){
	int *array = (int *)malloc(sizeof(int)*size);
	int i;
	srand(time(NULL));
	for( i = 0;i < size;i++){
		array[i] = MIN + rand() % (MAX - MIN);
	}

	return array;
}

void printArray(int arr[], int size){
	int i;
	for(i = 0; i < size; i++){
		printf("%d\t",arr[i]);
	}

	printf("\n");
}

int compar_int(const void* a, const void* b){
	int ret = *(int*)a - *(int*)b;
	return ret;
}

int main(int argc, char const *argv[])
{
	int size = 1000;
	int * arr = create_array(size);
	int arr2[size];
	clock_t s;

	memcpy(arr2, arr, size * sizeof(int));
	printf("Before sorting:\n");
	printArray(arr,size);
	printf("Softing...\n");
	s= clock();
	qsort(arr,size,sizeof(int), compar_int);

	printf("Time to run qsort 2 ways built-in: %lf\n", (float)(clock() - s)/CLOCKS_PER_SEC);

	printf("After sorting:\n");
	printArray(arr, size);

	s = clock();
	qs_3_gen(arr2,size-1,sizeof(int),compar_int);
	printf("Time to run qsort 3 way generic: %lf\n", (float)(clock() - s)/CLOCKS_PER_SEC);
	printf("After sorting:\n");
	printArray(arr2,size);
	


	free(arr);
	return 0;
}