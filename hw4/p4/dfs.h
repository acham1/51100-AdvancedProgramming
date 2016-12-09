/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * HW4 P4 */

#ifndef DFS_H
#define DFS_H

#include "graph.h"

typedef struct DFSresults {
    long* parent;
    char* visited; 
    long* length;
} DFSresults;

DFSresults* create_DFSresults(Graph* g);

DFSresults* dfs(Graph* g, long s);

DFSresults* dfsvisit(Graph* g, long s, DFSresults* d);

void destroy_DFSresults(DFSresults* d); 

#endif