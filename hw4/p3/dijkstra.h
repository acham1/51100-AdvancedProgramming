/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * HW4 P3 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "heap.h"
#include <limits.h>
#include <omp.h>

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

// returns pointer to allocated SingleSourceDistances using Graph g
// and source s; returns NULL if fail
SingleSourceDistances* dijkstra_omp(Graph* g, long s, int numthreads);

#endif