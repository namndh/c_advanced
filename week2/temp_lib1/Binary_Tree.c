#include <stdio.h>
#include <stdlib.h>
#include "data_type.h"
#include "Binary_Tree.h"
#include <string.h>


Tree make_tree(void *data, size_t size_data)
{
  Tree new_tree = malloc(sizeof(Node_Tree));
  const void *temp = data;
  void *pointer = malloc(sizeof(size_data));
  memcpy(pointer, temp, size_data);
  new_tree->data = pointer;
  new_tree->left = NULL;
  new_tree->right = NULL;
}

void insert_data(Tree *tree, void *data, size_t size ,int (* compare)(void *, void *))
{
  if(*tree == NULL){
    *tree = make_tree(data, size);
    return;
  }
  if((*compare)(data, (*tree)->data) == 0)return;
  else if((*compare)(data, (*tree)->data) > 0) insert_data(&((*tree)->right) ,data,size , compare);
  else if((*compare)(data, (*tree)->data) < 0) insert_data(&((*tree)->left),data, size ,compare);
}


Tree search(Tree tree, void *data, int (*compare)(void *, void *))
{
  if(tree == NULL){
    return NULL;
  }
  if((*compare)(data, tree->data) > 0 && tree->right != NULL)
    {
      return search(tree->right, data, compare);
    }
  else if((*compare)(data, tree->data) < 0 && tree->left != NULL)
    {
      return search(tree->left, data, compare);
    }
  else if((*compare)(data, tree->data) == 0)return tree;
  else 
  return NULL;
}
  
void *delete_min(Tree *tree)
{
  
  if(*tree == NULL)return NULL;

  if((*tree)->left == NULL)
    {
      void *k = (*tree)->data;
      (*tree) = (*tree)->right;
      return k;
    }
  else
    return delete_min(&((*tree)-> left));
}


void delete_node(Tree *tree, void *data, int (*compare)(void *, void *))
{
  if((*tree) == NULL)return;
  if(compare(data, (*tree)->data) < 0)delete_node(&((*tree)->left), data, compare);
  else if(compare(data, (*tree)->data) > 0)delete_node(&((*tree)->right), data, compare);
  else
    {
      if((*tree)->left == NULL)
	{
	  (*tree) = (*tree)->right;
	  return;
	}
      else if((*tree)->right == NULL)
	{
	  (*tree) = (*tree)->left;
	  return;
	};
      (*tree)->data = delete_min(&((*tree)->right));
    };
}


void preorder_traversal(Tree tree, void (*action)(void *))
{
  action(tree->data);
  if(tree->left != NULL)
    preorder_traversal(tree->left, action);
  if(tree->right != NULL)
    preorder_traversal(tree->right, action);
}

void inorder_traversal(Tree tree, void (*action)(void *))
{
  if(tree->left != NULL)
    inorder_traversal(tree->left, action);
  action(tree->data);
  if(tree->right != NULL)
    inorder_traversal(tree->right, action);
}


void postorder_traversal(Tree tree, void (*action)(void *))
{
  if(tree->left != NULL)
    postorder_traversal(tree->left, action);
  if(tree->right != NULL)
    postorder_traversal(tree->right, action);
  action(tree->data);
}
