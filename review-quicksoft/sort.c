#include "sort.h"


void swap(int* a, int* b){
	int temp; 
	temp = *a;
	*a = *b;	
	*b = temp;
}

int partition2Ways(int arr[], int left, int right){
	int pivot = arr[right];
	int i = left - 1;
	for (int j = left; j <= right - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			swap(&arr[i],&arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[right]);
	return i + 1;
}

void quickSoft2Ways(int arr[], int left, int right){
	if (left < right){
		int pivot = partition2Ways(arr, left, right);

		quickSoft2Ways(arr, left, pivot - 1);
		quickSoft2Ways(arr,pivot + 1,right);
	}
}


void quickSoft3Ways(int a[], int left, int right){

	if (right <= left ) return;

	int i = left - 1;
	int j = right;
	int p = left - 1;
	int q = right;
	int pivot = a[right];

	while(1){
		while (a[++i] < pivot);
		while (pivot < a[--j]){
			if (j == left)
				break;
		}
		if (i >= j){
			break;
		}
		
		swap(&a[i],&a[j]);

		if (a[i] == pivot){
			p ++;
			swap(&a[p],&a[i]);
		}

		if(a[j] == pivot){
			q--;
			swap(&a[j],&a[q]);
		}
	}

	swap(&a[i],&a[right]);

	j = i - 1;
	for (int k = left; k < p; k++, j--){
		swap(&a[k],&a[j]);
	}
	
	i = i + 1;
	for (int k = right-1; k > q; k--, i++){
		swap(&a[k],&a[i]);
	}

	quickSoft3Ways(a,left,j);
	quickSoft3Ways(a,i,right);
}
