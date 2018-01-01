#include <stdio.h>
#include <stdlib.h>
#include <libgraph/graph.h>
#include <libfdr/dllist.h>
#include <libfdr/jrb.h>
#include <libfdr/jval.h>


/* void enqueue(Dllist dllist, int node) */
/* { */
/*   dll_append(dllist, new_jval_i(node)); */
/* } */

/* int dequeue(Dllist dllist) */
/* { */
/*   Dllist node = dll_last(dllist); */
/*   int v = jval_i(node->val); */
/*   dll_delete_node(node); */
/*   return v; */
/* } */


/* void push(Dllist dllist, int node) */
/* { */
/*   dll_append(dllist, new_jval_i(node)); */
/* } */


/* int pop(Dllist dllist) */
/* { */
/*   Dllist node = dll_first(dllist); */
/*   int v = jval_i(node->val); */
/*   dll_delete_node(node); */
/*   return v; */
/* } */

/* void freeArray(int *array, int n) */
/* { */
/*   for(int i = 0; i< n; i++) */
/*     { */
/*       array[i] = 0; */
/*     }; */
/* } */


/* void BFS(Graph graph, int start, void (*function)(int)) */
/* { */
/*   int *visit = (int *)malloc(sizeof(int) * 100); */
/*   int i; */
/*   int *output = (int *)malloc(sizeof(int) * 100); */
/*   for(i = 0; i < 100; i++) */
/*     { */
/*       visit[i] = 0; */
/*     }; */

/*   Dllist traversal = new_dllist(); */
/*   enqueue(traversal, start); */

/*   while(!jrb_empty(traversal)) */
/*     { */
/*       int current = dequeue(traversal); */
/*       if(!visit[current]) */
/* 	{ */
/* 	  function(current); */
/* 	  visit[current] = 1; */
/* 	  JRB node; */
/* 	  freeArray(output, 100); */
/* 	  int numberOfAdjacentVertices = getAdjacentVertices(graph, current,output); */
/* 	  for(i = 0; i < numberOfAdjacentVertices; i++) */
/* 	    { */
/* 		  if(!visit[output[i]]) */
/* 		    { */
/* 		      enqueue(traversal, output[i]); */
/* 		    }; */
/* 	    } */
/* 	} */
/*     } */
/* } */


void print(int a)
{
  printf("%d\n", a);
}


/* void DFS(Graph graph, int start, void (*function)(int)) */
/* { */
/*   int *visit = (int *)malloc(sizeof(int) * 100); */
/*   int *output = (int *)malloc(sizeof(int ) * 100); */
/*   int i; */
/*   int n = 100; */
/*   for(i = 0; i< n; i++) */
/*     { */
/*       visit[i] = 0; */
/*     }; */
/*   Dllist traversal = new_dllist(); */
/*   push(traversal, start); */

/*   while(!dll_empty(traversal)) */
/*     { */
/*       int current = pop(traversal); */
/*       if( !visit[current]) */
/* 	{ */
/* 	  function(current); */
/* 	  visit[current] = 1; */
/* 	  freeArray(output, n); */
/* 	  int numberOfAdjacentVertices = getAdjacentVertices(graph, current, output); */
/* 	  for(i = 0; i< numberOfAdjacentVertices; i++) */
/* 	    { */
/* 	      if(!visit[output[i]]) */
/* 		{ */
/* 		  push(traversal, output[i]); */
/* 		}; */
/* 	    }; */
/* 	}; */
/*     }; */
/* } */
	      

  


int main()
{
  Graph g = createGraph();
  addEdge(g, 0, 1);
  addEdge(g, 0, 2);
  addEdge(g, 1, 2);
  addEdge(g, 1, 3);
  BFS(g, 0, &print);
  printf("DFS\n");
  DFS(g, 0, &print);
  return 0;
}
  
