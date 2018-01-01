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
        if(node2 == NULL) return 0;
        else return 1;
}

int adjacentUndir(Graph graph, int v1, int v2)
{
        if(adjacent(graph, v1, v2) == 1 && adjacent(graph, v1, v2) == 1) return 1;
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



void dropGraph(Graph graph)
{
        jrb_free_tree(graph);
}



void enqueue(Dllist dllist, int node)
{
        dll_prepend(dllist, new_jval_i(node));
}

int dequeue(Dllist dllist)
{
        Dllist node = dll_last(dllist);
        int v = jval_i(node->val);
        dll_delete_node(node);
        return v;
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

void freeArray(int *array, int n)
{
        for(int i = 0; i< n; i++)
        {
                array[i] = 0;
        };
}


void BFS(Graph graph, int start, void (*function)(int))
{
        int *visit = (int *)malloc(sizeof(int) * 100);
        int i;
        int *output = (int *)malloc(sizeof(int) * 100);
        for(i = 0; i < 100; i++)
        {
                visit[i] = 0;
        };
        int n = 100;
        Dllist traversal = new_dllist();
        enqueue(traversal, start);

        while(!jrb_empty(traversal))
        {
                int current = dequeue(traversal);
                if(!visit[current])
                {
                        function(current);
                        visit[current] = 1;
                        freeArray(output, n);
                        int numberOfAdjacentVertices = getAdjacentVertices(graph, current,output);
                        for(i = 0; i < numberOfAdjacentVertices; i++)
                        {
                                if(!visit[output[i]])
                                {
                                        enqueue(traversal, output[i]);
                                };
                        }
                }
        }
}




void DFS(Graph graph, int start, void (*function)(int))
{
        int *visit = (int *)malloc(sizeof(int) * 100);
        int *output = (int *)malloc(sizeof(int ) * 100);
        int i;
        int n = 100;
        for(i = 0; i< n; i++)
        {
                visit[i] = 0;
        };
        Dllist traversal = new_dllist();
        push(traversal, start);

        while(!dll_empty(traversal))
        {
                int current = pop(traversal);
                if( !visit[current])
                {
                        function(current);
                        visit[current] = 1;
                        freeArray(output, n);
                        int numberOfAdjacentVertices = getAdjacentVertices(graph, current, output);
                        for(i = 0; i< numberOfAdjacentVertices; i++)
                        {
                                if(!visit[output[i]])
                                {
                                        push(traversal, output[i]);
                                };
                        };
                };
        };
}

// void DFS(Graph graph, int start, void (*function)(int)){
//         int *visit = (int *)malloc(sizeof(int)*100);
//         int *output = (int *)malloc(sizeof(int)*100);
//         int i;
//         int n = 100;
//         for(i = 0; i < n; i ++) visit[i] = 0;

//         Dllist traversal = new_dllist();
// }