/** Alan Cham
  * HW 2 #6*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define S_TO_MS 1000
#define NUM_ARRAYS 68
#define FILE_NAME_INDEX 1
#define NUM_WORK_ITERATIONS 1000
#define my_max(x, y) ((x) > (y) ? (x) : (y))
#define my_min(x, y) ((x) < (y) ? (x) : (y))

typedef struct array_set {
    double** array_2d;
    int num_arrays;
    long* lens;
    double min;
    double max;
} array_set;

array_set load_arrays(int k, char* file_name);
long* solution1(double find, array_set arrays, int new);
long* solution2(double find, array_set arrays, int new);
long* solution3(double find, array_set arrays, int new);
long db_bsearch(double* array, long start, long end, long len, double key);
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

    srand(time(NULL));
    printf("Working strategy 1: ");
    time1 = work_kernel(wi, arrays, solution1);
    printf("Working strategy 2: ");
    time2 = work_kernel(wi, arrays, solution2);
    printf("Working strategy 3: ");
    time3 = work_kernel(wi, arrays, solution3);

    printf("Solution 1: takes %lf ms\n", time1*S_TO_MS);
    printf("Solution 2: takes %lf ms\n", time2*S_TO_MS);
    printf("Solution 3: takes %lf ms\n", time3*S_TO_MS);

    for (int i = 0; i < k; i++) {
        free(arrays.array_2d[i]);
    }
    free(arrays.array_2d);
    free(arrays.lens);
    return EXIT_SUCCESS;
}

double work_kernel(int iters, array_set arrays, long* (*solve)(double, array_set, int)) {
    double factor = (arrays.max-arrays.min)/RAND_MAX;
    double elapsed = 0;
    long* indices;
    clock_t start;
    double find;

    for (int i = 0; i < iters; i++) {
        find = arrays.min + factor*rand();
//        printf("finding %lf\n", find);
//        printf("x");
        fflush(stdin);
        start = clock();
        indices = solve(find, arrays, i == 0);
        elapsed += (clock() - start)/(double)CLOCKS_PER_SEC;
//        for (int j = 0; j < arrays.num_arrays; j++) {
//            printf("%lf ", arrays.array_2d[j][indices[j]]);
//        }
//        printf("\nend\n");
        free(indices);
    }
    printf("\n");
//    printf("wk_end\n");
    return elapsed;
}

long db_bsearch(double* array, long start, long end, long len, double key) {
    long mid = (start+end+1)/2;

    if (start >= end) {
        if (key == array[end]) {
            return end;
        } else if (key > array[end]) {
            return my_min(end+1, len-1);
        } else {
            return end;
        }
    }
    if (key == array[mid]) {
        return mid;
    } else if (key < array[mid]) {
        return db_bsearch(array, start, mid-1, len, key);
    } else {
        return db_bsearch(array, mid+1, end, len, key);
    }
}

long* solution1(double find, array_set arrays, int new) {
    long* indices = malloc(sizeof(long) * arrays.num_arrays);
    int num_arrays = arrays.num_arrays;
    long len;

    for (int i = 0; i < num_arrays; i++) {
        len = arrays.lens[i];
        indices[i] = db_bsearch(arrays.array_2d[i], 0, len - 1, len, find);
    }
    return indices;
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
    double max = -DBL_MAX;
    double min = +DBL_MAX;
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
        max = my_max(max, array_2d[i][num_nums-1]);
        min = my_min(min, array_2d[i][0]);
    }

    arrays.array_2d = array_2d;
    arrays.num_arrays = k;
    arrays.lens = lens;
    arrays.max = max;
    arrays.min = min;
    fclose(file_ptr);
    return arrays;
}