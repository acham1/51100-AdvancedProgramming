/** Alan Cham
  * HW 2 #6*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define MS_PER_S 1000
#define NUM_ARRAYS 68
#define FILE_NAME_INDEX 1
#define NUM_WORK_ITERATIONS 10000000
#define my_max(x, y) ((x) > (y) ? (x) : (y))
#define my_min(x, y) ((x) < (y) ? (x) : (y))
#define my_abs(x) (((x) < 0) ? -(x) : (x)) 

typedef struct array_set {
    double** array_2d;
    int num_arrays;
    long* lens;
    double min;
    double max;
    double minmax;
} array_set;

typedef struct union_pkg {
    double* unionized;
    long num_elements;
    long** ptr_arrays;
} union_pkg;

typedef struct M_node {
    double val;
    long p1;
    long p2;
} M_node;

void print_header(void);
union_pkg merge(array_set arrays);
array_set load_arrays(int k, char* file_name);
long* solution1(double find, array_set arrays, int new);
long* solution2(double find, array_set arrays, int new);
long* solution3(double find, array_set arrays, int new);
long db_bsearch(double* array, long start, long end, long len, double key);
double work_kernel(int iters, array_set arrays, long* (*solution)(double, array_set, int));

int main(int argc, char* argv[]) {
    array_set erase = {NULL, 0, NULL, 0, 0, 0};
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

    print_header();
    srand(time(NULL));
    for (int wi=1; wi <= NUM_WORK_ITERATIONS; wi*=10) {
        printf("%15e", (double) wi);       

        time1 = work_kernel(wi, arrays, solution1);
        printf("%15.4lf", time1*MS_PER_S);

        time2 = work_kernel(wi, arrays, solution2);
        printf("%15.4lf", time2*MS_PER_S);
        work_kernel(1, erase, solution2); // free memory

        time3 = work_kernel(wi, arrays, solution3);
        printf("%15.4lf\n", time3*MS_PER_S);
        work_kernel(1, erase, solution3); // free memory

        printf("%15.4s%15.4lf%15.4lf%15.4lf\n\n", "", time1/wi*MS_PER_S, time2/wi*MS_PER_S, time3/wi*MS_PER_S);
    }

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
        start = clock();
        indices = solve(find, arrays, i == 0);
        elapsed += (clock() - start)/(double)CLOCKS_PER_SEC;
//        if (arrays.array_2d != NULL) {
//            printf("\n**********begin**********\n");
//            printf("Finding %4.1lf: \n", find);
//            for (int j=0; j < arrays.num_arrays; j++) {
//                printf("%4.1lf  ", arrays.array_2d[j][indices[j]]);
//            }
//            printf("\n**********end**********\n");
//        }
        free(indices);
    }
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
    for (int i = 0; i < num_elements; i++) {
        least = DBL_MAX;
        finished = 1;
        for (int j = 0; j < num_arrays; j++) {
            if (list_pos[j] < arrays.lens[j] && arrays.array_2d[j][list_pos[j]] < least) {
                finished = 0;
                least = arrays.array_2d[j][list_pos[j]];
            }
        }
        for (int j = 0; j < num_arrays; j++) {
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
        if (unionized != NULL) {
            free(unionized);
            unionized = NULL;
        }
        if (ptr_arrays != NULL) {
            for (int i = 0; i < num_arrays; i++) {
                free(ptr_arrays[i]);
            }
            free(ptr_arrays);
            ptr_arrays = NULL;
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

    u_index = db_bsearch(unionized, 0, num_elements-1, num_elements, find);
    indices = malloc(sizeof(long) * num_arrays);
    for (int i = 0; i < num_arrays; i++) {
        indices[i] = ptr_arrays[i][u_index];
    }
    return indices;
}

long* solution3(double find, array_set arrays, int new) {
    long pos1, pos2, stop1, stop2;
    static long num_arrays = 0;
    static long* M_lens = NULL;
    static M_node** M = NULL;
    static double* first;      // array of values in first row of M
    long* indices = NULL;
    double dbl1, dbl2;
    long counter;
    long p;

    if (new) { // perform one-time set up for each new data set
        if (M != NULL) {
            for (int i = 0; i < num_arrays; i++) {
                free(M[i]);
            }
            free(M);
            free(M_lens);
            free(first);
            M = NULL;
            if (arrays.array_2d == NULL) {
                return NULL;
            }
        }

        num_arrays = arrays.num_arrays;
        M_lens = malloc(sizeof(long) * num_arrays);
        M = malloc(sizeof(M_node*) * num_arrays);
        M[num_arrays-1] = malloc(sizeof(M_node) * arrays.lens[num_arrays-1]);
        M_lens[num_arrays-1] = arrays.lens[num_arrays-1];
        for (int j=0; j < arrays.lens[num_arrays-1]; j++) {
            M[num_arrays-1][j].val = arrays.array_2d[num_arrays-1][j];
            M[num_arrays-1][j].p1 = j;
        }
        for (int i=num_arrays-2; i >= 0; i--) {
            M_lens[i] = arrays.lens[i] + M_lens[i+1]/2 + 1;
            M[i] = malloc(sizeof(M_node) * M_lens[i]);
            pos1 = pos2 = counter = 0;
            stop1 = arrays.lens[i];
            stop2 = M_lens[i+1];
            while (pos1 < stop1 || pos2 < stop2) {
                dbl1 = dbl2 = DBL_MAX;
                if (pos1 < stop1) {
                    dbl1 = arrays.array_2d[i][pos1];
                }
                if (pos2 < stop2) {
                    dbl2 = M[i+1][pos2].val;
                }
                if (dbl1 < dbl2) {
                    M[i][counter].val = dbl1;
                    M[i][counter].p1 = pos1++;
                    M[i][counter].p2 = my_min(pos2, M_lens[i+1]-1);
                } else if (dbl2 < dbl1) {
                    M[i][counter].val = dbl2;
                    M[i][counter].p1 = my_min(pos1, arrays.lens[i]-1);
                    M[i][counter].p2 = pos2;
                    pos2 += (pos2 == M_lens[i+1]-2 ? 1 : 2); // always include last element in M_i+1
                } else {
                    M[i][counter].val = dbl1;
                    M[i][counter].p1 = pos1++;
                    M[i][counter].p2 = pos2;
                    pos2 += (pos2 == M_lens[i+1]-2 ? 1 : 2); // always include last element in M_i+1
                }
                counter++;
            }
            M_lens[i] = counter;
            M[i] = realloc(M[i], sizeof(M_node) * counter);   
        }
        first = malloc(sizeof(double) * M_lens[0]);
        for (int i=0; i<M_lens[0]; i++) {
            first[i] = M[0][i].val;
        }
    } //end if (new)

    indices = malloc(sizeof(long) * num_arrays);
    p = db_bsearch(first, 0, M_lens[0]-1, M_lens[0], find);
    indices[0] = M[0][p].p1;
    for (int i=1; i<num_arrays; i++) {
        p = M[i-1][p].p2;
        if (M[i][my_max(0, p-1)].val > find) {
            indices[i] = M[i][my_max(0, p-1)].p1;
            p = p-1;
        } else {
            indices[i] = M[i][p].p1;
        }
    }
    return indices;
}

array_set load_arrays(int k, char* file_name) {
    FILE* file_ptr = fopen(file_name, "r");
    double min = +DBL_MAX;
    double max = -DBL_MAX;
    double minmax = +DBL_MAX;
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
        minmax = my_min(max, minmax);
        min = my_min(min, array_2d[i][0]);
    }

    arrays.array_2d = array_2d;
    arrays.num_arrays = k;
    arrays.lens = lens;
    arrays.minmax = minmax;
    arrays.max = max;
    arrays.min = min;
    fclose(file_ptr);
    return arrays;
}

void print_header(void) {
    printf("Alan Cham\n");
    printf("HW2 P6\n");
    printf("-------------------------------------------------------------------------\n");
    printf("Making raw performance analysis results:\n");
    printf("Top    : total runtime (ms)\n");
    printf("Bottom : average runtime per iteration (ms)\n");
    printf("-------------------------------------------------------------------------\n");
    printf("%15s%15s%15s%15s\n", "Iterations", "Strategy 1", "Stragegy 2", "Strategy 3");
}
