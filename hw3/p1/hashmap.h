/** Alan Cham
  * MPCS 51100
  * November 14, 2016
  * Homework 3, p1 */

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "linkedlist.h"

typedef struct {
    Linkedlist* buckets;
    int numbuckets;
} Hashmap;

#endif