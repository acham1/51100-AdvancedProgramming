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
    int numnodes;
} Linkedlist;

Linkedlist* ll_create(void);

#endif