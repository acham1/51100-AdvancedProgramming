/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * HW4 P3 */

#include "dijkstra.h"

// return 1 if key1 < key2
static int cmp(void* key1, void* key2) {
    Dvertex* a, * b;

    a = key1;
    b = key2;
    if (!a->reachable) {
        return 0;
    } else if (!b->reachable) {
        return 1;
    } else {
        return a->distance < b->distance;
    }
    return 1;
}

// returns pointer to allocated SingleSourceDistances using Graph g
// and source s; returns NULL if fail
SingleSourceDistances* dijkstra(Graph* g, long s) {
    SingleSourceDistances* d;
    long i, to, edgew, distto;
    Dvertex* vert, * tmp;
    Minheap* mh;
    Node* n;

    if (s >= g->occupancy) {
        return NULL;
    }
    d = malloc(sizeof(SingleSourceDistances));
    d->source = s;
    d->n = g->occupancy;
    d->dist = malloc(sizeof(long) * d->n);
    d->reach = malloc(sizeof(char) * d->n);
    for (long i = 0; i < d->n; i++) {
        d->dist[i] = LONG_MAX;
        d->reach[i] = 0;
    }
    mh = mh_create(cmp);
    for (long i = 0; i < d->n; i++) {
        vert = malloc(sizeof(Dvertex));
        vert->vertnum = i;
        vert->distance = LONG_MAX;
        vert->reachable = 0;
        mh_add(mh, vert);
    }
    vert = mh->values[s];
    vert->vertnum = s;
    vert->distance = 0;
    vert->reachable = 1;
    mh_decreasekey(mh, s, mh->values[s]);
    vert = mh_extractmin(mh);
    while (vert != NULL && vert->reachable) {
        i = vert->vertnum;
//        printf("Extracted vertex %ld with distance (%ld)\n", i, vert->distance);
        d->dist[i] = vert->distance;
        d->reach[i] = 1;
        n = g->adjlists[i]->head;
        while (n != NULL) {
            to = *(long*)(n->key);
            if (d->reach[to]) {
                n = n->next;
                continue;
            }
            edgew = *(long*)(n->value);
            tmp = mh->values[mh->heapindex[to]];
            distto = tmp->distance;
            if (!tmp->reachable || distto > d->dist[i] + edgew) {
                tmp->reachable = 1;
                tmp->distance = d->dist[i] + edgew;
                mh_decreasekey(mh, tmp->vertnum, tmp);
//                printf("Updating %ld to distance %ld\n", ((Dvertex*)(mh->values[mh->heapindex[to]]))->vertnum, ((Dvertex*)(mh->values[mh->heapindex[to]]))->distance);
            }
            n = n->next;
        }
        free(vert);
        vert = mh_extractmin(mh);
    }
    mh_deepdestroy(mh);
    return d;
}

// returns pointer to allocated SingleSourceDistances using Graph g
// and source s; returns NULL if fail
SingleSourceDistances* dijkstra_omp(MatGraph* mg, long s, int numthreads) {
    SingleSourceDistances* d;
    char* visited;
    long min, tmp;

    if (s >= mg->numverts) {
        return NULL;
    }
    d = malloc(sizeof(SingleSourceDistances));
    d->source = s;
    d->n = mg->numverts;
    d->dist = malloc(sizeof(long) * d->n);
    d->reach = malloc(sizeof(char) * d->n);
    visited = malloc(sizeof(char) * d->n);
#pragma omp parallel for num_threads(numthreads)
    for (long i = 0; i < d->n; i++) {
        d->dist[i] = LONG_MAX;
        d->reach[i] = 0;
        visited[i] = 0;
    }
    d->dist[s] = 0;
    d->reach[s] = 1;
    tmp = 0;
    min = s;
    while (tmp != LONG_MAX) {
        visited[min] = 1;
//        printf("Extract %ld with weight %ld\n", min, d->dist[min]);
#pragma omp parallel for num_threads(numthreads)
        for (long i = 0; i < d->n; i++) {
            if (mg->adjmat[min][i] && !visited[i] && d->dist[i] > d->dist[min] + mg->weightmat[min][i]) {
                d->dist[i] = d->dist[min] + mg->weightmat[min][i];
                d->reach[i] = 1;
            }
        }
        tmp = LONG_MAX;
#pragma omp parallel for num_threads(numthreads)
        for (long i = 0; i < d->n; i++) {
#pragma omp critical (deckey)
            if (!visited[i] && d->dist[i] < tmp) {
                tmp = d->dist[i];                
                min = i;
            }
        }
    }
    free(visited);
    return d;
}