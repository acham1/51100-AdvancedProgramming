/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * HW4 P3 */

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "dijkstra.h"
#include <omp.h>

#define EXPECTED_ARGC 2
#define GRAPH_FILE_INDEX 1
#define HARD_CODE_LIMIT 8

int printheading(FILE** f, int argc, char* argv[]);

int main(int argc, char* argv[]) {
    SingleSourceDistances* ssd;
    double start, end;
    MatGraph* mg;
    Graph* g;
    FILE* f;

    if (printheading(&f, argc, argv)) {
        printf(">>  End of test. Please retry with correct input.\n");
        return EXIT_FAILURE;
    }
    printf(">>  Creating graph from graph file.\n");
    g = dw_readgraph(f);
    mg = adjtomat(g);
//    for (int numthreads = omp_get_max_threads(); numthreads >= 1; numthreads /= 2) {
    for (int numthreads = 1; numthreads <= HARD_CODE_LIMIT; numthreads *= 2) {
        printf(">>  %2d threads. Computing all-pairs, parallelized within Dijsktra. ", numthreads);
        fflush(stdout);
        start = omp_get_wtime();
//        for (long i = 0; i <= 10; i++) {
        for (long i = 0; i < g->occupancy; i++) {
            ssd = dijkstra_omp(mg, i, numthreads);
            free(ssd->dist);
            free(ssd->reach);
            free(ssd);
        }
        end = omp_get_wtime();
        printf("(Results %5.2lf s)\n", end-start);
    }
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>  Destroying graph.\n");
    fclose(f);
    destroygraph(g);
    destroymatgraph(mg);
    printf(">>  End of test.\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    return EXIT_SUCCESS;
}

// validate input and return 1 if error, 0 otherwise
int printheading(FILE** f, int argc, char* argv[]) {
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>  Alan Cham\n");
    printf(">>  MPCS 51100\n");
    printf(">>  HW4 p3 Driver\n\n");
    printf(">> *The following results are obtained by parallelizing 'within' each\n"
        "    single-source computation\n");
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
