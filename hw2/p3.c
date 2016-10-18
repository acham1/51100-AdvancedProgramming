#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

// Write array of number of iterations to file
#define WRITE_RESULT

// Array dimensions
#define DIM 1000
#define DONE DIM*DIM

// Maximum number of iterations
#define MAX_ITER 10000

// Domain boundaries
#define XMIN -2
#define XMAX 1
#define YMIN -1.5
#define YMAX 1.5

// Complex number
typedef struct complex_{
    double real;
    double imag;
} Complex;

double mandelbrot_serial(int print);
double mandelbrot_omp(int is_static, int print, int threads);
void write_result();

int main(int argc, char **argv){
    double time;
    int numTrials = 1;
    int max = omp_get_max_threads();

    for (int i = 0; i < numTrials; i++) {
        time = mandelbrot_omp(1, 1, max);
        printf("OMP static version took %f seconds.\n",time);
        time = mandelbrot_omp(0, 1, max);
        printf("OMP dynamic version took %f seconds.\n",time);
        time = mandelbrot_serial(1);
        printf("Serial version took %f seconds.\n",time);
    }
    return 0;
}

void write_result(char* name, int* U) {
    int px, py;
    FILE* f;

    if ((f = fopen(name, "w")) == NULL){
        printf("Error opening file for writing.\n");
        exit(1);
    }
    for (py=0; py<DIM; py++){
        for (px=0; px<DIM; px++) {
            fprintf(f, "%d ", U[DIM*px + py]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

double mandelbrot_omp(int is_static, int print, int threads) {
    /* Fill in your code here */
    int px = 0, py = 0, iter = 0, *U;
    double tmp = 0, tick, tock;
    Complex c, z;

    // Allocate global array to collect data 
    U = malloc(DIM*DIM*sizeof(int));

    if (is_static) {
        tick = omp_get_wtime();
#pragma omp parallel for firstprivate(c, z, iter, U, py, tmp), schedule(static), num_threads(threads)
        for (px=0; px<= DIM-1; px++) {
            for (py=0; py<DIM; py++) {
                c.real = XMIN + px*(XMAX - XMIN)/(double)DIM;
                c.imag = YMIN + py*(YMAX - YMIN)/(double)DIM;
                z.real = 0;
                z.imag = 0;
                iter = 0;
                while (z.real*z.real + z.imag*z.imag < 4 && iter < MAX_ITER){
                    tmp = z.real*z.real - z.imag*z.imag + c.real;
                    z.imag = 2*z.real*z.imag + c.imag;
                    z.real = tmp;
                    iter++;
                }
                U[px*DIM + py] = iter;
            }
        }
    } else {
        tick = omp_get_wtime();
#pragma omp parallel for firstprivate(c, z, iter, U, py, tmp), schedule(dynamic), num_threads(threads)
        for (px=0; px<= DIM-1; px++) {
            for (py=0; py<DIM; py++) {
                c.real = XMIN + px*(XMAX - XMIN)/(double)DIM;
                c.imag = YMIN + py*(YMAX - YMIN)/(double)DIM;
                z.real = 0;
                z.imag = 0;
                iter = 0;
                while (z.real*z.real + z.imag*z.imag < 4 && iter < MAX_ITER){
                    tmp = z.real*z.real - z.imag*z.imag + c.real;
                    z.imag = 2*z.real*z.imag + c.imag;
                    z.real = tmp;
                    iter++;
                }
                U[px*DIM + py] = iter;
            }
        }
    }

    tock = omp_get_wtime();
    #ifdef WRITE_RESULT
    if (print && is_static) {
        write_result("omp_static_results.txt", U);
    } else if (print) {
        write_result("omp_dynamic_results.txt", U);
    }
    #endif
    return tock-tick; 
} 

double mandelbrot_serial(int print) {
    int px, py, iter, *U, i=0;
    double tmp;
    Complex c, z;

    // Allocate global array to collect data 
    U = malloc(DIM*DIM*sizeof(int));

    double tick = omp_get_wtime();
    for (px=0; px<DIM; px++) {
        for (py=0; py<DIM; py++) {
            c.real = XMIN + px*(XMAX - XMIN)/(double)DIM;
            c.imag = YMIN + py*(YMAX - YMIN)/(double)DIM;
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
    if (print) write_result("serial_result.txt", U);
    #endif
    return tock-tick; 
}
