/** Alan Cham
  * MPCS 51100
  * HW4 P1 */

#include "graph.h"

// create empty graph with memory allocated for defaults sizes
Graph creategraph(void) {
    Graph g;

    g.occ = 0;
    g.cap = DEFAULT_GRAPH_CAPACITY;
    g.adj = calloc(g.cap, sizeof(long*));
    g.weight = calloc(g.cap, sizeof(long*));
    g.adjcap = calloc(g.cap, sizeof(long));
    g.adjocc = calloc(g.cap, sizeof(long));
    for (int i = 0; i < g.cap; i++) {
        g.adjcap[i] = DEFAULT_ADJ_ARRAY_CAPACITY;
        g.adj[i] = calloc(g.adjcap[i], sizeof(long));
        g.weight[i] = calloc(g.adjcap[i], sizeof(long));
    }
    return g;
}

// read directed, weighted graph from FILE* f, in following format
// ignores any line starting with #
// vertices given as integer values
// each edge on separate line, like such: <fromV> <toV> <weight>
// return negative value for numV if error
Graph dw_readgraph(FILE* f) {
    long from, to, weight;
    Graph g;

    g = creategraph(); 
    while (!feof(f) && !readedge)
}

void destroygraph(Graph g) {
    long** adj;    // adjacency arrays
    long** weight; // edge weights
    long* adjcap;  // adjacency array capacity
    long* adjocc;  // adjacency array occupancy

    for (int i = 0; i < g.cap; i++) {
        free(weight[i]);
        free(adj[i]);
    }
    free(adj);
    free(adjcap);
    free(adjocc);
    free(weight);
}

#endif