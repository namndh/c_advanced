#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



int main()
{
  Graph graph = createGraph(10);

  addEdge(graph, 0, 5);
  addEdge(graph, 2, 4);
  addEdge(graph, 3, 2);


  int *output = (int *)malloc(sizeof(int) * 100);
  int n = getAdjacentVertices(graph, 3, output);
  int i = 0;
  printf("%d\n", n);
  for(i = 0; i< n; i++)
    {
      printf("%d\n", output[i]);
    };
  dropGraph(graph);
  return 0;
}
