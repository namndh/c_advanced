#include <stdio.h>
#include <stdlib.h>
#include <libfdr/jval.h>
#include <libfdr/jrb.h>
#include <string.h>


void readData(JRB tree, char *fileName){
  char *buffer = (char *)malloc(sizeof(char) * 100);

  char *token = (char *)malloc(sizeof(char) * 100);

  char * s = "\t\n";

  FILE *f = fopen(fileName, "r");

  if(f == NULL)
    {
      printf("Phone.c: Cannot open file\n");
      return;
    }

  while(fgets(buffer, 100, f) != NULL)
    {
      token = strtok(buffer, s);

      char *name = (char *)malloc(sizeof(char)*100);

      strcpy(name, token);

      char *tel = (char *)malloc(sizeof(char) * 100);

      token = strtok(NULL, s);

      strcpy(tel, token);

      jrb_insert_str(tree, name, new_jval_s(tel));

    };
}


int main (){
  JRB tree = make_jrb();
  readData(tree, "phoneBook.txt");
  JRB node = make_jrb();
  jrb_traverse(node, tree)
    {
      printf("%s - %s\n", jval_s(node->key), jval_s(node->val));
    };
  printf("---------------------------------------\n");
  node = jrb_find_str(tree, "Vo Nguyen Giap");
  node->val = new_jval_s("12345678");
  jrb_traverse(node, tree)
    {
      printf("%s - %s\n", jval_s(node->key), jval_s(node->val));
    };
  printf("---------------------------------------\n");
  node = jrb_find_str(tree, "Dinh Anh Dung");
  jrb_delete_node(node);
  jrb_traverse(node, tree)
    {
      printf("%s - %s\n", jval_s(node->key), jval_s(node->val));
    };

  return 0;
}

  
