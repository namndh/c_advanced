#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "data_type.h"

Tree make_tree(void *data, size_t size_data);
  
void insert_data(Tree *tree, void *data, size_t size ,int (* compare)(void *, void *));

Tree search(Tree tree, void *data, int (*compare)(void *, void *));

void delete_node(Tree *tree, void *data, int (*compare)(void *, void *));

void preorder_traversal(Tree tree, void (*action)(void *));

void inorder_traversal(Tree tree, void (*action)(void *));

void postorder_traversal(Tree tree, void (*action)(void *));

#endif