/** Alan Cham
  * MPCS 51100
  * HW4 P1 */

#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <limits.h>
#include <stdlib.h>

#define DEFAULT_MIN_HEAP_CAP 1
#define MIN_HEAP_CAP_GROWTH_FACTOR 2

// a heap type for integer (long) keys
typedef struct Minheap {
    long occupancy;
    long capacity;
    long* heapindex;
    long* heap;
    void** values;
    int (*cmp)(void* k1, void* k2); // pointer to fn that returns 1 if k1 < k2
} Minheap;

// heap is not expandable, input total num elements at creation
Minheap* mh_create(int (*cmp)(void* k1, void* k2));

// return 1 if error; otherwise 0
int mh_add(Minheap* mh, void* newval);

// return NULL if error, pointer to replaced 
void* mh_decreasekey(Minheap* mh, long id, void* newval);

void* mh_extractmin(Minheap* mh);

void mh_deepdestroy(Minheap* mh);

#endif