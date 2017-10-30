#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gentable.h"



void addEntry(SymbolTable *book, void *key, void *value)
{
  if(book == NULL || key == NULL || value == NULL)
    {
      printf("Input error\n");
      return;
    };
  void *new_key = strdup(key);
  void *new_value = strdup(value);
  //memcpy(Entry->key, key, (strlen((char*)key) + 1))
  //memcpy(Entry->value, value, (strlen((char*)value + 1))
  if( book->total <= book->size)
    {
      book->entries[book->total] = book->makeNode(new_key, new_value);
      book->total+=1;
    };
}


SymbolTable *createSymbolTable(Entry (*makeNode)(void *, void *), int (*compare)(void *, void *),int size)
{
  SymbolTable *symbolTable = malloc(sizeof(SymbolTable));
  symbolTable->makeNode = makeNode;
  symbolTable->compare = compare;
  symbolTable->size = size;
  symbolTable->entries = (Entry *)malloc(sizeof(Entry) * size);
  return symbolTable;
}


Entry *getEntry(void *key, SymbolTable *book)
{
  if(book == NULL || key == NULL)return NULL;

  int i;
  for(i = 0; i< book->total; i++)
    {
      if(book->compare(book->entries[i].key, key) == 0)return &book->entries[i];
    }
  return NULL;
}


void dropSymbolTable(SymbolTable *tab)
{
  if(tab == NULL)return;
  for(int i = 0; i< tab->total; i++)
    {
      free(&tab->entries[i]);
    };
}

void swapEntry(void *list, size_t dataSize, int i, int j)
{
  void *temp1 = list;
  void *temp_memory = malloc(dataSize);
  memcpy(temp_memory, temp1 + i *dataSize, dataSize);
  memcpy(temp1 + i *dataSize, temp1 + j * dataSize, dataSize);
  memcpy(temp1 + j * dataSize, temp_memory, dataSize);
}
  
  
  
void travel(SymbolTable *tab, void (*action)(void *))
{
  int i;
  if(tab == NULL)return;
  for(i = 0; i< tab->total; i++)
    {
      action(tab->entries[i].key);
      action(tab->entries[i].value);
    };
}

void quickSort(SymbolTable *list, int l, int r)
{
  if(l >= r) return;
  Entry *tempList = NULL;
  tempList =  list->entries;
  int i = l;
  int j = r-1;
  int p = l-1;
  int q = r ;
  while(1)
    {
      while(list->compare(tempList + i , tempList + r ) <0 )i++;
      while(list->compare(tempList + j , tempList + r ) > 0 && j > l) j--;
      if(i >= j)break;
      swapEntry(tempList, sizeof(Entry), i, j);

      if(list->compare(tempList + i, tempList + r ) == 0) {
	p++;
	swapEntry(tempList, sizeof(Entry), i, p);
	
      };
      if(list->compare(tempList + j , tempList + r) == 0) {
	q--;
	swapEntry(tempList, sizeof(Entry), j, q);
      };
      i++;
      j--;
    }

  int k;
  for(k = l; k <= p; k++)
    {
      swapEntry(tempList, sizeof(Entry), j, k);
      j--;
    }
  for(k = r; k >= q; k--)
    {
      swapEntry(tempList, sizeof(Entry), i, k);
      i++;
    };
  quickSort(list, l, j);
  quickSort(list, i, r);  
  
}
