/** Alan Cham
  * MPCS 51100
  * November 17, 2016
  * Homework 3, p2 */

#include <string.h>
#include "unique.h"
#include <stdio.h>

static int (*globalequals)(void*, void*);
static int (*prehash)(const void* key);

int uniq(void *f, int n, int sz, int (*equals)(void *, void *), int (*h)(const void *key)) {
    Hashmap* hmp = hmp_create();
    int numuniques = 0;
    char* fc = f;
    char* tmparray = malloc(sz * n);

    prehash = h;
    hmp->hashfn = hashfn;
    globalequals = equals;
    for (int i=0; i < n; i++) {
        if (!hmp_insert(hmp, fc + i*sz, NULL, u_cmp)) {
            memcpy(tmparray + numuniques*sz, fc + i*sz, sz);
            numuniques++;
        }
    }
    for (int j=0; j < numuniques; j++) {
        memcpy(fc + j*sz, tmparray + j*sz, sz);
    }
    hmp_shallowdestroy(hmp);
    free(tmparray);
    free(hmp);
    return numuniques;
}

// I have to use this wrapper because my buckets are sorted
// and might not search through the whole bucket otherwise
int u_cmp(void* obj1, void* obj2) {
    if (globalequals(obj1, obj2)) {
        return 0;
    } else {
        return 1;
    }
}

// I have to use this wrapper to ensure that the final hash
// is within the right range
long hashfn(Hashmap* hmp, void* obj) {
    long k = prehash(obj);
    return unique_abs(k % hmp->numbuckets);
}