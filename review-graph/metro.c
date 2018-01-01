#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libfdr/jrb.h>
#include "graph.h"
#include "utility.h"

typedef struct Station{
    int num;
    int *sign;
    int *name;
}Station;

typedef Graph Metro;

Station create_station(){
    Station stt;
    stt.num = 0;
    stt.sign = (char *)malloc(sizeof(char)*100);
    stt.name = (char *)malloc(sizeof(char)*100);
    return stt;
}

int readData(Metro metro, Station *stt, char *filename){
    FILE *f = fopen(filename, "r");

    if(f == NULL){
        printf("Cannot open input file!");
        exit(1);
    }
    int count = 0;
    stt[0] = create_station();
    char *buff = (char *)malloc(sizeof(char)*100);
    char *token = (char *)malloc(sizeof(char)*100);

    char *s = "\t\n=";
    char *s1 = "\t\n= ";
    int readMode = 0;
    while(fgets(buff, 100, f) != NULL){
        token = strtok(buff, s);
        if (strcmp(token, "[STATIONS]") == 0){
            readMode = 1;
            continue;
        }
        if (strcmp(token, "[LINES]") == 0){
            readMode = 2;
            continue;
        }

        if (readMode == 1){
            count ++;
            int vertex = token[1] - '0';
            stt[vertex] = create_station();
            stt[vertex].num = vertex;
            strcpy(stt[vertex].sign, token);
            token = strtok(NULL, s);
            strcpy(stt[vertex].name, token);
        }

        else if (readMode == 2){
            int prev = -1;
            while(1){
                token = strtok(NULL, s1);
                if(token == NULL) break;
                int current = token[1] -'0';
                if (prev == -1){
                    prev = current;
                    continue;
                }
                addEdge(metro, prev, current);
                prev = current;
            }
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

void printNode(int a) {
  printf("%d ", a );
}

int main(){
    Metro metro = createGraph();
    Station *station = (Station *)malloc(sizeof(Station) * 100);
    char *filename = "data.txt";
    int n = readData(metro, station, filename);
    while(1){
        switch(get_menu("Show all statons;Find the adjecent stations of a station;DFS;BFS",4,1)){
            case 1:{
                int i;
                for(i = 1; i <= n; i ++){
                    printStation(station[i]);
                }
            } break;
            case 2:{
                // printAllAdjacentStations(metro, station, n);
            } break;
            case 3:{
              DFS(metro, 1, &printNode);
            } break;
            case 4: {
                printf("\t\tAnswer:");
              BFS(metro, 1, &printNode);
            } break;
            case 0: goto end; break;
            default: exit(1);
        }
    }
    end:
        // dropGraph(metro);
        free(station);
    return 0;
}
