/** Alan Cham
  * HW 2 #6*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILE_NAME_INDEX 1
#define NUM_ARRAYS 68
#define NUM_WORK_ITERATIONS 1

typedef struct array_set {
    double** array_2d;
    int num_arrays;
    long* lens;
} array_set;

array_set load_arrays(int k, char* file_name);
long* solution1(double find, array_set arrays, int new);
long* solution2(double find, array_set arrays, int new);
long* solution3(double find, array_set arrays, int new);
double work_kernel(int iters, array_set arrays, long* (*solution)(double, array_set, int));

int main (int argc, char* argv[]) {
    array_set arrays;
    int k = NUM_ARRAYS;
    double time1, time2, time3;
    int wi = NUM_WORK_ITERATIONS;
 
    if (argc < 2) {
        printf("Error: please enter filename as command-line argument.\n");
        return EXIT_FAILURE;        
    }
    arrays = load_arrays(k, argv[FILE_NAME_INDEX]);
    if (arrays.array_2d == NULL) {
        printf("Error: unable to open file %s.\n", argv[FILE_NAME_INDEX]);
        return EXIT_FAILURE;
    }

    time1 = work_kernel(wi, arrays, solution1);
    time2 = work_kernel(wi, arrays, solution2);
    time3 = work_kernel(wi, arrays, solution3);

    printf("Solution 1: takes %lf s\n", time1);
    printf("Solution 2: takes %lf s\n", time2);
    printf("Solution 3: takes %lf s\n", time3);

    for (int i = 0; i < k; i++) {
        free(arrays.array_2d[i]);
    }
    free(arrays.array_2d);
    free(arrays.lens);
    return EXIT_SUCCESS;
}

double work_kernel(int iters, array_set arrays, long* (*solve)(double, array_set, int)) {
    return 0;
}

long* solution1(double find, array_set arrays, int new) {
    return NULL;
}

long* solution2(double find, array_set arrays, int new) {
    return NULL;
}

long* solution3(double find, array_set arrays, int new) {
    return NULL;
}

array_set load_arrays(int k, char* file_name) {
    long* lens;
    long num_nums;
    array_set arrays;
    double** array_2d;
    FILE* file_ptr = fopen(file_name, "r");

    if (file_ptr == NULL) {
        arrays.array_2d = NULL;
        return arrays;
    }
    array_2d = malloc(sizeof(double*) * k);
    lens = malloc(sizeof(long) * k);
    for (int i = 0; i < k; i++) {
        fscanf(file_ptr, " %ld ", &num_nums);
        lens[i] = num_nums;
        array_2d[i] = malloc(sizeof(double) * num_nums);
        for (int j = 0; j < num_nums; j++) {
            fscanf(file_ptr, " %lf ", &array_2d[i][j]);
        }
        printf("%f\n", array_2d[i][num_nums-1]);
    }

    arrays.array_2d = array_2d;
    arrays.num_arrays = k;
    arrays.lens = lens;
    fclose(file_ptr);
    return arrays;
}
