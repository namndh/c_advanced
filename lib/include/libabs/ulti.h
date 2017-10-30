#ifndef _ULTI_H_
#define _ULTI_H_
#include <stdio.h>
void swap(void *list, size_t size_data ,int i, int j);
 
void quick_sort(void *list, size_t size_data, int l, int r, int (*compare)(void *, void *));
#endif
