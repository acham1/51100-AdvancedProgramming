/** Alan Cham
  * HW 2 #6*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define S_TO_MS 1000
#define NUM_ARRAYS 68
#define FILE_NAME_INDEX 1
#define NUM_WORK_ITERATIONS 1
#define my_max(x, y) ((x) > (y) ? (x) : (y))
#define my_min(x, y) ((x) < (y) ? (x) : (y))

typedef struct array_set {
    double** array_2d;
    int num_arrays;
    long* lens;
    double min;
    double max;
} array_set;

typedef struct union_pkg {
    double* unionized;
    long num_elements;
    long** ptr_arrays;
} union_pkg;

union_pkg merge(array_set arrays);
array_set load_arrays(int k, char* file_name);
long* solution1(double find, array_set arrays, int new);
long* solution2(double find, array_set arrays, int new);
long* solution3(double find, array_set arrays, int new);
long db_bsearch(double* array, long start, long end, long len, double key);
double work_kernel(int iters, array_set arrays, long* (*solution)(double, array_set, int));

int main (int argc, char* argv[]) {
    array_set erase = {NULL, 0, NULL, 0, 0};
    int wi = NUM_WORK_ITERATIONS;
    double time1, time2, time3;
    int k = NUM_ARRAYS;
    array_set arrays;

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
    printf("Working strategy 2: \n");
    time2 = work_kernel(wi, arrays, solution2);
    work_kernel(1, erase, solution2); // free memory
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
        printf("finding %lf\n", find);
//        printf("x");
//        fflush(stdout);
        start = clock();
        indices = solve(find, arrays, i == 0);
        elapsed += (clock() - start)/(double)CLOCKS_PER_SEC;
        for (int j = 0; j < arrays.num_arrays; j++) {
            printf("%.20lf ", arrays.array_2d[j][indices[j]]);
        }
        printf("\nend\n");
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
    int num_arrays = arrays.num_arrays;
    long* indices;
    long len;

    indices = malloc(sizeof(long) * arrays.num_arrays);
    for (int i = 0; i < num_arrays; i++) {
        len = arrays.lens[i];
        indices[i] = db_bsearch(arrays.array_2d[i], 0, len - 1, len, find);
    }
    return indices;
}

union_pkg merge(array_set arrays) {
    long num_elements = 0;
    long** ptr_arrays;
    double* unionized;
    long counter = 0;
    union_pkg u_pkg;
    int num_arrays;
    long* list_pos;
    double least;
    int finished;
    long key;
  
    printf("Enter merge\n");
    num_arrays = arrays.num_arrays;
    for (int i = 0; i < num_arrays; i++) {
        num_elements += arrays.lens[i];
    }
    ptr_arrays = malloc(sizeof(long*) * num_arrays);
    for (int i = 0; i < num_arrays; i++) {
        ptr_arrays[i] = malloc(sizeof(long) * num_elements);
    }
    unionized = malloc(sizeof(double) * num_elements);
    list_pos = malloc(sizeof(long) * num_arrays);
    for (int i = 0; i < num_arrays; i++) {
        list_pos[i] = 0;
    }
    printf("%ld\n", num_elements);
    for (int i = 0; i < num_elements; i++) {
//        printf("%d\n", i);
        least = DBL_MAX;
        finished = 1;
        for (int j = 0; j < num_arrays; j++) {
//            printf("->%d\n", j);
            if (list_pos[j] < arrays.lens[j] && arrays.array_2d[j][list_pos[j]] < least) {
                finished = 0;
                least = arrays.array_2d[j][list_pos[j]];
            }
        }
        for (int j = 0; j < num_arrays; j++) {
//            printf("second 4 - %d\n", j);
            if (arrays.array_2d[j][list_pos[j]] == least) {
                ptr_arrays[j][i] = list_pos[j];
                list_pos[j]++;
            } else {
                ptr_arrays[j][i] = -1;
            }
        }
        unionized[i] = least;
        if (finished) {
            break;
        }
        counter++;
    }
    unionized = realloc(unionized, sizeof(double) * counter);
    if (unionized == NULL) {
        printf("Failed unionized realloc.\n");
    }
    for (int i = 0; i < num_arrays; i++) {
        ptr_arrays[i] = realloc(ptr_arrays[i], sizeof(long) * counter);   
        if (ptr_arrays[i] == NULL) {
            printf("Failed realloc ptr_array[%d]\n", i);
        }
    }
    for (int i = 0; i < num_arrays; i++) {
        key = arrays.lens[i]-1;
        for (int j = counter-1; j >= 0; j--) {
            if (ptr_arrays[i][j] == -1) {
                ptr_arrays[i][j] = key;
            } else {
                key = ptr_arrays[i][j];
            }
        }
    }
    free(list_pos);
    u_pkg.num_elements = counter;
    u_pkg.ptr_arrays = ptr_arrays;
    u_pkg.unionized = unionized;
    printf("Exit merge\n");
    return u_pkg;
}

long* solution2(double find, array_set arrays, int new) {
    static double* unionized = NULL;
    static long** ptr_arrays = NULL;
    static long num_elements = 0;
    static long num_arrays = 0;
    union_pkg u_pkg;
    long* indices;
    long u_index;

    if (new) {
        free(unionized);
        if (ptr_arrays != NULL) {
            for (int i = 0; i < num_arrays; i++) {
                free(ptr_arrays[i]);
            }
            free(ptr_arrays);
        }
        if (arrays.array_2d == NULL) {
            return NULL;
        }
        u_pkg = merge(arrays);
        num_elements = u_pkg.num_elements;
        num_arrays = arrays.num_arrays;
        ptr_arrays = u_pkg.ptr_arrays;
        unionized = u_pkg.unionized;
    }

    printf("num_elements: %ld\n", num_elements);
    printf("last: %lf\n", unionized[num_elements-1]);
    u_index = db_bsearch(unionized, 0, num_elements-1, num_elements, find);
    printf("u_index: %ld\n", u_index);
    printf("val at udex: %lf\n", unionized[u_index]);
    indices = malloc(sizeof(long) * num_arrays);
    for (int i = 0; i < num_arrays; i++) {
        indices[i] = ptr_arrays[i][u_index];
    }
    return indices;
}

long* solution3(double find, array_set arrays, int new) {
    return NULL;
}

array_set load_arrays(int k, char* file_name) {
    FILE* file_ptr = fopen(file_name, "r");
    double min = +DBL_MAX;
    double max = -DBL_MAX;
    double** array_2d;
    array_set arrays;
    long num_nums;
    long* lens;

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