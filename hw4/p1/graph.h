/** Alan Cham
  * MPCS 51100
  * HW4 P1 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NUM_EDGE_ARGS 3
#define MAX_LINE_WIDTH 200
#define ADJ_GROWTH_FACTOR 2
#define ADJ_ARRAY_GROWTH_FACTOR 2
#define DEFAULT_GRAPH_CAPACITY 1
#define DEFAULT_ADJ_ARRAY_CAPACITY 1

#define graph_max(a, b) ((a) > (b) ? (a) : (b))

typedef struct SingleSourceDistances {
    long source;   // source vertex
    long n;        // total vertices
    long* dist;    // distance array
    char* reach;   // reachability array
} SingleSourceDistances;

typedef struct AllPairDistances {
    long n;        // total vertices
    long** dist;   // distances matrix
    char** reach;  // reachability matrix
} AllPairDistances;

typedef struct Graph {
    long cap;      // vertices capacity
    long occ;      // occupancy; i.e. number of vertices
    long** adj;    // adjacency arrays
    long** weight; // edge weights
    long* adjcap;  // adjacency array capacity
    long* adjocc;  // adjacency array occupancy
} Graph;

// create empty graph with memory allocated for defaults sizes
Graph* creategraph(void);

// read directed, weighted graph from FILE* f, in following format
// ignores any line starting with #
// vertices given as integer values
// each edge on separate line, like such: <fromV> <toV> <weight>
// return negative value for numV if error
Graph* dw_readgraph(FILE* f);

// expand the number of vertices in the graph to newsz
void resizegraph(Graph* g, long newsz);

void destroygraph(Graph* g);

// read an edge into the memory at from, to and weight
// return 1 if fail, 0 otherwise
int dw_readedge(FILE* f, long* from, long* to, long* weight);

#endif