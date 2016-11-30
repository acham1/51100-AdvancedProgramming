/** Alan Cham
  * MPCS 51100
  * HW4 P1 */

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

#define EXPECTED_ARGC 2
#define GRAPH_FILE_INDEX 1

int main(int argc, char* argv[]) {
    FILE* f;

    if (argc < EXPECTED_ARGC) {
        printf("Error: please enter graph file path as command-line argument.\n");
        return EXIT_FAILURE;
    } else if ((f = fopen(argv[GRAPH_FILE_INDEX], "r")) == NULL) {
        printf("Error: failed to find graph file at location %s\n", argv[GRAPH_FILE_INDEX]);
        return EXIT_FAILURE;
    }

    
    return EXIT_SUCCESS;
}