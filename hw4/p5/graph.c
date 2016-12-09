/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * HW4 P4 */

#include "graph.h"

// create empty graph with memory allocated for defaults sizes
Graph* creategraph(void) {
    Graph* g = malloc(sizeof(Graph));
    g->occupancy = 0;
    g->numverts = DEFAULT_NUM_VERTICES;
    g->adjlists = malloc(DEFAULT_NUM_VERTICES * sizeof(Linkedlist*));
    for (long i = 0; i < DEFAULT_NUM_VERTICES; i++) {
        g->adjlists[i] = ll_create();
    }
    return g;
}

// read markov graph from file
// return negative value for numV if error
Graph* markov_readgraph(FILE* f) {
    char s[MAX_LINE_WIDTH+1];
    double* tmpval, weight;
    long from, to, newsz;
    long* tmpkey;
    char* tok;
    Graph* g;

    g = creategraph(); 
    while (!feof(f)) {
        if (!fgets(s, MAX_LINE_WIDTH+1, f) || !sscanf(s, " %ld ", &from)) {
            continue;
        }
        tok = strtok(s, MARKOV_TOKENS);
        while ((tok = strtok(NULL, MARKOV_TOKENS)) != NULL) {
            sscanf(tok, "%ld, %lf", &to, &weight);
            newsz = g->numverts;
            while (newsz < from+1 || newsz < to+1) {
                newsz *= GRAPH_CAPACITY_GROWTH_FACTOR;
            }
            if (newsz > g->numverts) {
                g->adjlists = realloc(g->adjlists, newsz * sizeof(Linkedlist*));
                for (long i = g->numverts; i < newsz; i++) {
                    g->adjlists[i] = ll_create();
                }
                g->numverts = newsz;
            }
            g->occupancy = graph_max(g->occupancy, from+1);
            g->occupancy = graph_max(g->occupancy, to+1);
            tmpkey = malloc(sizeof(long));
            *tmpkey = to;
            tmpval = malloc(sizeof(double));
            *tmpval = weight;
            ll_insert(g->adjlists[from], tmpkey, tmpval, NULL);
        }
    }
    return g;    
}

// read directed, weighted graph from FILE* f, in following format
// ignores any line starting with #
// vertices given as integer values
// each edge on separate line, like such: <fromV> <toV> <weight>
// return negative value for numV if error
Graph* dw_readgraph(FILE* f) {
    long from, to, weight, newsz;
    long* tmpkey, * tmpval;
    Graph* g;

    g = creategraph(); 
    while (!feof(f)) {
        if (!dw_readedge(f, &from, &to, &weight)) {
            newsz = g->numverts;
            while (newsz < from+1 || newsz < to+1) {
                newsz *= GRAPH_CAPACITY_GROWTH_FACTOR;
            }
            if (newsz > g->numverts) {
                g->adjlists = realloc(g->adjlists, newsz * sizeof(Linkedlist*));
                for (long i = g->numverts; i < newsz; i++) {
                    g->adjlists[i] = ll_create();
                }
                g->numverts = newsz;
            }
            g->occupancy = graph_max(g->occupancy, from+1);
            g->occupancy = graph_max(g->occupancy, to+1);
            tmpkey = malloc(sizeof(long));
            *tmpkey = to;
            tmpval = malloc(sizeof(long));
            *tmpval = weight;
            ll_insert(g->adjlists[from], tmpkey, tmpval, NULL);
        }
    }
    return g;
}

void destroygraph(Graph* g) {
    for (long i = 0; i < g->numverts; i++) {
        ll_deepdestroy(g->adjlists[i]);
    }
    free(g->adjlists);
    free(g);
}

// read an edge into the memory at from, to and weight
// return 1 if fail, 0 otherwise
int dw_readedge(FILE* f, long* from, long* to, long* weight) {
    char s[MAX_LINE_WIDTH+1];

    if (fgets(s, MAX_LINE_WIDTH+1, f) == NULL) {
        return 1;
    } else if (sscanf(s, " %ld %ld %ld ", from, to, weight) < NUM_EDGE_ARGS) {
        return 1;
    }
    return 0;
}

// return pointer to MatGraph, given pointer to adjacency list form
// NULL if fail
MatGraph* adjtomat(Graph* g) {
    Linkedlist* ll;
    MatGraph* mg;
    Node* n;

    mg = malloc(sizeof(MatGraph));
    mg->numverts = g->occupancy;
    mg->adjmat = calloc(mg->numverts, sizeof(char*));
    mg->weightmat = calloc(mg->numverts, sizeof(long*));
    for (int i = 0; i < mg->numverts; i++) {
        mg->adjmat[i] = calloc(mg->numverts, sizeof(char));
        mg->weightmat[i] = calloc(mg->numverts, sizeof(long));
        ll = g->adjlists[i];
        n = ll->head;
        while (n != NULL) {
            mg->adjmat[i][*(long*)n->key] = 1;
            mg->weightmat[i][*(long*)n->key] = *(long*)n->value;
            n = n->next;
        }
    }
    return mg;
}

void destroymatgraph(MatGraph* mg) {
    for (int i = 0; i < mg->numverts; i++) {
        free(mg->weightmat[i]);
        free(mg->adjmat[i]);
    }
    free(mg->weightmat);
    free(mg->adjmat);
    free(mg);
}