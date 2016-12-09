/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * HW4 P5 */

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "bfs.h"

#define EXPECTED_ARGC 2
#define GRAPH_FILE_INDEX 1
#define HARD_CODE_LIMIT 8
#define myabs(a) ((a) > 0 ? (a) : -(a))

long getgcd(long a, long b);
int printheading(FILE** f, int argc, char* argv[]);

int main(int argc, char* argv[]) {
    long gcd, i, j, k;
    BFSresults* b;
    Graph* g;
    Node* n;
    FILE* f;

    if (printheading(&f, argc, argv)) {
        printf(">>  End of test. Please retry with correct input.\n");
        return EXIT_FAILURE;
    }
    printf(">>  Creating markov graph from markov graph file.\n");
    g = markov_readgraph(f);
    b = bfs(g, 1); // dfs from first vertex
    gcd = 0;
    for (long x = 1; x < g->occupancy; x++) {
        n = g->adjlists[x]->head;
        while (n != NULL) {
            i = x;
            j = *(long*)n->key;
            k = b->length[i] - b->length[j] + 1;
            if (k > 0 && b->parent[j] != i) {
                gcd = getgcd(gcd, myabs(k));
            }
            if (gcd == 1) {
                break;
            }
            n = n->next;
        }
        if (gcd == 1) {
            break;
        }
    }
    printf(">>  Period of markov graph is: %ld\n", gcd);
    printf(">>  i.e. %s\n", (gcd == 1) ? "graph is Aperiodic" : "graph is Periodic");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>  Destroying graph.\n");
    destroy_BFSresults(b);
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

long getgcd(long a, long b) {
    long oddA, oddB;

    oddA = a % 2;
    oddB = b % 2;
    if (a == 0) {
        return b;
    } else if (b == 0) {
        return a;
    } else if (!oddA && !oddB) {
        return 2*getgcd(a/2, b/2);
    } else if (oddA && !oddB) {
        return getgcd(a, b/2);
    } else if (!oddA && oddB) {
        return getgcd(a/2, b);
    } else if (a >= b) {
        return getgcd((a-b)/2, b);
    } else {
        return getgcd((b-a)/2, a);
    }
}