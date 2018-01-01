#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main(){
  Graph graph = createGraph();
  addEdgeUndir(graph, 1, 3);
  addEdgeUndir(graph, 3, 2);
  addEdgeUndir(graph, 3, 4);
  addEdgeUndir(graph, 2, 2);
  addEdgeUndir(graph, 1, 4);


  int *output = (int *)malloc(sizeof(int) * 100);
  int n = getAdjacentVertices(graph, 3, output);
  int i;
  for(i = 0; i< n; i++)
    {
      printf("%d\n", output[i]);
    };
  return 0;
}
