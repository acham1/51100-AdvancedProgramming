#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Write array of number of iterations to file
#define WRITE_RESULT

// Array dimensions
#define DIM 100
#define DONE DIM*DIM

// Maximum number of iterations
#define MAX_ITER 10000

// Domain boundaries
#define XMIN -2
#define XMAX 1
#define YMIN -1.5
#define YMAX 1.5

#define mysqr(x) ((x)*(x))
#define bound(x) ((x) < 1 ? 1 : (x))

// Complex number
typedef struct complex_{
    double real;
    double imag;
} Complex;

double mandelbrot_serial(int prob_size, int print);
double mandelbrot_omp(int prob_size, int is_static, int print, int threads, int chunk_size);
void write_result(char* name, int* U, int prob_size);

int main(int argc, char **argv){
    int i, j, n;
    double time_var, time_var2;
    double mean, mean2, variance, variance2;
    double temp, temp2;
    int numTrials = 1;
    int max = omp_get_max_threads();
    time_t mytm;

    double* serial_results = malloc(sizeof(double) * numTrials);
    double** static_results = malloc(sizeof(double*) * max);
    for (i=0; i<max; i++) static_results[i] = malloc(sizeof(double) * numTrials);
    double** dynamic_results = malloc(sizeof(double*) * max);
    for (i=0; i<max; i++) dynamic_results[i] = malloc(sizeof(double) * numTrials);

    // print heading information
    time(&mytm);
    printf("Name:         Alan Cham\n");
    printf("Date:         %s", asctime(localtime(&mytm)));
    printf("Assignment:   Hw2 #3\n");
    printf("Thread limit: %d (on this machine)\n\n", max);

    printf("--------------------------------------------------------------------\n");
    printf("Part 1: Dependence of Runtime Mean and Variance on Number of Threads\n");
    printf("--------------------------------------------------------------------\n\n");

    // print heading information
    printf("Problem size DIM                           : %d\n", DIM);
    printf("Number of samples per test                 : %d\n", numTrials);

    /* time serial case  */
    printf("\nRunning serial case %2d times               : ", numTrials); fflush(stdout);
    for (j=1; j<=numTrials; j++) {
        printf("x"); fflush(stdout);
        serial_results[j-1] = mandelbrot_serial(DIM, j==1);
    }

    /* time static omp case */
    for (i=1; i<=max; i++) {
        printf("\nRunning %02d-thread static omp case %2d times : ", i, numTrials);
        for (j=1; j<=numTrials; j++) {
            printf("x"); fflush(stdout);
            static_results[i-1][j-1] = mandelbrot_omp(DIM, 1, i==max && j==numTrials, i, 0);
        }
    }

    /* time dynamic omp case */
    for (i=1; i<=max; i++) {
        printf("\nRunning %02d-thread dynamic omp case %2d times: ", i, numTrials);
        for (j=1; j<=numTrials; j++) {
            printf("x"); fflush(stdout);
            dynamic_results[i-1][j-1] = mandelbrot_omp(DIM, 0, i==max && j==numTrials, i, 0);
        }
    }

    // calculate serial mean and variance
    printf("\n\nSummary of Results (mean(s), variance(s^2), Ratio to Serial Time):\n"); fflush(stdout);
    for (time_var=0, i=0; i<numTrials; i++) 
        time_var += serial_results[i];
    temp = mean = time_var/numTrials;
    for(variance=0, i=0; i<numTrials; i++) 
        variance += mysqr(serial_results[i] - mean);
    variance = variance/numTrials;
    printf("Serial           : (%3.3lf, %lf, %3.3lf)\n", mean, variance, 1.0); fflush(stdout);
    
    // calculate omp mean and variance
    for(j=1; j<=max;j++) {
        for(time_var = time_var2 = 0, i=0; i<numTrials; i++) {
            time_var += static_results[j-1][i];
            time_var2 += dynamic_results[j-1][i];
        }
        mean = time_var/numTrials;
        mean2 = time_var2/numTrials;

        for(variance = variance2 = 0, i=0; i<numTrials; i++) {
            variance += mysqr(static_results[j-1][i] - mean);
            variance2 += mysqr(dynamic_results[j-1][i] - mean);
        }
        variance = variance/numTrials;
        variance2 = variance2/numTrials;
        printf("%02d-thread static : (%3.3lf, %lf, %3.3lf)\n", j, mean, variance, mean/temp); fflush(stdout);
        printf("%02d-thread dynamic: (%3.3lf, %lf, %3.3lf)\n", j, mean2, variance2, mean2/temp); fflush(stdout);
    }

    printf("\n---------------------------------------------------------------\n");
    printf("Part 2: Dependence of Runtime Mean and Variance on Problem Size\n");
    printf("---------------------------------------------------------------\n\n");

    printf("The following omp timing results use %d threads:\n\n", bound(max/2)); fflush(stdout);
    for (i=1; i<= DIM; i*=10) {
        // print heading information
        n = i;
        printf("Problem size DIM                  : %d\n", i); fflush(stdout);
        printf("Running serial case %02d times      : ", numTrials); fflush(stdout);

        // print progress update for serial case
        for(j=1; j<=numTrials; j++) {
            printf("x"); fflush(stdout);
            serial_results[j-1] = mandelbrot_serial(n, 0);
        }

        // compute mean and variance
        for(time_var = 0, j=1; j<=numTrials; j++) 
            time_var += serial_results[j-1];
        temp = mean = time_var/numTrials;
        for(variance = 0, j=0; j<numTrials; j++) 
            variance += mysqr(serial_results[j] - mean);
        temp2 = variance = variance/numTrials;

        // print progress update for static case
        printf("\nRunning static omp case %02d times  : ", numTrials); fflush(stdout);
        for(j=1; j<=numTrials; j++) {
            printf("x"); fflush(stdout);
            static_results[bound(max/2) - 1][j-1] = mandelbrot_omp(n, 1, 0, bound(max/2), 0);
        }

        // compute mean and variance
        for(time_var = 0, j=1; j<=numTrials; j++) 
            time_var += static_results[bound(max/2)-1][j-1];
        mean = time_var/numTrials;
        for(variance = 0, j=0; j<numTrials; j++) 
            variance += mysqr(static_results[bound(max/2)-1][j] - mean);
        variance = variance/numTrials;

        // print progress update for dynamic case
        printf("\nRunning dynamic omp case %02d times : ", numTrials); fflush(stdout);
        for(j=1; j<=numTrials; j++) {
            printf("x"); fflush(stdout);
            dynamic_results[bound(max/2) - 1][j-1] = mandelbrot_omp(n, 0, 0, bound(max/2), 0);
        }

        // compute mean and variance
        for(time_var = 0, j=1; j<=numTrials; j++) 
            time_var += dynamic_results[bound(max/2)-1][j-1];
        mean2 = time_var/numTrials;
        for(variance = 0, j=0; j<numTrials; j++) 
            variance2 += mysqr(dynamic_results[bound(max/2)-1][j] - mean);
        variance2 = variance2/numTrials;

        // print results summary
        printf("\nSerial (mean, variance)           : %3.3lf, %lf\n", temp, temp2); fflush(stdout);
        printf("%02d-thread static (mean, variance) : %3.3lf, %lf\n", bound(max/2), mean, variance); fflush(stdout);
        printf("%02d-thread dynamic (mean, variance): %3.3lf, %lf\n", bound(max/2), mean, variance); fflush(stdout);
        printf("Static OMP Time Ratio to Serial   : %3.3lf\n", mean/temp); fflush(stdout);
        printf("Dynamic OMP Time Ratio to Serial  : %3.3lf\n\n", mean2/temp); fflush(stdout);
    }

    for (i=0; i<max; i++) free(static_results[i]);
    for (i=0; i<max; i++) free(dynamic_results[i]);
    free(static_results);
    free(dynamic_results);
    free(serial_results);
    return 0;
}

