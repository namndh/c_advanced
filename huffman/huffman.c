#include <stdio.h>
#include <stdlib.h>
#include <libfdr/dllist.h>
#include <libfdr/jrb.h>
#include <libgraph/graph.h>
#define NONE_STRING ""


typedef struct HuffmanTree{
  Graph graph;
  JRB root;
} HuffmanTree;


typedef struct Coding {
  int size;r21
  char bits[2];
} Coding;

HuffmanTree makeTree()
{
  HuffmanTree huffmanTree;
  huffmanTree.graph = createGraph();
  root = make_jrb();
  return huffmanTree;
}


