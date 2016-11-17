/** Alan Cham
  * MPCS 51100
  * November 13, 2016
  * Homework 3, p1 */

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
Node* ll_find(Linkedlist* ll, void* key, int (*cmp)(void*, void*));
Node* ll_remove(Linkedlist* ll, void* key, int (*cmp)(void*, void*));
int ll_insert(Linkedlist* ll, void* key, void* value, int (*cmp)(void*, void*));
#endif