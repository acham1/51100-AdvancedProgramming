/** Alan Cham
  * MPCS 51100
  * November 17, 2016
  * Homework 3, p2 */

#include <stdlib.h>
#include "linkedlist.h"
#include "hashmap.h"
#include <stdio.h>

static void hmp_swap(Element* e1, Element* e2) {
    void* tmpkey, *tmpval;

//    printf("in swap\n");
    tmpkey = e1->key;
    tmpval = e1->value;
    e1->key = e2->key;
    e1->value = e2->value;
    e2->key = tmpkey;
    e2->value = tmpval;            
//    printf("out swap\n");
}

static void hmp_insertlist(Hashmap* hmp, Linkedlist* ll, int (*cmp)(void*, void*)) {
    Node* n;

    if (ll == NULL) {
        return;
    }
    n = ll->head;
    while (n != NULL) {
        hmp_insert(hmp, n->key, n->value, cmp);
        n = n->next;
    }
}

static void hmp_quicksort(Element* elmnts, long start, long end, int (*cmp)(void* key1, void*key2)) {
//    printf("start/end %ld %ld\n", start, end);
    long i = start, j = start;
    void* key;

    if (start >= end) {
        return;
    }
    key = elmnts[end].key;
//    for (int k = start; k <= end; k++) {
//        printf(">> %s\n", (char*) elmnts[k].key);
//    }
    while (i < end) {
//        printf("%s %s\n", (char*) elmnts[i].key, (char*) elmnts[end].key);
        if (cmp(elmnts[i].key, key) < 0) {
            hmp_swap(elmnts+i, elmnts+j);
            j++;
        }
        i++;
    }
//    printf("now about to swap %ld and %ld\n", j, end);
    hmp_swap(elmnts+j, elmnts+end);
//    printf("swapped\n");
    hmp_quicksort(elmnts, start, j-1, cmp);
    hmp_quicksort(elmnts, j+1, end, cmp);
}

Hashmap* hmp_create(void) {
    Hashmap* hmp = malloc(sizeof(Hashmap));
    hmp->loadfactorthresh = DEFAULT_LOAD_FACTOR_THRESHOLD;
    hmp->buckets = calloc(1, sizeof(Linkedlist*));
    hmp->buckets[0] = ll_create();
    hmp->numkeys = 0;
    hmp->numbuckets = 1;
    hmp->maxoccupancy = 0;
    hmp->minoccupancy = 0;
    hmp->numminoccupancy = 1;
    hmp->nummaxoccupancy = 1;
    return hmp;
}

int hmp_resize(Hashmap* hmp, long size, int (*cmp)(void*, void*)) {
    Hashmap newhmp;
    int i = 0;

//    printf("resizing w numkeys %ld/%ld\n", hmp->numkeys, hmp->numbuckets);
    if (size < hmp->numbuckets) {
        printf("special error: invalid resize input\n");
        return 1;
    }
    newhmp.loadfactorthresh = hmp->loadfactorthresh;
    newhmp.hashfn = hmp->hashfn;
    newhmp.numkeys = 0;
    newhmp.numbuckets = size;
    newhmp.buckets = calloc(size, sizeof(Linkedlist*));
    newhmp.maxoccupancy = 0;
    newhmp.minoccupancy = 0;
    newhmp.numminoccupancy = size;
    newhmp.nummaxoccupancy = size;
    while (i < hmp->numbuckets) {
        hmp_insertlist(&newhmp, hmp->buckets[i], cmp);
        i++;
    }
    hmp_shallowdestroy(hmp);
    *hmp = newhmp;

    return 0;
}

