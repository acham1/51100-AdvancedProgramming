/** Alan Cham
  * MPCS 51100
  * HW4 P1 */

#include "graph.h"

// create empty graph with memory allocated for defaults sizes
Graph* creategraph(void) {
    Graph* g = malloc(sizeof(Graph));

    g->occ = 0;
    g->cap = DEFAULT_GRAPH_CAPACITY;
    g->adj = calloc(g->cap, sizeof(long*));
    g->weight = calloc(g->cap, sizeof(long*));
    g->adjcap = calloc(g->cap, sizeof(long));
    g->adjocc = calloc(g->cap, sizeof(long));
    for (int i = 0; i < g->cap; i++) {
        g->adjocc[i] = 0;
        g->adjcap[i] = DEFAULT_ADJ_ARRAY_CAPACITY;
        g->adj[i] = calloc(g->adjcap[i], sizeof(long));
        g->weight[i] = calloc(g->adjcap[i], sizeof(long));
    }
    return g;
}

// read directed, weighted graph from FILE* f, in following format
// ignores any line starting with #
// vertices given as integer values
// each edge on separate line, like such: <fromV> <toV> <weight>
// return negative value for numV if error
Graph* dw_readgraph(FILE* f) {
    long from, to, weight, index;
    Graph* g;

    g = creategraph(); 
    while (!feof(f)) {
        if (!dw_readedge(f, &from, &to, &weight)) {
            printf("adding edge: %ld %ld %ld\n", from, to, weight);
            while (from+1 > g->cap || to+1 > g->cap) {
                printf("resizing graph capacity to %ld\n", g->cap * ADJ_GROWTH_FACTOR);
                resizegraph(g, g->cap * ADJ_GROWTH_FACTOR);
            }
            g->occ = graph_max(graph_max(g->occ, from+1), to+1);
            while (g->adjocc[from] >= g->adjcap[from]) {
                long* tmp;
                printf("resizing adjacency array capacity (%ld, %ld, %ld)\n", from, g->adjocc[from], g->adjcap[from]);
                tmp = realloc(g->adj[from], g->adjcap[from] * sizeof(long) * ADJ_ARRAY_GROWTH_FACTOR);
                g->adj[from] = tmp;
                g->adjcap[from] *= ADJ_ARRAY_GROWTH_FACTOR;
                printf("end\n");
            }
            index = g->adjocc[from]++;
            g->adj[from][index] = to;
            g->weight[from][index] = weight;
            printf("added edge: %ld %ld %ld\n", from, to, weight);
        }
    }
    return g;
}

// expand the number of vertices in the graph to newsz
void resizegraph(Graph* g, long newsz) {
    if (newsz <= g->cap) {
        printf("Invalid resize request\n");
        return;
    }
    g->adj = realloc(g->adj, newsz * sizeof(long*));
    g->weight = realloc(g->weight, newsz * sizeof(long*));                
    g->adjcap = realloc(g->adjcap, newsz * sizeof(long));
    g->adjocc = realloc(g->adjocc, newsz * sizeof(long));
    for (int i = g->cap; i < newsz; i++) {
        g->adjocc[i] = 0;
        g->adjcap[i] = DEFAULT_ADJ_ARRAY_CAPACITY;
        g->adj[i] = calloc(g->adjcap[i], sizeof(long));
        g->weight[i] = calloc(g->adjcap[i], sizeof(long));
    }
    g->cap = newsz;
}

void destroygraph(Graph* g) {
    for (int i = 0; i < g->cap; i++) {
//        free(g.weight[i]);
//        free(g.adj[i]);
    }
//    free(g.adj);
//    free(g.adjcap);
//    free(g.adjocc);
//    free(g.weight);
}

// read an edge into the memory at from, to and weight
// return 1 if fail, 0 otherwise
int dw_readedge(FILE* f, long* from, long* to, long* weight) {
    char s[MAX_LINE_WIDTH+1];

//    printf("dw_readedge\n");
    if (fgets(s, MAX_LINE_WIDTH+1, f) == NULL) {
        return 1;
    } else if (sscanf(s, " %ld %ld %ld ", from, to, weight) < NUM_EDGE_ARGS) {
        return 1;
    }
    return 0;
}