/** Alan Cham
  * MPCS 51100
  * November 17, 2016
  * Homework 3, p2 */

#include <stdio.h>
#include <stdlib.h>

#define p2_abs(a) ((a) > 0 ? (a) : -(a))


int uniq(void *f, int n, int sz, int (*equals)(void *, void *), int (*h)(const void* key));
int equals(void* obj1, void* obj2);
int h(const void* key);

int main(void) {
    return EXIT_SUCCESS;
}

int uniq(void *f, int n, int sz, int (*equals)(void *, void *), int (*h)(const void *key)) {

    return 0;
}

int equals(void* obj1, void* obj2) {
    return *(int*) obj == *(int*) obj2;
}

int h(const void* key) {

}