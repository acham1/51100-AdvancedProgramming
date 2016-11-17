/** Alan Cham
  * MPCS 51100
  * November 14, 2016
  * Homework 3, p1 */

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "linkedlist.h"

#define DEFAULT_LOAD_FACTOR_THRESHOLD 0.7
#define HMP_GROWTH_FACTOR 2
#define hmp_max(a, b) ((a) > (b) ? (a) : (b))
  
typedef struct {
    void* key;
    void* value;
} Element;

typedef struct Hashmap {
    Linkedlist** buckets;
    long numkeys;
    long numbuckets;
    long maxoccupancy;
    long minoccupancy;
    long numminoccupancy;
    long nummaxoccupancy;
    double loadfactorthresh;
    long (*hashfn)(struct Hashmap*, void*);
} Hashmap;

Hashmap* hmp_create(void);
int hmp_resize(Hashmap* hmp, long size, int (*cmp)(void*, void*));
int hmp_insert(Hashmap* hmp, void* key, void* value, int (*cmp)(void*, void*));
Element hmp_find(Hashmap* hmp, void* key, int (*cmp)(void*, void*));
Element hmp_remove(Hashmap* hmp, void* key, int (*cmp)(void*, void*));
void hmp_deepdestroy(Hashmap* hmp);
void hmp_shallowdestroy(Hashmap* hmp);
void hmp_traverse(Hashmap* hmp, int (*cmp)(void* key1, void* key2), void (*dosomething)(void*, void*));
#endif