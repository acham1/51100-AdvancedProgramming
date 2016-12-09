/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * HW4 P4 */

#ifndef BFS_H
#define BFS_H

#include "graph.h"

typedef struct BFSresults {
    long* parent;
    char* visited; 
    long* length;
//    char* color;
} BFSresults;

BFSresults* create_BFSresults(Graph* g);

BFSresults* bfs(Graph* g, long s);

void destroy_BFSresults(BFSresults* b); 

#endif