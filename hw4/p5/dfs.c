/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * HW4 P5 */

#include "dfs.h"

DFSresults* create_DFSresults(Graph* g) {
    DFSresults* d;

    d = malloc(sizeof(DFSresults));
    d->visited = calloc(g->occupancy, sizeof(char));
    d->parent = calloc(g->occupancy, sizeof(long));
    d->length = calloc(g->occupancy, sizeof(long));
    return d;
}

DFSresults* dfs(Graph* g, long s) {
    DFSresults* d;

    d = create_DFSresults(g);
    d->length[s] = 0;
    d->parent[s] = -1;
    dfsvisit(g, s, d);
    return d;
}

DFSresults* dfsvisit(Graph* g, long s, DFSresults* d) {
    long neighbor;
    Node* n;

    d->visited[s] = 1;
    n = g->adjlists[s]->head;
    while (n != NULL) {
        neighbor = *(long*) n->key;
        if (!d->visited[neighbor]) {
            d->parent[neighbor] = s;
            d->length[neighbor] = d->length[s] + 1;
            dfsvisit(g, neighbor, d);
        }
        n = n->next;
    }
    return d;
}

void destroy_DFSresults(DFSresults* d) {
    free(d->length);
    free(d->parent);
    free(d->visited);
    free(d);
}
