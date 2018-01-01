#include <stdio.h>
#include <stdlib.h>
#include <libfdr/jrb.h>
#include <libfdr/jval.h>
#include <libfdr/dllist.h>
#include "graph.h"

void printOutput(int *output, int n)
{
  int i;
  for(i = 0; i < n; i++)
    {
      printf("%d\n", output[i]);
    };
}
  

int main()
{
  Graph graph = createGraph();
  addVertex(graph, 3, "Dinh Anh Dung");
  addVertex(graph, 4, "Nguyen Tan Dung");
  addVertex(graph, 1, "Nguyen Hoang Thi");
  addVertex(graph, 2, "Tran Dinh Cu");
  addVertex(graph, 5, "Hoang Van Thai");

  printf("done\n");
  addEdge(graph, 2, 3);
  addEdge(graph, 3, 4);
  addEdge(graph, 1, 5);
  addEdge(graph, 4, 2);
  addEdge(graph, 3, 1);
  addEdge(graph, 1, 2);
  addEdge(graph, 1, 4);
  printf("done2\n");
  
  int *output = (int *)malloc(sizeof(int) * 100);
  int count = indegree(graph, 1, output);
  printf("indeg of 1\n");
  printOutput(output, count);
  output = (int *)malloc(sizeof(int) * 100);
  count = outdegree(graph, 1, output);
  printf("out deg of 1\n");
  printOutput(output, count);


  int i = DAG(graph);
  if(i == 1)
    printf("DAG\n");
  else
    printf("Not DAG\n");


  return 0;
}
  
