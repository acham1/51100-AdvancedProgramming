/** Alan Cham
  * MPCS 51100
  * November 14, 2016
  * Homework 3, p1 */

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "linkedlist.h"

#define DEFAULT_LOAD_FACTOR_THRESHOLD 0.7

typedef struct {
    void* key;
    void* value;
} Element;

typedef struct {
    Linkedlist** buckets;
    unsigned numkeys;
    unsigned numbuckets;
    unsigned maxoccupancy;
    unsigned minoccupancy;
    unsigned numminoccupancy;
    unsigned nummaxoccupancy;
    double loadfactorthresh;
    unsigned (*hashfn)(void*);
} Hashmap;

Hashmap* hmp_create(void);
int hmp_resize(unsigned);
int hmp_insert(Hashmap* hmp, void* key, void* value);
Element hmp_find(Hashmap* hmp, void* key);
Element hmp_remove(Hashmap* hmp, void* key);
void hmp_deepdestroy(Hashmap* hmp);
void hmp_traverse(Hashmap* hmp, int (*cmp)(void* key1, void* key2), void (*dosomething)(void*, void*));
#endif