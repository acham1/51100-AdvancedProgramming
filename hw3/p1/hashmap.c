/** Alan Cham
  * MPCS 51100
  * November 14, 2016
  * Homework 3, p1 */

#include <stdlib.h>
#include "linkedlist.h"
#include "hashmap.h"

Hashmap* hmp_create(void) {
    Hashmap* hmp = malloc(sizeof(Hashmap));
    hmp->loadfactorthresh = DEFAULT_LOAD_FACTOR_THRESHOLD;
    hmp->buckets = malloc(sizeof(Linkedlist*));
    hmp->buckets[0] = ll_create();
    hmp->numkeys = 0;
    hmp->numbuckets = 1;
    hmp->maxoccupancy = 0;
    hmp->minoccupancy = 0;
    hmp->numminoccupancy = 1;
    hmp->nummaxoccupancy = 1;
    return hmp;
}

int hmp_resize(Hashmap* hmp, unsigned size) {
    Hashmap* newhmp = malloc(sizeof(Hashmap));

    if (size < hmp->numbuckets) {
        printf("special error: invalid resize input\n");
        return 1;
    }
    newhmp = malloc(sizeof(Hashmap));
    newhmp->hashfn = hmp->hashfn;
    newhmp->numkeys = hmp->numkeys;

    hmp_shallowdestroy(hmp);
    *hmp = newhmp;
    return 0;
}

int hmp_insert(Hashmap* hmp, void* key, void* value) {
    return 1;
}

Element hmp_find(Hashmap* hmp, void* key) {
    Element elmnt;
    elmnt.key = NULL;
    elmnt.value = NULL;
    return elmnt;
}

Element hmp_remove(Hashmap* hmp, void* key) {
    Element elmnt;
    elmnt.key = NULL;
    elmnt.value = NULL;
    return elmnt;
}

void hmp_deepdestroy(Hashmap* hmp) {

}

void hmp_shallowdestroy(Hashmpa* hmp) {

}

void hmp_traverse(Hashmap* hmp, int (*cmp)(void* key1, void* key2), void (*dosomething)(void*, void*)) {

}
