#ifndef _DATA_TYPE_H
#define _DATA_TYPE_H

typedef struct node_t{
  void *data;
  struct node_t *next;
}Node;

typedef struct node_tree_t{
  void *data;
  struct node_tree_t *left;
  struct node_tree_t *right;
}Node_Tree;


typedef Node_Tree* Tree;

typedef struct list_t{
  Node *root;
  Node *end;
}List;

typedef union Jval{
  int i;
  float f;
  char *str;
  char c;
  void *v;
}Jval;



#endif