void write_result(char* name, int* U, int prob_size) {
    int px, py;
    FILE* f;

    if ((f = fopen(name, "w")) == NULL){
        printf("Error opening file for writing.\n");
        exit(1);
    }
    for (py=0; py<prob_size; py++){
        for (px=0; px<prob_size; px++) {
            fprintf(f, "%d ", U[prob_size*px + py]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

double mandelbrot_omp(int prob_size, int is_static, int print, int threads, int chunk_size) {
    /* Fill in your code here */
    int px = 0, py = 0, iter = 0, *U;
    double tmp = 0, tick, tock;
    Complex c, z;

    // Allocate global array to collect data 
    U = malloc(prob_size*prob_size*sizeof(int));

    if (is_static && !chunk_size) {
        tick = omp_get_wtime();
#pragma omp parallel for firstprivate(c, z, iter, U, py, tmp), schedule(static), num_threads(threads)
        for (px=0; px<= prob_size-1; px++) {
            for (py=0; py<prob_size; py++) {
                c.real = XMIN + px*(XMAX - XMIN)/(double)prob_size;
                c.imag = YMIN + py*(YMAX - YMIN)/(double)prob_size;
                z.real = 0;
                z.imag = 0;
                iter = 0;
                while (z.real*z.real + z.imag*z.imag < 4 && iter < MAX_ITER){
                    tmp = z.real*z.real - z.imag*z.imag + c.real;
                    z.imag = 2*z.real*z.imag + c.imag;
                    z.real = tmp;
                    iter++;
                }
                U[px*prob_size + py] = iter;
            }
        }
    } else if (is_static && chunk_size) {
        tick = omp_get_wtime();
#pragma omp parallel for firstprivate(c, z, iter, U, py, tmp), schedule(static, chunk_size), num_threads(threads)
        for (px=0; px<= prob_size-1; px++) {
            for (py=0; py<prob_size; py++) {
                c.real = XMIN + px*(XMAX - XMIN)/(double)prob_size;
                c.imag = YMIN + py*(YMAX - YMIN)/(double)prob_size;
                z.real = 0;
                z.imag = 0;
                iter = 0;
                while (z.real*z.real + z.imag*z.imag < 4 && iter < MAX_ITER){
                    tmp = z.real*z.real - z.imag*z.imag + c.real;
                    z.imag = 2*z.real*z.imag + c.imag;
                    z.real = tmp;
                    iter++;
                }
                U[px*prob_size + py] = iter;
            }
        }
    } else {
        tick = omp_get_wtime();
#pragma omp parallel for firstprivate(c, z, iter, U, py, tmp), schedule(dynamic), num_threads(threads)
        for (px=0; px<= prob_size-1; px++) {
            for (py=0; py<prob_size; py++) {
                c.real = XMIN + px*(XMAX - XMIN)/(double)prob_size;
                c.imag = YMIN + py*(YMAX - YMIN)/(double)prob_size;
                z.real = 0;
                z.imag = 0;
                iter = 0;
                while (z.real*z.real + z.imag*z.imag < 4 && iter < MAX_ITER){
                    tmp = z.real*z.real - z.imag*z.imag + c.real;
                    z.imag = 2*z.real*z.imag + c.imag;
                    z.real = tmp;
                    iter++;
                }
                U[px*prob_size + py] = iter;
            }
        }
    }

    tock = omp_get_wtime();
    #ifdef WRITE_RESULT
    if (print && is_static) {
        write_result("p3.static_results.txt", U, prob_size);
    } else if (print) {
        write_result("p3.dynamic_results.txt", U, prob_size);
    }
    #endif
    return tock-tick; 
} 

double mandelbrot_serial(int prob_size, int print) {
    int px, py, iter, *U, i=0;
    double tmp;
    Complex c, z;

    // Allocate global array to collect data 
    U = malloc(prob_size*prob_size*sizeof(int));

    double tick = omp_get_wtime();
    for (px=0; px<prob_size; px++) {
        for (py=0; py<prob_size; py++) {
            c.real = XMIN + px*(XMAX - XMIN)/(double)prob_size;
            c.imag = YMIN + py*(YMAX - YMIN)/(double)prob_size;
            z.real = 0;
            z.imag = 0;
            iter = 0;
            while (z.real*z.real + z.imag*z.imag < 4 && iter < MAX_ITER){
                tmp = z.real*z.real - z.imag*z.imag + c.real;
                z.imag = 2*z.real*z.imag + c.imag;
                z.real = tmp;
                iter++;
            }
            U[i++] = iter;
        }
    }
    double tock = omp_get_wtime();

    // Write DIM*DIM array of number of iterations at each point to file
    #ifdef WRITE_RESULT
    if (print) write_result("p3.serial_result.txt", U, prob_size);
    #endif
    return tock-tick; 
}
