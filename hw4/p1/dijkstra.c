/** Alan Cham
  * MPCS 51100
  * HW4 P1 */

#include "dijkstra.h"

// returns pointer to allocated SingleSourceDistances using Graph g
// and source s; returns NULL if fail
SingleSourceDistances* dijkstra(Graph* g, long s) {
    SingleSourceDistances* d;
    long i, to, edgew, distto;
    Dvertex* vert, * tmp;
    Minheap* mh;
    Node* n;

    d = malloc(sizeof(SingleSourceDistances));
    d->source = s;
    d->n = g->occupancy;
    d->dist = malloc(sizeof(long) * d->n);
    d->reach = malloc(sizeof(char) * d->n);
    for (long i = 0; i < d->n; i++) {
        d->dist[i] = LONG_MAX;
        d->reach[i] = 0;
    }
    printf("Initialized SSD\n");
    mh = malloc(sizeof(Minheap));
    for (long i = 0; i < d->n; i++) {
        vert = malloc(sizeof(Dvertex));
        vert->vertnum = i;
        vert->distance = LONG_MAX;
        vert->reachable = 0;
        mh_add(mh, vert);
        printf("Added vertex %ld\n", i);
    }
    vert = mh->values[s];
    vert->vertnum = s;
    vert->distance = 0;
    vert->reachable = 1;
    mh_decreasekey(mh, s, mh->values[s]);
    while (vert = mh_extractmin(mh), vert->reachable) {
        i = vert->vertnum;
        printf("Extracted vertex %ld\n", i);
        d->dist[i] = vert->distance;
        d->reach[i] = 1;
        n = g->adjlists[i]->head;
        while (n != NULL) {
            to = *(long*)(n->key);
            edgew = *(long*)(n->value);
            tmp = mh->values[mh->heapindex[to]];
            distto = tmp->distance;
            if (!tmp->reachable || distto > d->dist[i] + edgew) {
                tmp->reachable = 1;
                tmp->distance = d->dist[i] + edgew;
                mh_decreasekey(mh, tmp->vertnum, tmp);
            }
            n = n->next;
        }
    }
    mh_deepdestroy(mh);
    return NULL;
}