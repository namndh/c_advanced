#include <stdio.h>
#include <stdlib.h>
#include <libfdr/jrb.h>
#include <libfdr/jval.h>
#include <libfdr/dllist.h>
#include "graph.h"


Graph createGraph()
{
  Graph graph;
  graph.vertices = make_jrb();
  graph.edges = make_jrb();
  return graph;
}


void addVertex(Graph graph, int id, char *name)
{
  JRB node = jrb_find_int(graph.vertices, id);
  if(node != NULL)
    {
      node->val = new_jval_s(name);
      return;
    }
  jrb_insert_int(graph.vertices, id, new_jval_s(name));
  jrb_insert_int(graph.edges, id, new_jval_v(make_jrb()));
  return;
}

int hasVertex(Graph graph, int v)
{
  JRB node = jrb_find_int(graph.vertices, v);
  if(node == NULL)return 0;
  else return 1;
}

char *getVertex(Graph graph, int id)
{
  JRB node = jrb_find_int(graph.vertices, id);
  if(node == NULL)
    return NULL;
  return jval_s(node->val);
}


void addEdge(Graph graph, int v1, int v2, double weight)
{
  //printf("%d - %d\n", v1, v2);
  JRB vertex1 = jrb_find_int(graph.vertices, v1);
  if(vertex1 == NULL)return;
  
  JRB vertex2 = jrb_find_int(graph.vertices, v2);
  if(vertex2 == NULL)return;
  
  vertex1 = jrb_find_int(graph.edges, v1);
  
  JRB node1 = (JRB) jval_v(vertex1->val);
  
  vertex2 = jrb_find_int(node1, v2);
  if(vertex2 != NULL)
    return;
  
  jrb_insert_int(node1, v2, new_jval_d(weight));
}

void addEdgeUndir(Graph graph, int v1, int v2, double weight)
{
  addEdge(graph, v1, v2, weight);
  addEdge(graph, v2, v1, weight);
}



int hasEdge(Graph graph, int v1, int v2)
{
  JRB vertex1 = jrb_find_int(graph.vertices, v1);
  if(vertex1 == NULL)return 0;
  
  JRB vertex2 = jrb_find_int(graph.vertices, v2);
  if(vertex2 == NULL)return 0;
  
  vertex1 = jrb_find_int(graph.edges, v1);
  
  JRB node1 = (JRB)jval_v(vertex1->val);
  vertex2 = jrb_find_int(node1, v2);
  
  if(vertex2 == NULL)return 0;
  return 1;
}


int indegree(Graph graph, int v, int *output)
{
  JRB node = jrb_find_int(graph.edges, v);
  if(node == NULL)return 0;
  
  JRB ptr;
  JRB inPtr;
  int count = 0;
  int n;


  jrb_traverse(ptr, graph.edges)
    {
      if(jval_i(ptr->key) == v)continue;
      node = (JRB) jval_v(ptr->val);
      jrb_traverse(inPtr, node)
	{
	  n = jval_i(inPtr->key);
	  if(n == v)
	    {
	      output[count] = jval_i(ptr->key);
	      count++;
	      break;
	    };
	};
    };
  return count;
}

int outdegree(Graph graph, int v, int *output)
{
  JRB node = jrb_find_int(graph.edges, v);
  if(node == NULL)return 0;
  
  JRB ptr;
  int count = 0;
  int n;
  
  node = (JRB)jval_v(node->val);
  
  jrb_traverse(ptr, node)
    {
      n = jval_i(ptr->key);
      output[count] = n;
      count++;
    }
  return count;
}

void push(Dllist dllist, int node)
{
  dll_prepend(dllist, new_jval_i(node));
}

int pop(Dllist dllist)
{
  Dllist node = dll_first(dllist);
  int v = jval_i(node->val);
  dll_delete_node(node);
  return v;
}

void enQueue(Dllist dllist, int node)
{
  dll_append(dllist, new_jval_i(node));
}

