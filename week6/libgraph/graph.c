#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


Graph createGraph(int size_max){
  Graph graph;
  graph.matrix = (int **)malloc(sizeof(int *) * size_max);
  int i;
  for(i = 0; i< size_max; i++)
    {
      graph.matrix[i] = (int *)malloc(sizeof(int) * size_max);
    };

  graph.sizemax = size_max;
  return graph;
}



void addEdge(Graph graph, int v1, int v2)
{
  if(v1 >= graph.sizemax || v2>=graph.sizemax)return;
  graph.matrix[v1][v2] = 1;
  graph.matrix[v2][v1] = 1;
}


int adjacent(Graph graph, int v1, int v2)
{
  if(v1 >= graph.sizemax || v2 >= graph.sizemax)return 0;
  return graph.matrix[v1][v2];
}


int getAdjacentVertices(Graph graph, int vertex, int *output)
{
  if(vertex >= graph.sizemax)return 0;
  int i;
  int count = 0;
  for(i = 0; i< graph.sizemax; i++)
    {
      if(graph.matrix[vertex][i])
	{
	  output[count] = i;
	  count++;
	};
    };
  return count;
}

void dropGraph(Graph graph)
{
  int i;
  for(i = 0; i< graph.sizemax; i++)
    {
      free(graph.matrix[i]);
    };
  free(graph.matrix);
}
