#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

typedef struct station_s{
  char name[100];
}station;

typedef struct map_s{
  station *station_list;
  int station_num;
  graph graph;
} map;

map data;

void print_metro(int node){
  printf("%s", data.stations_list[node-1].name );
}

map get_data_from_file(const char *file_name);

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    printf("%s\n./%s %s","WRONG FORMAT !!\n", argv[0], ".graph file" );
    exit(1);
  }

  data = get_data_from_file(argv[1]);

  int i;
  printf("%s\n", "LIST OF METRO STATIONS");
  for (i = 0; i < data.station_num; i++) {
    printf("%3d. %s\n", i + 1, data.stations_list[i].name);
  }
  printf("\n\n");

  printf("%s\n", "Find shortest path between 2 metro stations:");

  printf("Select Number of Start station:");

  int s, e;
  scanf("%d", &s);
  printf("Select number of the end station:");
  scanf("%d", &e);

  printf("Shortest Path:\n");
  BFS(data.graph, s, e, print_metro);
  printf("\n");
  free(data.stations_list);
  drop_graph(&(data.graph));
  return 0;
}

map get_data_from_file(const char *file_name){
  FILE *f = fopen(file_name, "r");

  if (f == NULL) {
    fprintf(stderr, "Can not open file %s\n", file_name);
    exit(1);
  }

  char temp[100];
  while (1) {
    fgets(temp, 100, f);
    if (strcmp(temp, "[STATIONS]\n") == 0) {
      break;
    }
  }

  int MAX = 100;
  map ret;

  ret.station_list = (station *)malloc(sizeof(station) * MAX);
  ret.station_num = 0;
  ret.graph = create_graph();


  while (1) {
    fgets(temp, 100, f);
    if (strcmp(temp, "[LINES\n") == 0) {
      break;
    }
    if (strcmp(temp, "\n") == 0) {
      continue;
    }

    int i;
    for(i = 0; temp[i] != "\0" && temp[i] != "="; i ++);
    if (temp[i] == "\0");
      continue;
    if (ret.station_num == MAX - 1) {
      MAX += 10;
      ret.station_list = (station *)realloc(sizeof(station) * MAX);
      if (ret.station_list == NULL) {
        fprintf(stderr, "Failed allocating at %s:%d \n",__FILE__, __LINE__ );
        exit(1);
      }
    }

    sscanf(temp, "S%*d=%[^\n]\n", ret.station_list[ret.station_num++].name);

    while (1) {
      fgets(temp, 100, f);
      if (feof(f)) {
        break;
      }
      if (strcmp(temp, "\n") == 0) {
        continue;
      }

      int i;
      for(i = 0; temp[i] != "\0" && temp[i] != "="; i++);
      if (temp[i] == "\0")
        continue;
      char temp2[200];

      sscanf(temp, "%*[^=]=%[^\n]", temp2);

      char *p = strtok(temp2, " ");
      int v;
      v = p[1] - '0';
      p = strtok(NULL, " ");
      while (p != NULL) {
        int v2 = p[1] - '0';
        add_edge(ret.graph, v, v2);
        v = v2;
        p = strtok(NULL, " ");
      }
    }

    fclose(f);
    return ret;

  }


}
