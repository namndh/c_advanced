#ifndef GENTABLE_H_
#define GENTABLE_H_

typedef struct Entry{
  void *key;
  void *value;
}Entry;

typedef struct SymbolTable{
  Entry *entries;
  int size;
  int total;
  Entry (*makeNode)(void *, void *);
  int (*compare)(void *, void *);
}SymbolTable;

void addEntry(SymbolTable *book, void *key, void *value);

SymbolTable *createSymbolTable(Entry (*makeNode)(void *, void *), int (*compare)(void *, void *),int size);

Entry *getEntry(void *key, SymbolTable *book);

void dropSymbolTable(SymbolTable *tab);

void travel(SymbolTable *tab, void (*action)(void *));

void quickSort(SymbolTable *list, int l, int r);

#endif
