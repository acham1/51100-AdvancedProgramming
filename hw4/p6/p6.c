/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * HW4 P6 */

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include <time.h>

#define NUM_SAMPLES 1000000
#define EXPECTED_ARGC 2
#define GRAPH_FILE_INDEX 1
#define HARD_CODE_LIMIT 8
#define myabs(a) ((a) > 0 ? (a) : -(a))

int printheading(FILE** f, int argc, char* argv[]);

int main(int argc, char* argv[]) {
    long* tally, state, nextstate;
    double r, cumulated;
    Graph* g;
    Node* n;
    FILE* f;

    if (printheading(&f, argc, argv)) {
        printf(">>  End of test. Please retry with correct input.\n");
        return EXIT_FAILURE;
    }
    printf(">>  Creating markov graph from markov graph file.\n");
    g = markov_readgraph(f);
    printf(">>  Sampling %.0E times via Markov\n", (double) NUM_SAMPLES);
    tally = calloc(g->occupancy, sizeof(long));
    state = 1;
    srand(time(NULL));
    for (long i = 0; i < NUM_SAMPLES; i++) {
        tally[state]++;
        n = g->adjlists[state]->head;
        cumulated = 0;
        r = (double) rand() / RAND_MAX;
        while (cumulated < r && n != NULL) {
            nextstate = *(long*)n->key;
            cumulated += *(double*)n->value;
            n = n->next;
        }
        state = nextstate;
    }
    for (long i = 1; i < g->occupancy; i++) {
        printf("State %2ld: stationary probability %5.3lf%%\n", i, (double)tally[i]/NUM_SAMPLES*100);
    }
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>  Destroying graph.\n");
    destroygraph(g);
    free(tally);
    printf(">>  End of test.\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    return EXIT_SUCCESS;
}

// validate input and return 1 if error, 0 otherwise
int printheading(FILE** f, int argc, char* argv[]) {
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>  Alan Cham\n");
    printf(">>  MPCS 51100\n");
    printf(">>  HW4 p6 Driver\n");
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