/** Alan Cham
  * MPCS 51100
  * November 17, 2016
  * Homework 3, p2 */

#ifndef UNIQUE_H
#define UNIQUE_H

#include "hashmap.h"
#include <stdlib.h>
  
#define unique_abs(a) ((a) > 0 ? (a) : -(a))

int uniq(void *f, int n, int sz, int (*equals)(void *, void *), int (*h)(const void *key));

// I have to use this wrapper because my buckets are sorted
// and might not search through the whole bucket otherwise
int u_cmp(void* obj1, void* obj2);

// I have to use this wrapper to ensure that the final hash
// is within the right range
long hashfn(Hashmap* hmp, void* obj);

#endif