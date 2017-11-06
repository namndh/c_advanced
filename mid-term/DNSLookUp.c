#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libfdr/jval.h>
#include <libfdr/jrb.h>

typedef JRB DNS;

int readData(DNS dnsList, char *fileName)
{
  FILE *f = fopen(fileName, "r");
  if(f == NULL)
    {
      printf("File error! \n Try again\n");
      return 0;
    };
  if(dnsList == NULL)return 0;

  char *buffer = (char *)malloc(sizeof(char) * 100);
  char *buffer2 = (char *)malloc(sizeof(char) * 100);
  fgets(buffer, 100, f);
  int count = 0;
  while(fgets(buffer, 100, f) != NULL)
    {
      char *domain = (char *)malloc(sizeof(char) * 100);
      char *ip = (char *)malloc(sizeof(char) * 100);
      if(fgets(buffer2, 100, f) == NULL)
	{
	  printf("Form of file error\n");
	  return count;
	};
      strcpy(domain, buffer);
      strcpy(ip, buffer2);
      domain[strlen(domain) - 1] = '\0';
      ip[strlen(ip) - 1] = '\0';
      jrb_insert_str(dnsList, domain, new_jval_s(ip));
      count++;
    };
  fclose(f);
  return count;
}


void printAllData(DNS dnsList)
{
  JRB ptr;
  jrb_traverse(ptr, dnsList)
    {
      printf("%s\t%s\n", jval_s(ptr->key), jval_s(ptr->val));
    };
}


int insertDomain(DNS dnsList, char *domain, char *ip)
{
  if(dnsList == NULL)
    {
      printf("NULL DNS\n");
      return 0;
    };
  jrb_insert_str(dnsList, domain, new_jval_s(ip));
  return 1;
}

void writeToFile(DNS dnsList,int num,  char *fileName)
{
  if(dnsList == NULL)
    {
      printf("NULL DNS\n");
      return;
    };
  FILE * f = fopen(fileName, "w");
  if(f == NULL)
    {
      printf("Writing to file error\n");
    };
  fprintf(f, "%d\n", num);
  JRB ptr;
  jrb_traverse(ptr, dnsList)
    {
      fprintf(f, "%s\n%s\n", jval_s(ptr->key), jval_s(ptr->val));
    };
  fclose(f);
}

char * lookForIP(DNS dnsList, char *domain)
{
  JRB domainResult = jrb_find_str(dnsList, domain);
  if(domainResult == NULL)
    {
      printf("No domain name %s \n", domain);
      return NULL;
    };
  return jval_s(domainResult->val);
}

char *lookForDomain(DNS dnsList, char *ip)
{
  JRB ptr;
  jrb_traverse(ptr, dnsList)
    {
      if(strcmp(jval_s(ptr->val), ip) == 0)
	{
	  return jval_s(ptr->key);
	};
    };
  printf("No IP like: %s\n", ip);
  return NULL;
}
  

int main()
{
  char *fileName = (char *)malloc(sizeof(char) * 100);
  DNS dnsList = make_jrb();
  int choice;
  int num = 0;
  do
    {
      printf("MENU \n");
      printf("1. Read data and show all data\n");
      printf("2. Insert domain into memory\n");
      printf("3. Look up for IP \n");
      printf("4. Look up for domain with IP\n");
      printf("5. Exit\n");
      printf("Your choice: ");
      scanf("%d", &choice);
      while(getchar() != '\n');

      if(choice == 1)
	{
	  dnsList = make_jrb();
	  printf("Input file name: ");
	  gets(fileName);
	  num = readData(dnsList, fileName);
	  printAllData(dnsList);
	}

      if(choice == 2)
	{
	  char *domain = (char *)malloc(sizeof(char) * 100);
	  char *ip = (char *)malloc(sizeof(char) * 100);
	  printf("Input the domain: ");
	  gets(domain);
	  printf("Input the ip : ");
	  gets(ip);
	  num += insertDomain(dnsList, domain, ip);
	  writeToFile(dnsList, num, fileName);
	};
      
      if(choice == 3)
	{
	  char *domain = (char*)malloc(sizeof(char) * 100);
	  printf("Input the domain to get ip : ");
	  gets(domain);
	  char *ip = lookForIP(dnsList, domain);
	  if(ip != NULL)
	    {
	      printf("%s\n", ip);
	    };
	}

      if(choice == 4)
	{
	  char *ip = (char*)malloc(sizeof(char) * 100);
	  printf("Input the ip to get domain: ");
	  gets(ip);
	  char *domain = lookForDomain(dnsList, ip);
	  if(domain != NULL)
	    {
	      printf("%s\n", domain);
	    };
	}

      
    }while(choice != 5);
}
	  
