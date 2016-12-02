/** Alan Cham
  * MPCS 51100
  * HW4 P1 */

#include "heap.h"

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
        tmp = mh->heapindex[pos];
        mh->heapindex[pos] = mh->heapindex[parent];
        mh->heapindex[parent] = tmp;
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

void* mh_extractmin(Minheap* mh) {
    long pos, last, leftchild, rightchild, tmp2;
    void* themin, * tmp;
    char heapify;

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
        pos = 0;
        heapify = 1;
        while (heapify) {
            leftchild = pos*2 + 1;
            rightchild = pos*2 + 2;
            if (leftchild < mh->occupancy && mh->cmp(mh->values[leftchild], mh->values[pos])) {
                tmp = mh->values[leftchild];
                mh->values[leftchild] = mh->values[pos];
                mh->values[pos] = tmp;
                tmp2 = mh->heap[pos];
                mh->heap[pos] = mh->heap[leftchild];
                mh->heap[leftchild] = tmp2;
                mh->heapindex[mh->heap[pos]] = pos;
                mh->heapindex[mh->heap[leftchild]] = leftchild;
                pos = leftchild;
            } else if (rightchild < mh->occupancy && mh->cmp(mh->values[rightchild], mh->values[pos])) {
                tmp = mh->values[rightchild];
                mh->values[rightchild] = mh->values[pos];
                mh->values[pos] = tmp;
                tmp2 = mh->heap[pos];
                mh->heap[pos] = mh->heap[rightchild];
                mh->heap[rightchild] = tmp2;
                mh->heapindex[mh->heap[pos]] = pos;
                mh->heapindex[mh->heap[rightchild]] = rightchild;
                pos = rightchild;
            } else {
                heapify = 0;
            }
        }
    }
    return themin;
}

void mh_deepdestroy(Minheap* mh) {
    for (long i = 0; i < mh->occupancy; i++) {
        free(mh->values[i]);
    }
    free(mh->heapindex);
    free(mh->heap);
    free(mh);
}