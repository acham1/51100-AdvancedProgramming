/** Alan Cham
  * MPCS 51100
  * November 17, 2016
  * Homework 3, p2 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define my_max(x, y) ((x) > (y) ? (x) : (y))
#define my_min(x, y) ((x) < (y) ? (x) : (y))
#define my_abs(x) (((x) < 0) ? -(x) : (x)) 
#define NUM_WORK_ITERATIONS 1000000
#define MAX_NUM_BINS 10000
#define NUM_ARRAYS 68

typedef struct M_node {
    double val;
    long p1;
    long p2;
} M_node;

typedef struct Bin {
    long b1[NUM_ARRAYS];
    long b2[NUM_ARRAYS];
} Bin;

double work_kernel(int iters, long* (*solution)(double, int));
long db_bsearch(double* array, long start, long end, long len, double key);
int inputvalid(int argc, char* argv[]);
long* solution3(double find, int new);
long* solution4(double find, int new);
void load_arrays(char* file_name);
void print_header(void);
void setupsoln3(void);
void setupsoln4(void);

double* firstrowM = NULL;
double** array_2d = NULL;
long* M_lens = NULL;
M_node** M = NULL;
long* lens = NULL;
Bin* bins = NULL;
long numbins;
double min;
double max;

int main(int argc, char* argv[]) {
    double times[5];
    double timesper[5];

    if (!inputvalid(argc, argv))
        return EXIT_FAILURE;
    print_header();
    srand(time(NULL));
    for (int wi=1; wi <= NUM_WORK_ITERATIONS; wi*=10) {
        printf("%15.2e", (double) wi);       

        times[0] = work_kernel(wi, solution3);
        timesper[0] = times[0]/wi;
        printf("%15.4lf", times[0]);

        numbins = 1;
        times[1] = work_kernel(wi, solution4);
        timesper[1] = times[1]/wi;
        printf("%15.4lf", times[1]);

        numbins = 10;
        times[2] = work_kernel(wi, solution4);
        timesper[2] = times[2]/wi;
        printf("%15.4lf", times[2]);

        numbins = 100;
        times[3] = work_kernel(wi, solution4);
        timesper[3] = times[3]/wi;
        printf("%15.4lf", times[3]);

        numbins = 1000;
        times[4] = work_kernel(wi, solution4);
        timesper[4] = times[4]/wi;
        printf("%15.4lf", times[4]);

        numbins = 10000;
        times[5] = work_kernel(wi, solution4);
        timesper[5] = times[5]/wi;
        printf("%15.4lf\n", times[5]);

        printf("%15.4s%15.4lf%15.4lf%15.4lf%15.4lf%15.4lf%15.4lf\n\n", "", 
            timesper[0], timesper[1], timesper[2], timesper[3], timesper[4], timesper[5]);
    }

    printf("-------------------------------------------------------------------------\n");
    printf("    Note   : Old refers to 3rd method in Hw2 P6; New refers to this hw's hash-like method\n");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < NUM_ARRAYS; i++)
        free(array_2d[i]);
    free(array_2d);
    free(lens);
    return EXIT_SUCCESS;
}

double work_kernel(int iters, long* (*solve)(double, int)) {
    double factor = (max-min)/RAND_MAX;
    double elapsed = 0;
    long* indices;
    clock_t start;
    double find;

    for (int i = 0; i < iters; i++) {
        find = min + factor*rand();
        start = clock();
        indices = solve(find, i == 0);
        elapsed += (clock() - start)/(double)CLOCKS_PER_SEC;
        free(indices);
    }
    return elapsed * 1000; //convert to ms
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

void load_arrays(char* file_name) {
    FILE* file_ptr = fopen(file_name, "r");
    min = +DBL_MAX;
    max = -DBL_MAX;
    long num_nums;

    if (file_ptr == NULL) {
        array_2d = NULL;
        return;
    }
    array_2d = malloc(sizeof(double*) * NUM_ARRAYS);
    lens = malloc(sizeof(long) * NUM_ARRAYS);
    for (int i = 0; i < NUM_ARRAYS; i++) {
        fscanf(file_ptr, " %ld ", &num_nums);
        lens[i] = num_nums;
        array_2d[i] = malloc(sizeof(double) * num_nums);
        for (int j = 0; j < num_nums; j++) {
            fscanf(file_ptr, " %lf ", &array_2d[i][j]);
        }
        max = my_max(max, array_2d[i][num_nums-1]);
        min = my_min(min, array_2d[i][0]);
    }
    fclose(file_ptr);
}

void print_header(void) {
    printf("-------------------------------------------------------------------------\n");
    printf("    Alan Cham\n");
    printf("    HW3 P3\n");
    printf("-------------------------------------------------------------------------\n");
    printf("Making raw performance analysis results:\n");
    printf("    Top    : total runtime (ms)\n");
    printf("    Bottom : average runtime per iteration (ms)\n");
    printf("-------------------------------------------------------------------------\n");
    printf("%15s%15s%15s%15s%15s%15s%15s\n", "Num Searches", "Old", "New(1 bin)", "New(10 bin)", "New(100 bin)", "New(1000 bin)", "New(10000 bin)");
}

int inputvalid(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error: please enter arrays filename as command-line argument.\n");
        return 0;        
    }
    load_arrays(argv[1]);
    if (array_2d == NULL) {
        printf("Error: unable to open arrays file %s.\n", argv[1]);
        return 0;
    }
    return 1;
}

long* solution4(double find, int new) {
    int b = (find-min)/(max-min)*numbins;
    long* indices = calloc(NUM_ARRAYS, sizeof(long));

    if (new) {
        free(bins);
        setupsoln4();
    }
    b = my_max(0, b);
    b = my_min(b, numbins-1);
    for (int i=0; i < NUM_ARRAYS; i++) {
        // binary search between the bin bounds
        indices[i] = db_bsearch(array_2d[i], bins[b].b1[i], bins[b].b2[i], lens[i], find);
    }
    return indices;
}

// determine the index bounds for each bin
void setupsoln4(void) {
    double* lowerthresh = malloc(sizeof(double) * numbins);
    double* higherthresh = malloc(sizeof(double) * numbins);
    int pos, binnum;

    bins = malloc(numbins * sizeof(Bin));
    for (int j=0; j < numbins; j++) {
        lowerthresh[j] = min + j * (max-min)/numbins;
        higherthresh[j] = min + (j+1) * (max-min)/numbins;
    }
    for (int i=0; i < NUM_ARRAYS; i++) {
        pos = 0;
        for (binnum=0; binnum < numbins; binnum++) {
            bins[binnum].b1[i] = bins[binnum].b2[i] = -1;
            while (bins[binnum].b1[i] == -1 || bins[binnum].b2[i] == -1) {
                if (bins[binnum].b1[i] == -1 && (array_2d[i][pos] >= lowerthresh[binnum] || pos == lens[i] -1)) {
                    bins[binnum].b1[i] = pos;
                }
                if (bins[binnum].b2[i] == -1 && (array_2d[i][pos] >= higherthresh[binnum] || pos == lens[i] -1)) {
                    bins[binnum].b2[i] = pos;
                } else {
                    pos++;
                }
            }            
        }
    }
    free(lowerthresh);
    free(higherthresh);
}

long* solution3(double find, int new) {
    long* indices = NULL;
    long p;

    if (new) { // perform one-time set up for each new data set
        if (M != NULL) {
            for (int i = 0; i < NUM_ARRAYS; i++)
                free(M[i]);
            free(firstrowM);
            free(M_lens);
            free(M);
            M = NULL;
        }
        setupsoln3();
    }

    indices = malloc(sizeof(long) * NUM_ARRAYS);
    p = db_bsearch(firstrowM, 0, M_lens[0]-1, M_lens[0], find);
    indices[0] = M[0][p].p1;
    for (int i=1; i<NUM_ARRAYS; i++) {
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

void setupsoln3(void) {
    long pos1, pos2, stop1, stop2;
    double dbl1, dbl2;
    long counter;

    M_lens = malloc(sizeof(long) * NUM_ARRAYS);
    M = malloc(sizeof(M_node*) * NUM_ARRAYS);
    M[NUM_ARRAYS-1] = malloc(sizeof(M_node) * lens[NUM_ARRAYS-1]);
    M_lens[NUM_ARRAYS-1] = lens[NUM_ARRAYS-1];
    for (int j=0; j < lens[NUM_ARRAYS-1]; j++) {
        M[NUM_ARRAYS-1][j].val = array_2d[NUM_ARRAYS-1][j];
        M[NUM_ARRAYS-1][j].p1 = j;
    }
    for (int i=NUM_ARRAYS-2; i >= 0; i--) {
        M_lens[i] = lens[i] + M_lens[i+1]/2 + 1;
        M[i] = malloc(sizeof(M_node) * M_lens[i]);
        pos1 = pos2 = counter = 0;
        stop1 = lens[i];
        stop2 = M_lens[i+1];
        while (pos1 < stop1 || pos2 < stop2) {
            dbl1 = dbl2 = DBL_MAX;
            if (pos1 < stop1) {
                dbl1 = array_2d[i][pos1];
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
                M[i][counter].p1 = my_min(pos1, lens[i]-1);
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
    firstrowM = malloc(sizeof(double) * M_lens[0]);
    for (int i=0; i<M_lens[0]; i++) {
        firstrowM[i] = M[0][i].val;
    }
}