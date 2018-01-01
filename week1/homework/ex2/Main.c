#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gen_quick_sort.c"


typedef struct Phone
{
  char name[40];
  char tel[30];
  char email[50];
  int score;
}Phone;


int phone_compare(void *phone1, void *phone2)
{
  return strcmp((*(Phone *)phone1).name, (*(Phone *)phone2).name);
}


void print_phone_list(Phone *phone_list, int num)
{
  int i;
  for(i = 0; i< num; i++)
    {
      printf("%d. Name: %s\n", i + 1, phone_list[i].name);
      printf("Tel: %s\n", phone_list[i].tel);
      printf("Email: %s\n", phone_list[i].email);
    };
}


int read_data(char *file_name, Phone *phone_book)
{
  FILE *f = fopen(file_name, "r");

  char *buffer = (char *)malloc(sizeof(char) * 1000);

  char *token = (char *)malloc(sizeof(char) * 100);

  char *s = "\n\t";

  int num = 0;

  fgets(buffer, 1000, f);
  
  while( fgets(buffer, 1000, f) != NULL)
    {
      printf("%d\n", num);
      
      token = strtok(buffer, s);

      strcpy(phone_book[num].name, token);

      token = strtok(NULL, s);

      strcpy(phone_book[num].tel, token);

      token = strtok(NULL, s);

      strcpy(phone_book[num].email, token);

      num++;
    };
  //free(buffer);
  //free(token);
  fclose(f);
  return num;
}


int main()
{
  char *file_name = "phoneBook.txt";

  Phone *phone_book = (Phone *)malloc(sizeof(Phone) * 100);

  int num = read_data(file_name, phone_book);

  printf("Before sorting\n");
  print_phone_list(phone_book, num);

  quick_sort(phone_book, sizeof(Phone), 0, num - 1 , phone_compare);
  
  printf("After sorting \n");
  print_phone_list(phone_book, num);
  return 0;
}

 
  
  

