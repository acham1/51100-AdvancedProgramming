/** Alan Cham
  * MPCS 51100
  * HW4 P1 */

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

#define EXPECTED_ARGC 2
#define GRAPH_FILE_INDEX 1

int printheading(FILE** f, int argc, char* argv[]);

int main(int argc, char* argv[]) {
    long numE = 0;
    Graph* g;
    FILE* f;
    Node* n;

    if (printheading(&f, argc, argv)) {
        printf(">>  End of test. Please retry with correct input.\n");
        printf("********************************************************************************\n");
        return EXIT_FAILURE;
    }
    printf(">>  Creating graph from graph file.\n");
    g = dw_readgraph(f);

    printf(">>  Printing graph edges\n");
    for (long i = 0; i < g->occupancy; i++) {
        numE += g->adjlists[i]->numnodes;
        n = g->adjlists[i]->head;
        printf("vertex %ld has %ld outdegree\n", i, g->adjlists[i]->numnodes);
        while (n != NULL) {
            printf("%ld %ld %ld\n", i, *(long*) n->key, *(long*) n->value);
            n = n->next;
        }
    }

    printf(">>  Destroying graph.\n");
    printf(">>  Found %ld edges total\n", numE);
    destroygraph(g);    
    return EXIT_SUCCESS;
}

// validate input and return 1 if error, 0 otherwise
int printheading(FILE** f, int argc, char* argv[]) {
    printf("********************************************************************************\n");
    printf(">>  Alan Cham\n");
    printf(">>  MPCS 51100\n");
    printf(">>  HW4 p1 Driver\n");
    printf("********************************************************************************\n");
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