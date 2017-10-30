#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libfdr/jrb.h>
#include <libgraph/graph.h>



typedef struct Station {
  int num;
  char *sign;
  char *name;
}Station;


typedef Graph Metro;


Station create_station(){
  Station station;
  station.sign = (char *)malloc(sizeof(char) * 100);
  station.name = (char *)malloc(sizeof(char) * 100);
  return station;
}

int readData(Metro metro, Station *station, char *fileName)
{
  FILE *f = fopen(fileName, "r");

  if(f == NULL)
    {
      printf("file can not be opened\n");
      return 0;
    };
  int count = 0;
  station[0] = create_station();
  char *buffer = (char *)malloc(sizeof(char) * 100);
  char *token = (char*)malloc(sizeof(char) * 100);

  char *s = "\t\n=";
  char *s1 = "\t\n= ";
  int readMode = 0;
  while(fgets(buffer, 100, f) != NULL)
    {
      token = strtok(buffer, s);
      if(strcmp(token, "[STATIONS]") == 0)
	{
	  readMode = 1;
	  continue;
	};
      
      if(strcmp(token, "[LINES]") == 0)
	{
	  readMode = 2;
	  continue;
	};
 
      
      if(readMode == 1)
	{
	  count++;
	  int vertex = token[1] - '0';
	  station[vertex].num = vertex;
	  station[vertex] = create_station();
	  strcpy(station[vertex].sign, token);
	  token = strtok(NULL, s);
	  strcpy(station[vertex].name, token);
	}
      else if(readMode == 2)
	{
	  int prev = -1;
	  while(1)
	    {
	      token = strtok(NULL, s1);
	      if(token == NULL)break;
	      int current = token[1] - '0';
	      if(prev == -1)
		{
		  prev = current;
		  continue;
		};
	      addEdge(metro, prev, current);
	      prev = current;
	    };
	}
    }
  fclose(f);
  return count;
}

void printStation(Station station)
{
  printf("%d. %s - %s\n", station.num, station.sign, station.name);
}


int *printAllAdjacentStations(Metro metro, Station *station, int n)
{
  printf("Input the name of station\n");
  char *stationName = (char *)malloc(sizeof(char) * 100);
  gets(stationName);
  int i;
  int s = -1;
  for(i = 0; i<= n; i++)
    {
      if(strcmp(station[i].name, stationName) == 0)
	{
	  s = i;
	  break;
	};
    }

  if(s == -1)
    {
      printf("Can not find station\n");
      return NULL;
    };

  int *output = (int *)malloc(sizeof(int) * 100);
  int num = getAdjacentVertices(metro, s, output);
  for(i = 0; i< num; i++)
    {
      printStation(station[output[i]]);
    };
  return output;
}
  
  
 

int main()
{
  Metro metro = createGraph();
  Station *station = (Station *)malloc(sizeof(Station) * 100);
  char *fileName = "data.txt";
  int n = readData(metro, station, fileName);
  int choice;
  do
    {
      printf("MENU\n");
      printf("1. Show all stations\n");
      printf("2. Find the adjacent stations of a station\n");
      printf("3. exit\n");
      scanf("%d", &choice);
      while(getchar() != '\n');

      if(choice == 1)
	{
	  int i;
	  for(i = 1; i<= n; i++)
	    {
	      printStation(station[i]);
	    };
	}

      if(choice == 2)
	{
         printAllAdjacentStations(metro, station, n);
	};
    }while(choice != 3);
          
  return 0;
}
	  
	  
