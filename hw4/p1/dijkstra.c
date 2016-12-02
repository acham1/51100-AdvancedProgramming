/** Alan Cham
  * MPCS 51100
  * HW4 P1 */

#include "dijkstra.h"

// returns pointer to allocated SingleSourceDistances using Graph g
// and source s; returns NULL if fail
SingleSourceDistances* dijkstra(Graph* g, long s) {
    SingleSourceDistances* d;

    d = malloc(sizeof(SingleSourceDistances));
    d->source = s;
    d->n = g->occupancy;
    d->dist = malloc(sizeof(long) * d->n);
    d->reach = malloc(sizeof(char) * d->n);
    for (long i = 0; i < d->n; i++) {
        d->dist[i] = LONG_MAX;
        d->reach[i] = 0;
    }

    // minheap priority queue
    return NULL;
}