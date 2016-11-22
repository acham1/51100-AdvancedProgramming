// This is to strip out the prime numbers from the naturalnumbers.org
// file that has additional unneeded information. The next accepted prime
// must be at least twice the previous accepted prime.

#include <stdio.h>
#include <stdlib.h>

#define IN_FILE "P-1000000.txt"
#define OUT_FILE "primes.txt"
#define NUM_PRIMES 1000000
#define MAX_NUM_WIDTH 100

int main(void) {
    FILE* fi = fopen(IN_FILE, "r");  
    FILE* fo = fopen(OUT_FILE, "w");
    char garbage[MAX_NUM_WIDTH+1];
    int threshold = 2;
    int prevprime = 1;
    int primenum = 1;

    if (fi == NULL) {
        printf("error: failed to open input file %s\n", IN_FILE);
        return EXIT_FAILURE;
    }  
    if (fo == NULL) {
        printf("error: failed to open output file %s\n", OUT_FILE);
        return EXIT_FAILURE;
    }  
    while (!feof(fi) && fscanf(fi, "%s %d, %s", garbage, &primenum, garbage) != EOF) {
        if (primenum > threshold) {
            fprintf(fo, "%d\n", prevprime);
            threshold *= 2;
        }
        prevprime = primenum;
    }

    fclose(fi);
    fclose(fo);
    return EXIT_SUCCESS;
}