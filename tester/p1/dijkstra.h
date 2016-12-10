/** Alan Cham
  * MPCS 51100
  * HW4 P1 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "heap.h"
#include <limits.h>

typedef struct SingleSourceDistances {
    long source;   // source vertex
    long n;        // total vertices
    long* dist;    // distance array
    char* reach;   // reachability array
} SingleSourceDistances;

typedef struct Dvertex {
    long vertnum;
    long distance;
    char reachable;
} Dvertex;

// returns pointer to allocated SingleSourceDistances using Graph g
// and source s; returns NULL if fail
SingleSourceDistances* dijkstra(Graph* g, long s);

#endif