#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libfdr/jrb.h>
#include <libfdr/jval.h>
#include "utility.h"

#define TXT "dns.txt"

typedef JRB DNS;

int num_of_iter;

int get_data_from_file(DNS dnsList);

// int get_data_from_file1(DNS dnsList);

int count_line(FILE *fp);

void print_data(DNS dnsList);

int add_domain(DNS dnsList, char *domain, char *ip);

void write_to_file(DNS dnsList,int num);

char * search_ip(DNS dnsList, char *domain);

char *search_domain(DNS dnsList, char *ip);

int main(int argc, char const *argv[])
{

	DNS dnsList = make_jrb();
	int num = 0;
	while(1){
		switch(get_menu("Display all;Add DNS;Find IP;Find domain",4,1)){
			case 1:{
				printf("\n\n\t\tTable of DNS:\n");
				dnsList = make_jrb();
				num = get_data_from_file(dnsList);
				print_data(dnsList);
			} break;

			case 2:{
				printf("\n\n");
				char *domain = (char *)malloc(sizeof(char) * 100);
	  			char *ip = (char *)malloc(sizeof(char) * 100);
				printf("\t\t> Domain to add:" );
				scanf(" %[^\n]", domain);mfflush();
				printf("\t\t> IP to add:" );
				scanf(" %[^\n]", ip);mfflush();
	  			num += add_domain(dnsList, domain, ip);
	  			write_to_file(dnsList, num);
			} break;

			case 3: {
				printf("\n\n");
			    char *domain = (char*)malloc(sizeof(char) * 100);
			    printf("\t\t> Input the domain to get ip : ");
			    scanf(" %[^\n]", domain);mfflush();
			    char *ip = search_ip(dnsList, domain);
			    if(ip != NULL)
			    	{
			      		printf("\t\t%s\n", ip);
			    	};
			} break;

			case 4: {
				printf("\n\n");
	  			char *ip = (char*)malloc(sizeof(char) * 100);
	  			printf("Input the ip to get domain: ");
				scanf("%[^\n]", ip);mfflush();
	  			char *domain = search_domain(dnsList, ip);
	  			if(domain != NULL)
	    			{
	      				printf("\t\t%s\n", domain);
	    			};
			} break;
			case 0:
				goto end;
			break;

			default: exit(1);
		}
	}

	end :
		printf("\n\n\t\tTable of DNS:\n");
		print_data(dnsList);
		jrb_free_tree(dnsList);
	return 0;
}



int get_data_from_file(DNS dnsList)
{
  FILE *f = fopen(TXT, "r");
  if(f == NULL)
    {
      fprintf(stderr, "\t\tCan not open the file %s : %d\n",__FILE__, __LINE__);
    };
  if(dnsList == NULL)return 0;
  float line_num = count_line(f);
  if (line_num - 2*(line_num/2) != 0)
  {
  	printf("\t\tError file form!\n");\
  	exit(1);
  }
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
	  printf("\t\tForm of file error\n");
	  return count;
	};
      strcpy(domain, buffer);
      strcpy(ip, buffer2);
      domain[strlen(domain) - 1] = '\0';
      ip[strlen(ip) - 1] = '\0';
      JRB find = jrb_find_str(dnsList,domain);
		if (find == NULL){
			jrb_insert_str(dnsList, domain, new_jval_s(ip));
			count++;
		} else {
			printf("\t\tDuplicate elements!!\n");
			exit(1);
		}
      // jrb_insert_str(dnsList, domain, new_jval_s(ip));
      // count++;
    };
  fclose(f);
  return count;
}

// int get_data_from_file1(DNS dnsList){
// 	FILE *f = fopen(TXT,"r");
// 	if (f == NULL)
// 	{
// 		fprintf(stderr, "\t\tCan not open the file!\n");
// 		exit(1);
// 	}
// 	if (dnsList == NULL) exit(1);

// 	// char* num_Iter;
// 	// fgets(num_Iter,100,f);
// 	// if (strlen(num_Iter) > 1)
// 	// {
// 	// 	printf("\t\tWrong format of the file\n");
// 	// 	exit(1);
// 	// }
// 	// int count = 0;
// 	// int line = count_line(f);
// 	// for (int i = 0; i < line; i++)
// 	// {
// 	// 	char *domain = (char *)malloc(sizeof(char) * 100);
//  //      	char *ip = (char *)malloc(sizeof(char) * 100);
//  //      	fgets(domain,100,f);
//  //      	fgets(ip,100,f);
//  //      	domain[strlen(domain) - 1] = '\0';
//  //      	ip[strlen(ip) - 1] = '\0';
// 	// 	JRB find = jrb_find_str(dnsList,domain);
// 	// 	if (find == NULL){
// 	// 		jrb_insert_str(dnsList, domain, new_jval_s(ip));
// 	// 		count++;
// 	// 	} else {
// 	// 		printf("\t\tDuplicate elements!!\n");
// 	// 		exit(1);
// 	// 	}
// 	// }
// 	// fclose(f);
// 	// return count;

// }

void print_data(DNS dnsList)
{
  JRB ptr;
  jrb_traverse(ptr, dnsList)
    {
      printf("\t\t%s\t%s\n", jval_s(ptr->key), jval_s(ptr->val));
    };
}


int add_domain(DNS dnsList, char *domain, char *ip)
{
  if(dnsList == NULL)
    {
      printf("\t\tNULL DNS\n");
      return 0;
    };
  jrb_insert_str(dnsList, domain, new_jval_s(ip));
  return 1;
}

void write_to_file(DNS dnsList,int num)
{
  if(dnsList == NULL)
    {
      printf("\t\tNULL DNS\n");
      return;
    };
  FILE * f = fopen(TXT, "w");
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

char * search_ip(DNS dnsList, char *domain)
{
  JRB domainResult = jrb_find_str(dnsList, domain);
  if(domainResult == NULL)
    {
      printf("\t\tNo domain name %s \n", domain);
      return NULL;
    };
  return jval_s(domainResult->val);
}

char *search_domain(DNS dnsList, char *ip)
{
  JRB ptr;
  jrb_traverse(ptr, dnsList)
    {
      if(strcmp(jval_s(ptr->val), ip) == 0)
	{
	  return jval_s(ptr->key);
	};
    };
  printf("\t\tNo IP like: %s\n", ip);
  return NULL;
}

int count_line(FILE *fp){
	char s[1000];
	int count = 0;
	while(fgets(s,1000,fp) != NULL){
		count ++;
	}
	rewind(fp);
	return count;
}