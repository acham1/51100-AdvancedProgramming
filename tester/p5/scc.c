/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * HW4 P5 */

#include "scc.h"

// verify that the whole graph is one strongly connected component
char isirreducible(Graph* g) {
    DFSresults* d1, * d2;
    Graph* t;

    d1 = dfs(g, 1);
    if (d1->numtree < g->occupancy-1) {
        destroy_DFSresults(d1);
        return 0;
    }
    destroy_DFSresults(d1);
    t = transposegraph(g);
    d2 = dfs(t, 1);
    if (d2->numtree < g->occupancy-1) {
        destroy_DFSresults(d2);
        destroygraph(t);
        return 0;
    }
    destroy_DFSresults(d2);
    destroygraph(t);
    return 1;
}
