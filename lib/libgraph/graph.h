#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <libfdr/jrb.h>
#include <libfdr/dllist.h>
#include <libfdr/jval.h>
#define INFINITIVE_VALUE 9999999999.0
#define MAX_MEM 1000



typedef struct Graph
{
  JRB vertices;
  JRB edges;
}Graph;


Graph createGraph();

void addVertex(Graph graph, int id, char *name);

char *getVertex(Graph graph, int id);

void addEdge(Graph graph, int v1, int v2, double weight);

double getEdgeValue(Graph graph, int v1, int v2);//return INFINITIVE_VALUE if no edge between v1 and v2

int hasEdge(Graph graph, int v1, int v2);

int indegree(Graph graph, int v, int *output);

int outdegree(Graph graph, int v, int *output);

void DFS(Graph graph, int v, void (* function)(int));

void BFS(Graph graph, int v, void (* function)(int));

int DAG(Graph graph);

void dropGraph(Graph graph);

double shortestPath(Graph graph, int s, int t, Dllist path);

Dllist topologicalOrder(Graph graph);



//private
void modifyQueue(Dllist queue, int v, double *d);

double choosePath(int s, int t, Dllist path, double *d, int *parent);

/* void enQueueP(Dllist dllist, int v, double *d); */

int compareNodeVertex(Dllist dllistNode, int vertex, double *d);

int compareNode(Dllist dllist1, Dllist dllist2, double *d);

int relax(Graph graph, int current, int next, double *d, int *parent);

/* void enQueue(Dllist queue, int node); */

/* int deQueue(Dllist dllist); */

/* void push(Dllist dllist, int node); */

/* int pop(Dllist dllist); */


#endif
