/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * HW4 P4 */

#include "bfs.h"

BFSresults* create_BFSresults(Graph* g) {
    BFSresults* b;

    b = malloc(sizeof(BFSresults));
//    b->color = calloc(g->occupancy, sizeof(char));
    b->visited = calloc(g->occupancy, sizeof(char));
    b->parent = calloc(g->occupancy, sizeof(long));
    b->length = calloc(g->occupancy, sizeof(long));
    return b;
}

BFSresults* bfs(Graph* g, long s) {
    long* stack, read, write, x;
    BFSresults* b;
    Node* n;

    stack = malloc(sizeof(long) * g->occupancy);
    read = write = 0;
    b = create_BFSresults(g);
//    b->color[s] = 0;
    b->length[s] = 0;
    b->parent[s] = -1;
    b->visited[s] = 1;
    stack[write++] = s;
    while (read < write) {
        n = g->adjlists[stack[read]]->head;
        while (n != NULL) {
            x = *(long*)n->key;
            if (!b->visited[x]) {
//                b->color[x] = !b->color[stack[read]];
                b->visited[x] = 1;
                b->length[x] = b->length[stack[read]] + 1;
                b->parent[x] = stack[read];
                stack[write++] = x;
            }
            n = n->next;
        }
        read++;
    }
    free(stack);
    return b;
}

void destroy_BFSresults(BFSresults* b) {
    free(b->length);
    free(b->parent);
    free(b->visited);
    free(b);
}