int hmp_insert(Hashmap* hmp, void* key, void* value, int (*cmp)(void*, void*)) {
    long h;
    int n;

    if (hmp == NULL || hmp->hashfn == NULL) {
        return 1;
    }    
    h = hmp->hashfn(hmp, key);
    if (hmp->buckets[h] == NULL) {
        hmp->buckets[h] = ll_create();
    }
    if (ll_insert(hmp->buckets[h], key, value, cmp)) {
        return 1;
    }
    hmp->numkeys++;
    if ((double) hmp->numkeys/hmp->numbuckets >= hmp->loadfactorthresh) {
        hmp_resize(hmp, hmp->numbuckets * HMP_GROWTH_FACTOR, cmp);
        return 0;
    }
    n = hmp->buckets[h]->numnodes;
    if (n > hmp->maxoccupancy) {
        hmp->nummaxoccupancy = 1;
        hmp->maxoccupancy = n;
    } else if (n == hmp->maxoccupancy) {
        hmp->nummaxoccupancy++;
    }
    if (n == hmp->minoccupancy+1) {
        if (hmp->numminoccupancy == 1) {
            hmp->minoccupancy = n;
        } else {
            hmp->numminoccupancy--;
        }
    }
    return 0;
}

Element hmp_find(Hashmap* hmp, void* key, int (*cmp)(void*, void*)) {
    Element elmnt = {NULL, NULL};
    long h;
    Node* n;

    if (hmp == NULL || hmp->hashfn == NULL) {
        return elmnt;
    }    
    h = hmp->hashfn(hmp, key);
    if (hmp->buckets[h] == NULL) {
        return elmnt;
    }
    n = ll_find(hmp->buckets[h], key, cmp);
    if (n != NULL) {
        elmnt.key = n->key;
        elmnt.value = n->value;
    }
    return elmnt;
}

Element hmp_remove(Hashmap* hmp, void* key, int (*cmp)(void*, void*)) {
    Element elmnt = {NULL, NULL};
    Node* n = NULL;
    long h;
    int num;

    if (hmp == NULL || hmp->hashfn == NULL) {
        return elmnt;
    }    
    h = hmp->hashfn(hmp, key);
    if (hmp->buckets[h] == NULL) {
        return elmnt;
    }
    n = ll_remove(hmp->buckets[h], key, cmp);
    if (n == NULL) {
        return elmnt;
    }
    elmnt.key = n->key;
    elmnt.value = n->value;
    free(n);
    num = hmp->buckets[h]->numnodes;
    if (num < hmp->minoccupancy) {
        hmp->numminoccupancy = 1;
        hmp->minoccupancy = num;
    } else if (num == hmp->minoccupancy) {
        hmp->numminoccupancy++;
    }
    if (num == hmp->maxoccupancy-1) {
        if (hmp->nummaxoccupancy == 1) {
            hmp->maxoccupancy = num;
        } else {
            hmp->nummaxoccupancy--;
        }
    }
    hmp->numkeys--;
    return elmnt;
}

void hmp_deepdestroy(Hashmap* hmp) {
    int i = 0;

    if (hmp == NULL || hmp->buckets == NULL) {
        return;
    }
    while (i < hmp->numbuckets) {
        ll_deepdestroy(hmp->buckets[i++]);
    }
    free(hmp->buckets);
    free(hmp);
}

void hmp_shallowdestroy(Hashmap* hmp) {
    int i = 0;

    if (hmp == NULL || hmp->buckets == NULL) {
        return;
    }
    while (i < hmp->numbuckets) {
        ll_shallowdestroy(hmp->buckets[i++]);
        free(hmp->buckets[i++]);
    }
    free(hmp->buckets);
}

void hmp_traverse(Hashmap* hmp, int (*cmp)(void* key1, void* key2), void (*dosomething)(void*, void*)) {
    Element* contents = calloc(hmp->numbuckets, sizeof(Element));
    int i, j;
    Node* n;

    for (i = j = 0; i < hmp->numbuckets; i++) {
        if (hmp->buckets[i] != NULL) {
            n = hmp->buckets[i]->head;
            while (n != NULL) {
                contents[j].key = n->key;
                contents[j].value = n->value;
                n = n->next;
                j++;
            }
        }
    }
//    printf("in qs\n");
    hmp_quicksort(contents, 0, hmp->numkeys-1, cmp);
//    printf("out qs\n");
    for (i = 0; i < hmp->numkeys; i++) {
        dosomething(contents[i].key, contents[i].value);
    }
    free(contents);
}
