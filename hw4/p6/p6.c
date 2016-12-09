/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * HW4 P6 */

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "scc.h"

#define EXPECTED_ARGC 2
#define GRAPH_FILE_INDEX 1
#define HARD_CODE_LIMIT 8
#define myabs(a) ((a) > 0 ? (a) : -(a))

int printheading(FILE** f, int argc, char* argv[]);

int main(int argc, char* argv[]) {
    char irreducible;
    Graph* g;
    FILE* f;

    if (printheading(&f, argc, argv)) {
        printf(">>  End of test. Please retry with correct input.\n");
        return EXIT_FAILURE;
    }
    printf(">>  Creating markov graph from markov graph file.\n");
    g = markov_readgraph(f);
    irreducible = isirreducible(g);
    if (irreducible) {
        printf(">>  Exactly one strongly connected component detected.\n");
        printf(">>  Result: graph is Irreducible\n");
    } else {
        printf(">>  More than one strongly connected component detected.\n");
        printf(">>  Result: graph is Reducible\n");
    }
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>  Destroying graph.\n");
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
    printf(">>  HW4 p5 Driver\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    if (argc < EXPECTED_ARGC) {
        printf(">>  Error: please enter markov graph file path as command-line argument.\n");
        return 1;
    } else if ((*f = fopen(argv[GRAPH_FILE_INDEX], "r")) == NULL) {
        printf(">>  Error: failed to find markov graph file at location %s\n", argv[GRAPH_FILE_INDEX]);
        return 1;
    } else {
        printf(">>  Success: opening markov graph file at %s.\n", argv[GRAPH_FILE_INDEX]);
    }
    return 0;
}