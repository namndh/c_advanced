#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <libfdr/jval.h>
#include <libfdr/jrb.h>
#include <libfdr/dllist.h>

typedef JRB Graph;

Graph createGraph();
void addEdge(Graph graph, int v1, int v2);
void addEdgeUndir(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int adjacentUndir(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int v, int *output);
void dropGraph(Graph graph);
void BFS(Graph graph, int start, void (*function)(int));
void DFS(Graph graph, int start, void (*function)(int));


#endif