int deQueue(Dllist dllist)
{
  Dllist first_list = dll_first(dllist);
  int node = jval_i(first_list->val);
  dll_delete_node(first_list);
  return node;
}

int DAG(Graph graph)
{
  int *visit = (int *)malloc(sizeof(int) * 100);
  Dllist stack;
  int start;
  JRB ptr;

  int i;
  for(i = 0; i< 100; i++)
    {
      visit[i] = 0;
    };

  
  jrb_traverse(ptr, graph.edges)
    {
      start = jval_i(ptr->key);
      stack = new_dllist();
      
      if(visit[start] == 1)continue;
      push(stack, start);

      while(!dll_empty(stack))
	{
	  int popNode = pop(stack);
	  visit[popNode] = 1;
	  
	  int *output = (int *)malloc(sizeof(int) * 1000);
	  int count;
	  count = outdegree(graph, popNode, output);
	  for(i = 0; i < count; i++)
	    {
	      if(visit[output[i]] == 1)return 1;
	      push(stack, output[i]);
	    };
	}
    }
  return 0;
}


void DFS(Graph graph, int v, void (*function)(int))
{
  int *visit = (int *)malloc(sizeof(int) * 100);
  int *output = (int *)malloc(sizeof(int)* 100);
  int i;
  for(i = 0; i < 100 ;i ++)
    {
      visit[i] = 0;
    }
  
  Dllist stack = new_dllist();
  push(stack, v);
  while(!dll_empty(stack))
    {
      int popNode = pop(stack);
      if(visit[popNode] == 0){
	function(popNode);
	visit[popNode] = 1;
	int count = outdegree(graph, popNode, output);
	for(i = 0; i < count; i++)
	  {
	    if (visit[output[i]] != 1)
	      {
		push(stack, output[i]);
	      }
	  };
      };
    };
}


/* void topologicalOrder(Graph graph, int v) */
/* { */
double getEdgeValue(Graph graph, int v1, int v2)
{
  if(!hasVertex(graph, v1) || !hasVertex(graph, v2))
    return INFINITIVE_VALUE;
  JRB node = jrb_find_int(graph.edges, v1);
  JRB treeV1 = (JRB)jval_v(node->val);
  JRB node2 = jrb_find_int(treeV1, v2);
  if(node2 == NULL)return INFINITIVE_VALUE;
  else
    {
      return jval_d(node2->val);
    };
}


int relax(Graph graph, int current, int next,  double *d, int *parent)
{
  double distance_dir = getEdgeValue(graph, current, next);
  if( d[next] > (d[current] + distance_dir))
    {
      d[next] = d[current] + distance_dir;
      parent[next] = current;
      return 1;
    };
  return 0;
}


int compareNode(Dllist dllist1, Dllist dllist2, double *d)
{
  int d1 = d[jval_i(dllist1->val)];
  int d2 = d[jval_i(dllist2->val)];
  if(d1 > d2)return 1;
  else if(d2 > d1) return -1;
  else return 0;
}

int compareNodeVertex(Dllist dllistNode, int vertex, double *d)
{
  int d1 = d[jval_i(dllistNode->val)];
  int d2 = d[vertex];

  if(d1 > d2)return 1;
  else if(d1 < d2) return -1;
  else return 0;
}


void enQueueP(Dllist dllist, int v, double *d)
{
  if(dll_empty(dllist))
    {
      dll_append(dllist, new_jval_i(v));
      return;
    };
  Dllist ptr;
  dll_traverse(ptr, dllist)
    {
      int compareValue = compareNodeVertex(ptr, v, d);
      if(compareValue == -1)
	     {
	       dll_insert_b(ptr, new_jval_i(v));
	       return;
	     }
    };
  dll_append(dllist, new_jval_i(v));
}


