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


char *getVertex(Graph graph, int id)
{
  JRB node = jrb_find_int(graph.vertices, id);
  if(node == NULL)
    return NULL;
  return jval_s(node->val);
}


void addEdge(Graph graph, int v1, int v2)
{
  printf("%d - %d\n", v1, v2);
  JRB vertex1 = jrb_find_int(graph.vertices, v1);
  if(vertex1 == NULL)return;
  
  JRB vertex2 = jrb_find_int(graph.vertices, v2);
  if(vertex2 == NULL)return;
  
  vertex1 = jrb_find_int(graph.edges, v1);
  
  JRB node1 = (JRB) jval_v(vertex1->val);
  
  vertex2 = jrb_find_int(node1, v2);
  if(vertex2 != NULL)
    return;
  
  jrb_insert_int(node1, v2, new_jval_i(1));
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
  dll_append(dllist, new_jval_i(node));
}

int pop(Dllist dllist)
{
  Dllist node = dll_first(dllist);
  int v = jval_i(node->val);
  dll_delete_node(node);
  return v;
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
  
  Dllist Stack = new Dllist();
  push(stack, v);
  while(!dll_empty(stack))
    {
      int popNode = pop(stack);
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
}

/* void topologicalOrder(Graph graph, int v) */
/* { */
  

  
  





