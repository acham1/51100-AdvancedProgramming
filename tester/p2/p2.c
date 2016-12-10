/** Alan Cham
  * MPCS 51100
  * HW4 P2 */

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "dijkstra.h"
#include <omp.h>

#define EXPECTED_ARGC 2
#define GRAPH_FILE_INDEX 1

int printheading(FILE** f, int argc, char* argv[]);

int main(int argc, char* argv[]) {
    SingleSourceDistances* ssd;
    double start, end;
    Graph* g;
    FILE* f;

    if (printheading(&f, argc, argv)) {
        printf(">>  End of test. Please retry with correct input.\n");
        return EXIT_FAILURE;
    }
    printf(">>  Creating graph from graph file.\n");
    g = dw_readgraph(f);
    for (int numthreads = 1; numthreads <= omp_get_max_threads(); numthreads *= 2) {
        printf(">>  %2d threads. Computing all-pairs, parallelized outside Dijkstra. ", numthreads);
        fflush(stdout);
        start = omp_get_wtime();
#pragma omp parallel for shared(g), private(ssd), schedule(dynamic), num_threads(numthreads)
        for (long i = 0; i < g->occupancy; i++) {
            ssd = dijkstra(g, i);
            free(ssd->dist);
            free(ssd->reach);
            free(ssd);
        }
        end = omp_get_wtime();
        printf("(Results %5.2lf s)\n", end-start);
    }
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>  Destroying graph.\n");
    free(f);
    destroygraph(g);
    printf(">>  End of test.\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    return EXIT_SUCCESS;
}

// validate input and return 1 if error, 0 otherwise
int printheading(FILE** f, int argc, char* argv[]) {
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>  Alan Cham\n");
    printf(">>  MPCS 51100\n");
    printf(">>  HW4 p2 Driver\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    if (argc < EXPECTED_ARGC) {
        printf(">>  Error: please enter graph file path as command-line argument.\n");
        return 1;
    } else if ((*f = fopen(argv[GRAPH_FILE_INDEX], "r")) == NULL) {
        printf(">>  Error: failed to find graph file at location %s\n", argv[GRAPH_FILE_INDEX]);
        return 1;
    } else {
        printf(">>  Success: opening file at %s.\n", argv[GRAPH_FILE_INDEX]);
    }
    return 0;
}
