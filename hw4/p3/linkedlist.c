/** Alan Cham
  * MPCS 51100
  * November 31, 2016
  * Homework 4 p3 */

#include "linkedlist.h"
#include <stdlib.h>
  
Linkedlist* ll_create(void) {
    Linkedlist* ll = malloc(sizeof(Linkedlist));
    ll->head = NULL;
    ll->numnodes = 0;
    return ll;
}

void ll_shallowdestroy(Linkedlist* ll) {
    Node* curr, *next;

    if (ll == NULL) {
        return;
    }
    ll->numnodes = 0;
    curr = ll->head;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    ll->head = NULL;
}

void ll_deepdestroy(Linkedlist* ll) {
    Node* curr, *next;

    if (ll == NULL) {
        return;
    }
    curr = ll->head;
    while (curr != NULL) {
        next = curr->next;
        free(curr->key);
        free(curr->value);
        free(curr);
        curr = next;
    }
    free(ll);
}

Node* ll_find(Linkedlist* ll, void* key, int (*cmp)(void*, void*)) {
    Node* curr;
    int result;

    if (ll == NULL || ll->head == NULL) {
        return NULL;
    }
    result = cmp(key, ll->head->key);
    if (result < 0) {
        return NULL;
    } else if (result == 0) {
        return ll->head;
    }
    curr = ll->head->next;
    while (curr != NULL) {
        result = cmp(key, curr->key);
        if (result == 0) {
            return curr;
        } else if (result < 0) {
            return NULL;
        }
        curr = curr->next;
    }
    return NULL;
}

Node* ll_remove(Linkedlist* ll, void* key, int (*cmp)(void*, void*)) {
    Node* prev, *curr;
    int result;

    if (ll == NULL || ll->head == NULL) {
        return NULL;
    }
    result = cmp(key, ll->head->key);
    if (result < 0) {
        return NULL;
    } else if (result == 0) {
        curr = ll->head;
        ll->head = curr->next;
        ll->numnodes--;
        return curr;
    }
    prev = ll->head;
    curr = ll->head->next;
    while (curr != NULL) {
        result = cmp(key, curr->key);
        if (result == 0) {
            prev->next = curr->next;
            ll->numnodes--;
            return curr;
        } else if (result < 0) {
            return NULL;
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}

int ll_insert(Linkedlist* ll, void* key, void* value, int (*cmp)(void*, void*)) {
    Node* prev, *curr, *tmp;
    int result, prevresult;

    if (ll == NULL) {
        return 1;
    } else if (ll->head == NULL) {
        ll->head = malloc(sizeof(Node));
        ll->head->key = key;
        ll->head->value = value;
        ll->head->next = NULL;
        ll->numnodes = 1;
        return 0;
    }
    if (cmp == NULL) {
        tmp = malloc(sizeof(Node));
        tmp->key = key;
        tmp->value = value;
        tmp->next = ll->head;
        ll->head = tmp;
        ll->numnodes++;
        return 0;
    }
    result = cmp(key, ll->head->key);
    if (result < 0) {
        tmp = malloc(sizeof(Node));
        tmp->key = key;
        tmp->value = value;
        tmp->next = ll->head;
        ll->head = tmp;
        ll->numnodes++;
        return 0;
    } else if (result == 0) {
        return 1;
    }
    prevresult = result;
    prev = ll->head;
    curr = ll->head->next;
    while (curr != NULL) {
        result = cmp(key, curr->key);
        if (result == 0) {
            return 1;
        } else if (result < 0 && prevresult > 0) {
            tmp = malloc(sizeof(Node));
            prev->next = tmp;
            tmp->next = curr;
            tmp->key = key;
            tmp->value = value;
            ll->numnodes++;
            return 0;
        }
        prevresult = result;
        prev = curr;
        curr = curr->next;
    }
    tmp = malloc(sizeof(Node));
    tmp->next = prev->next;
    prev->next = tmp;
    tmp->key = key;
    tmp->value = value;
    ll->numnodes++;    
    return 0;
}
