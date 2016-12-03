/** Alan Cham
  * MPCS 51100
  * HW4 P1 */

#include "heap.h"
#include <stdio.h>

static void mh_heapify(Minheap* mh, long pos) {
    char lvalid, rvalid;
    long child, ltmp;
    void* vtmp;

    lvalid = (pos*2 + 1 < mh->occupancy);
    rvalid = (pos*2 + 2 < mh->occupancy);
    if (lvalid && rvalid) {
        child = mh->cmp(mh->values[pos*2+1], mh->values[pos*2+2]) ? pos*2 + 1 : pos*2 + 2;
    } else if (lvalid) {
        child = pos*2 + 1;
    } else {
        return;
    }
    if (mh->cmp(mh->values[child], mh->values[pos])) {
        vtmp = mh->values[child];
        mh->values[child] = mh->values[pos];
        mh->values[pos] = vtmp;
        ltmp = mh->heap[pos];
        mh->heap[pos] = mh->heap[child];
        mh->heap[child] = ltmp;
        mh->heapindex[mh->heap[pos]] = pos;
        mh->heapindex[mh->heap[child]] = child;
        mh_heapify(mh, child);
    }
}

// heap is not expandable, input total num elements at creation
Minheap* mh_create(int (*cmp)(void* k1, void* k2)) {
    Minheap* mh = malloc(sizeof(Minheap));
    mh->occupancy = 0;
    mh->capacity = DEFAULT_MIN_HEAP_CAP;
    mh->values = malloc(sizeof(void*) * DEFAULT_MIN_HEAP_CAP+1);
    mh->heapindex = malloc(sizeof(long) * DEFAULT_MIN_HEAP_CAP+1);
    mh->heap = malloc(sizeof(long) * DEFAULT_MIN_HEAP_CAP+1);
    mh->cmp = cmp;
    return mh;
}

// return 1 if error; otherwise 0
int mh_add(Minheap* mh, void* newval) {
    long pos, parent, tmp;
    void* tmpval;

    while (mh->occupancy >= mh->capacity) {
        mh->capacity *= MIN_HEAP_CAP_GROWTH_FACTOR;
        mh->heapindex = realloc(mh->heapindex, sizeof(long) * (mh->capacity+1));
        mh->heap = realloc(mh->heap, sizeof(long) * (mh->capacity+1));
        mh->values = realloc(mh->values, sizeof(void*) * (mh->capacity+1));
    }
    pos = mh->occupancy++;
    mh->heapindex[pos] = pos;
    mh->heap[pos] = pos;
    mh->values[pos] = newval;
    parent = (pos-1)/2;
    while (pos > 0 && mh->cmp(mh->values[pos], mh->values[parent])) {
        mh->heapindex[mh->heap[pos]] = parent;
        mh->heapindex[mh->heap[parent]] = pos;
        tmp = mh->heap[pos];
        mh->heap[pos] = mh->heap[parent];
        mh->heap[parent] = tmp;
        tmpval = mh->values[pos];
        mh->values[pos] = mh->values[parent];
        mh->values[parent] = tmpval;
        pos = parent;
        parent = (pos-1)/2;
    }
    return 0;
}

// return NULL if error, pointer to replaced 
void* mh_decreasekey(Minheap* mh, long id, void* newval) {
    void* original, * tmpval;
    long pos, parent, tmp;

    if (id >= mh->occupancy || mh->heapindex[id] == -1) {
        return NULL;
    }
    pos = mh->heapindex[id];
    original = mh->values[pos];
    mh->values[pos] = newval;
    parent = (pos-1)/2;
    if (pos > 0 && mh->cmp(mh->values[pos], mh->values[parent])) {
        while (pos > 0 && mh->cmp(mh->values[pos], mh->values[parent])) {
            mh->heapindex[mh->heap[pos]] = parent;
            mh->heapindex[mh->heap[parent]] = pos;
            tmp = mh->heap[pos];
            mh->heap[pos] = mh->heap[parent];
            mh->heap[parent] = tmp;
            tmpval = mh->values[pos];
            mh->values[pos] = mh->values[parent];
            mh->values[parent] = tmpval;
            pos = parent;
            parent = (pos-1)/2;
        }
    } else {
        mh_heapify(mh, pos);
    }
    return original;
}

void* mh_extractmin(Minheap* mh) {
    long pos, last;
    void* themin;

    pos = --(mh->occupancy);
    themin = mh->values[0];
    mh->values[0] = NULL;
    mh->heapindex[mh->heap[0]] = -1;
    if (pos > 0) {
        last = mh->heap[pos];
        mh->heap[0] = last;
        mh->heapindex[last] = 0;
        mh->values[0] = mh->values[pos];
        mh->values[pos] = NULL;
        mh_heapify(mh, 0);
    }
    return themin;
}

void mh_deepdestroy(Minheap* mh) {
    for (long i = 0; i < mh->occupancy; i++) {
        free(mh->values[i]);
    }
    free(mh->heapindex);
    free(mh->values);
    free(mh->heap);
    free(mh);
}