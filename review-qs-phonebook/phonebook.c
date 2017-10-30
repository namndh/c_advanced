#include <stdio.h>
#include <stdlib.h>
#include <time.h>	
#include <string.h>

#define SWAP(a, b, size)                        \
     do                                         \
     {                                          \
          register size_t __size = (size);      \
          register char *__a = (a), *__b = (b); \
          do                                    \
          {                                     \
               char __tmp = *__a;               \
               *__a++ = *__b;                   \
               *__b++ = __tmp;                  \
          } while (--__size > 0);               \
     } while (0)

typedef	struct _phone_book
{
	char name [25], email[60], tel[12], dob[12];
}phone_book;

int count_line(FILE *fp);

phone_book* get_data_from_file(FILE *fp, int size);

void print_phone_book(phone_book *pb, int size);

void qs_3_gen(void *base, long int last_index, long int size, int  (*compar)(const void*, const void*));

int compar_name(const void *a, const void *b);

int main(int argc, char const *argv[])
{
	FILE *fp = fopen("phonebook.csv","r");
	if(fp == NULL){
		fprintf(stderr, "Can't open file\n");
		exit(1);
	}

	clock_t s;
	float t_qsort, t_qs_3_gen;
	int size_pb = count_line(fp);

	phone_book *p_book = get_data_from_file(fp,size_pb);
	phone_book p_book2[size_pb];
	memcpy(p_book2,p_book,sizeof(phone_book)*size_pb);

	s = clock();
	qs_3_gen(p_book2, size_pb - 1, sizeof(phone_book), compar_name);
	t_qs_3_gen = (float)(clock() - s)/CLOCKS_PER_SEC;

	s = clock();
	qsort(p_book, size_pb, sizeof(phone_book),compar_name);
	t_qsort = (float)(clock() - s)/CLOCKS_PER_SEC;

	printf("After sorting:\n");
	printf("Adress Book use qsort built-in:\n");
	print_phone_book(p_book,size_pb);
	printf("Time to run qsort built-int:%lf\n",t_qsort);

	printf("Phone Book use qsort 3 ways generic:\n");
	print_phone_book(p_book2,size_pb);
	printf("Time to run qsort 3 ways generic:%lf\n", t_qs_3_gen);\

	fclose(fp);

	return 0;
}

int count_line(FILE *fp){
	char s[1000];
	int count = 0;
	while(fgets(s, 1000,fp) != NULL){
		count++;
	}
	rewind(fp);
	return count;
}

phone_book* get_data_from_file(FILE* fp, int size){
	phone_book *pbook = (phone_book*)malloc(sizeof(phone_book)*size);
	if(pbook == NULL){
		fprintf(stderr, "Failed allocating in %s:%d\n",__FILE__,__LINE__);
		exit(1);
	}

	for (int i = 0; i < size; i++)
	{
		fscanf(fp,"%[^|]|%[^|]|%[^|]|%[^\n]\n", pbook->name, pbook->tel, pbook->email, pbook->dob);
		pbook++;
	}
	return pbook-size;
}

void print_phone_book(phone_book *pb, int size){
	printf("\n\n");
	printf("%-25s %-13s %-62s %-13s\n", "Name","Tel","Email", "Date of Birth");
	for (int i = 0; i < size; i++)
	{
		printf("%-25s %-13s %-62s %-13s\n",pb->name,pb->tel,
		pb->email, pb->dob );
		pb ++;
	}
	printf("\n");
}

void qs_3_gen(void *base, long int last_index, long int size, int  (*compar)(const void*, const void*)){
	if (last_index <= 0 ) return;
	char* base2 = (char*)base;
	long int i, p;
	long int j, q;
	long int k;
	long int pivot_index;

	i = p = -1;
	j = q = last_index;
	pivot_index = last_index;

	while(1){
		while(compar(&base2[size*pivot_index], &base2[size*(++i)]) > 0);
		while(compar(&base2[size*pivot_index], &base2[size*(--j)]) < 0)
			if (i == j) break;
		if ( i >= j) break;
		SWAP(&base2[size * i], &base2[size * j], size);

		if (compar(&base2[size*pivot_index], &base2[size*j]) == 0){
			SWAP(&base2[size*i], &base2[size*(++p)],size);
		}

		if (compar(&base2[size*pivot_index], &base2[size*j]) == 0) {
			SWAP(&base2[size*(--q)], &base2[size*j],size);
		}
	}

	SWAP(&base2[size * i], &base2[size*pivot_index],size);
	j = i - 1;
	i = i + 1;

	for(k = 0; k <= p; k++, j--){
		SWAP(&base2[size*k],&base2[size*j],size);
	}

	for(k = last_index-1; k >= q; k --, i++){
		SWAP(&base2[size*k],&base2[size*i],size);
	}

	qs_3_gen(base2, j, size, compar);
	qs_3_gen(&base2[size*i],last_index-i,size,compar);
}

int compar_name(const void* a, const void* b){
	phone_book _a = *(phone_book*)a;
	phone_book _b = *(phone_book*)b;
	return strcmp(_a.name,_b.name);
}

