/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * HW4 P5 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "linkedlist.h"

#define MARKOV_TOKENS "[\n"
#define NUM_EDGE_ARGS 3
#define MAX_LINE_WIDTH 10000
#define DEFAULT_NUM_VERTICES 1
#define GRAPH_CAPACITY_GROWTH_FACTOR 2

#define graph_max(a, b) ((a) > (b) ? (a) : (b))

typedef struct Graph {
    long numverts; // vertices capacity
    long occupancy;// actual number of vertices 
    Linkedlist** adjlists; // array of adjacency lists
} Graph;

typedef struct MatGraph {
    long numverts; // number of vertices in graph
    char** adjmat; // adjacency matrix; value 1 if edge exists, 0 otherwise
    long** weightmat; // weight matrix
} MatGraph;

// create empty graph with memory allocated for defaults sizes
Graph* creategraph(void);

// read directed, weighted graph from FILE* f, in following format
// ignores any line starting with #
// vertices given as integer values
// each edge on separate line, like such: <fromV> <toV> <weight>
// return negative value for numV if error
Graph* dw_readgraph(FILE* f);

// read markov graph from file
// return negative value for numV if error
Graph* markov_readgraph(FILE* f);

// expand the number of vertices in the graph to newsz
void resizegraph(Graph* g, long newsz);

void destroygraph(Graph* g);

void destroymatgraph(MatGraph* mg);

// read an edge into the memory at from, to and weight
// return 1 if fail, 0 otherwise
int dw_readedge(FILE* f, long* from, long* to, long* weight);

// return pointer to MatGraph, given pointer to adjacency list form
// NULL if fail
MatGraph* adjtomat(Graph* g);

#endif