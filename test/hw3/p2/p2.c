/** Alan Cham
  * MPCS 51100
  * November 17, 2016
  * Homework 3, p2 */

#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"
#include "unique.h"
#include <time.h>
  
#define LOWER_BOUND 5000
#define HIGHER_BOUND 10000

void scramble(int* array, int len);
int equals(void* obj1, void* obj2);
int h(const void* key);

int main(void) {
    int* arraywrepeats;
    int* verifyarray;
    int numuniques;
    int numrepeats;
    int result;

    printf("----------------------------------\n");
    printf("HW3 P2: Test Driver for Uniques\n");
    srand(time(NULL));

    printf(">>  Setting # of unique ints to random b/t %d and %d: ", LOWER_BOUND, HIGHER_BOUND);
    numuniques = rand() % (HIGHER_BOUND - LOWER_BOUND) + LOWER_BOUND;
    printf("%d\n", numuniques);

    printf(">>  Setting # of repeat ints to random b/t %d and %d: ", LOWER_BOUND, HIGHER_BOUND);
    numrepeats = rand() % (HIGHER_BOUND - LOWER_BOUND) + LOWER_BOUND;
    printf("%d\n", numrepeats);

    printf("----------------------------------\n");
    printf(">>  Creating array with %d unique ints\n", numuniques);
    arraywrepeats = malloc(sizeof(int) * (numuniques + numrepeats));
    for (int i=0; i < numuniques; i++) {
        arraywrepeats[i] = i;
    }

    printf(">>  Appending %d random repeats into the array\n", numrepeats);
    for (int i=0; i < numrepeats; i++) {
        arraywrepeats[numuniques + i] = rand() % numuniques;
    }

    printf(">>  Scrambling the array randomly\n");
    scramble(arraywrepeats, numuniques + numrepeats);

    printf("----------------------------------\n");
    printf(">>  Passing array to function uniq\n");
    result = uniq(arraywrepeats, numuniques+numrepeats, sizeof(int), equals, h);

    printf(">>  Number of uniques found: %d\n", result);
    printf(">>  Verifying all unique elements are in resulting array\n");
    verifyarray = calloc(numuniques, sizeof(int));
    for (int i=0; i < numuniques; i++) {
        verifyarray[arraywrepeats[i]] = 1;
    }
    result = 1;
    for (int i=0; i < numuniques; i++) {
        result &= verifyarray[i];
    }
    if (result) {
        printf(">>  SUCCESS: all unique elements found in output\n");
    } else {
        printf(">>  FAILURE: output is missing at least one unique element\n");
    }

    printf("----------------------------------\n");
    printf("End of Test Driver\n");
    printf("----------------------------------\n");
    return EXIT_SUCCESS;
}

void scramble(int* array, int len) {
    int r, tmp;
    for (int i=0; i < len; i++) {
        tmp = array[i];
        r = rand() % len;
        array[i] = array[r];
        array[r] = tmp;
    }

}


int equals(void* obj1, void* obj2) {
    return (*(int*) obj1 == *(int*) obj2);
}

int h(const void* key) {
    return *(int*) key;
}