void modifyQueue(Dllist queue, int v, double *d)
{
  if(dll_empty(queue))return;
  Dllist ptr;
  int found = 0;
  dll_traverse(ptr, queue)
    {
      if(jval_i(ptr->val) == v){
	found = 1;
	break;
      };
    }
  if(found == 0)return;
  dll_delete_node(ptr);
  enQueueP(queue, v, d);
}

double choosePath(int s, int t, Dllist path, double *d, int *parent)
{
  int i;
  dll_prepend(path, new_jval_i(t));
  i = t;
  do
    {
      i = parent[i];
      if(i == -1)break;
      dll_prepend(path, new_jval_i(i));
    }
  while(i != s);
  return d[t];
      
}

  


void dijkstra(Graph graph, int s, double *d, int *parent)
{
  int *output = (int *)malloc(sizeof(int) * 100);
  Dllist queue = new_dllist();

  d[s] = 0;
  JRB ptr;

  jrb_traverse(ptr, graph.vertices)
    {
      int ptrVertex = jval_i(ptr->key);
      d[ptrVertex] = getEdgeValue(graph, s, ptrVertex);
      parent[ptrVertex] = -1;
    };

  jrb_traverse(ptr, graph.vertices)
    {
      int ptrVertex = jval_i(ptr->key);
      enQueueP(queue, ptrVertex, d);
    };

  while(!dll_empty(queue))
    {
      int popNode = deQueue(queue);

      int n = outdegree(graph, popNode, output);
      int i;
      for(i = 0; i< n; i++)
	{
	  if(relax(graph, popNode, output[i], d, parent))
	    modifyQueue(queue, output[i], d);
	};
    };

}

      
double shortestPath(Graph graph, int s, int t, Dllist path, double *length)
{
  double *d = (double *)malloc(sizeof(double) * MAX_MEM);
  int *parent = (int *)malloc(sizeof(int) * MAX_MEM);
  /* int *output = (int *)malloc(sizeof(int) * MAX_MEM); */
  /* int i; */
  /* int count = 0; */
  /* JRB node; */


  /* Dllist queue = new_dllist(); */
  /* d[s] = 0; */
  /* jrb_traverse(node, graph.vertices) */
  /*   { */
  /*     int node_key = jval_i(node->key); */
  /*     if (node_key == s)continue; */
  /*     d[node_key] = getEdgeValue(graph, s, node_key); */
  /*     //  printf("val : %f\n", d[node_key]); */
  /*     parent[node_key] = -1; */
  /*     enQueueP(queue, node_key, d); */
  /*   }; */

  /* while(!dll_empty(queue)x) */
  /*   { */
  /*     int popNode = deQueue(queue); */
  /*     int n = outdegree(graph, popNode, output); */
  /*     for ( i  = 0; i< n ; i++) */
  /* 	{ */
  /* 	  if(relax(graph, popNode, output[i], d, parent) == 1) */
  /* 	    modifyQueue(queue, output[i], d); */
  /* 	}; */
  /*   }; */
  dijkstra(graph, s, d, parent);
  return (*length = choosePath(s, t, path, d, parent));
}

Dllist topologicalOrder(Graph graph)
{
  int *degrees = (int *)malloc(sizeof(int) * 100);
  if(!DAG(graph))return NULL;
  Dllist queue = new_dllist();
  int *output = (int *)malloc(sizeof(int) * 100);
  Dllist topo = new_dllist();
  JRB node;

  jrb_traverse(node, graph.vertices){
    int node_key = jval_i(node->val);
    degrees[node_key] = indegree(graph, node_key, output);
    if(degrees[node_key] == 0){
      enQueue(queue, node_key);
    }
  };

  while(!dll_empty(queue)){
    int popNode = deQueue(queue);
    enQueue(topo, popNode);
    output = (int *)malloc(sizeof(int) * 100);
    int n = outdegree(graph, popNode, output);
    int i;
    for(i = 0; i< n; i++)
    {
      degrees[output[i]] -= 1;
      if(degrees[output[i]] == 0)enQueue(queue, output[i]);
    }

  }
  return topo;
}
  
  




