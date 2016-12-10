/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * Homework 4 p2 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
    void* key;
    void* value;
    struct Node* next;
} Node;

typedef struct Linkedlist {
    Node* head;
    unsigned long numnodes;
} Linkedlist;

Linkedlist* ll_create(void);
void ll_shallowdestroy(Linkedlist* ll);
void ll_deepdestroy(Linkedlist* ll);
// return pointer to node if found, NULL otherwise
Node* ll_find(Linkedlist* ll, void* key, int (*cmp)(void*, void*));
// return pointer to node if removed, NULL otherwise
Node* ll_remove(Linkedlist* ll, void* key, int (*cmp)(void*, void*));
// return 1 if problem, 0 if success
int ll_insert(Linkedlist* ll, void* key, void* value, int (*cmp)(void*, void*));
#endif