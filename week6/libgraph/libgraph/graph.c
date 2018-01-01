#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



Graph createGraph(){
  Graph graph = make_jrb();
  return graph;
}


void addEdge(Graph graph, int v1, int v2)
{
  JRB treeV1 = jrb_find_int(graph, v1);
  JRB treeV2 = jrb_find_int(graph, v2);
  if(treeV1 == NULL) jrb_insert_int(graph, v1,new_jval_v( make_jrb()));
  if(treeV2 == NULL) jrb_insert_int(graph, v2, new_jval_v(make_jrb()));
  treeV1 = jrb_find_int(graph, v1);
  JRB node = (JRB)jval_v(treeV1->val);
  jrb_insert_int(node, v2, new_jval_i(1));
}

void addEdgeUndir(Graph graph, int v1, int v2)
{
  addEdge(graph, v1, v2);
  addEdge(graph, v2, v1);
}

int adjacent(Graph graph, int v1, int v2)
{
  JRB treeV1 = jrb_find_int(graph, v1);
  JRB treeV2 = jrb_find_int(graph, v2);
  if(treeV1 == NULL || treeV2 == NULL) return 0;
  JRB node1 = (JRB)jval_v(treeV1->val);
  JRB node2 = jrb_find_int(node1, v2);
  if(node2 == NULL)return 0;
  else return 1;
}

int adjacentUndir(Graph graph, int v1, int v2)
{
  if(adjacent(graph, v1, v2) == 1 && adjacent(graph, v1, v2) == 1)return 1;
  else return 0;
}


int getAdjacentVertices(Graph graph, int v, int *output)
{
  JRB treeV = jrb_find_int(graph, v);
  if(treeV == NULL) return 0;
  JRB node = (JRB)jval_v(treeV->val);
  int count = 0;
  JRB ptr;
  jrb_traverse(ptr, node){
    output[count] = jval_i(ptr->key);
    count++;
  }
  return count;
}
  
