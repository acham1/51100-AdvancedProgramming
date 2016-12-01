/** Alan Cham
  * MPCS 51100
  * HW4 P1 */

#include "graph.h"

// create empty graph with memory allocated for defaults sizes
Graph creategraph(void) {
    Graph g;

//    printf("creategraph\n");
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
    long from, to, weight, adjocc;
    long* newadjarr;
    Graph g;

//    printf("dw_readgraph\n");
    g = creategraph(); 
    while (!feof(f)) {
//        printf("trying to read edge\n");
        if (!dw_readedge(f, &from, &to, &weight)) {
            printf("adding edge: %ld %ld %ld\n", from, to, weight);
            while (from > g.cap-1 || to > g.cap-1) {
                printf("resizing graph capacity to %ld\n", g.cap * ADJ_GROWTH_FACTOR);
                resizegraph(&g, g.cap * ADJ_GROWTH_FACTOR);
            }
            g.occ = graph_max(g.occ, from+1);
            g.occ = graph_max(g.occ, to+1);
            while (g.adjocc[from] >= g.adjcap[from]) {
                printf("resizing adjacency array capacity (%ld, %ld, %ld)\n", from, g.adjocc[from], g.adjcap[from]);
                newadjarr = calloc(g.adjcap[from] * ADJ_ARRAY_GROWTH_FACTOR, sizeof(long));
                printf("1\n");
                memcpy(newadjarr, g.adj[from], sizeof(long) * g.adjocc[from]);
                printf("2\n");
                printf("Printing out contents of adj[from]\n");
                for (int i = 0; i < g.adjocc[from]; i++) {
                    printf("%d has %ld\n", i, g.adj[from][i]);
                    printf("%d has %ld\n", i, newadjarr[i]);
                }
                free(g.adj[from]);
                printf("3\n");
                g.adj[from] = newadjarr;
                printf("4\n");
                g.adjcap[from] *= ADJ_ARRAY_GROWTH_FACTOR;
            }
            adjocc = g.adjocc[from]++;
            g.adj[from][adjocc] = to;
            g.weight[from][adjocc] = weight;
        }
    }
    return g;
}

// expand the number of vertices in the graph to newsz
void resizegraph(Graph* g, long newsz) {
    long* newadjcap, * newadjocc;
    long** newadj, ** newweight;

//    printf("resizegraph\n");
    newadj = calloc(newsz, sizeof(long*));
    newweight = calloc(newsz, sizeof(long*));
    newadjcap = calloc(newsz, sizeof(long));
    newadjocc = calloc(newsz, sizeof(long));
    memcpy(newadj, g->adj, sizeof(long*) * g->cap);
    memcpy(newweight, g->weight, sizeof(long*) * g->cap);
    memcpy(newadjcap, g->adjcap, sizeof(long) * g->cap);
    memcpy(newadjocc, g->adjocc, sizeof(long) * g->cap);
    free(g->adj);
    free(g->weight);
    free(g->adjocc);
    free(g->adjcap);
    g->adj = newadj;
    g->weight = newweight;                
    g->adjcap = newadjcap;
    g->adjocc = newadjocc;
    g->cap *= ADJ_GROWTH_FACTOR;
    for (int i = 0; i < g->cap; i++) {
        if (g->adj[i] == NULL) {
//            printf("filling out NULL\n");
            g->adjcap[i] = DEFAULT_ADJ_ARRAY_CAPACITY;
            g->adj[i] = calloc(g->adjcap[i], sizeof(long));
            g->weight[i] = calloc(g->adjcap[i], sizeof(long));
        }
    }
}

void destroygraph(Graph g) {
    printf("destroygraph\n");
    for (int i = 0; i < g.cap; i++) {
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