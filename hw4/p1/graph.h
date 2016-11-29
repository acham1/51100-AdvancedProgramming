/** Alan Cham
  * MPCS 51100
  * HW4 P1 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#define DEFAULT_GRAPH_CAPACITY 10
#define DEFAULT_ADJ_ARRAY_CAPACITY 10

typedef struct SingleSourceDistances {
    long source;   // source vertex
    long n;        // total vertices
    long* dist;    // distance array
    char* reach;   // reachability array
} SingleSourceDistances;

typedef struct AllPairDistances {
    long n;        // total vertices
    long** dist;   // distances matrix
    char** reach;  // reachability matrix
} AllPairDistances;

typedef struct Graph {
    long cap;      // vertices capacity
    long occ;      // occupancy; i.e. number of vertices
    long** adj;    // adjacency arrays
    long** weight; // edge weights
    long* adjcap;  // adjacency array capacity
    long* adjocc;  // adjacency array occupancy
} Graph;

#endif