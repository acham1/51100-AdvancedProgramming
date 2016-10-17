/** Name:       Alan Cham
 *  Assignment: HW2 Q2 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define mysqr(x) ((x)*(x))
#define bound(x) ((x) < 1 ? 1 : (x))
#define N 1000

float **matrix(int n) {
	float *data = (float *) calloc(n*n, sizeof(float));
	float **M  = (float **) malloc(n * sizeof(float*));

	for (int i=0; i<n; i++)
		M[i] = &data[i*n];
	return M;
}

void matrix_free( float ** M) {
	free(M[0]);
	free(M);
}

void init(float **M, int n) {
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			M[i][j] = (float) (rand()%100);
}

/* Perform matrix multiplication using OpenMP */
// argument t is number of threads to use
double mm_omp(int n, int t) {
	// Allocate arrays
	float **A = matrix(n);
	float **B = matrix(n);
	float **C = matrix(n);
	init(A, n);
	init(B, n);

	// Multiply
	double start = omp_get_wtime();
#pragma omp parallel for num_threads(t), firstprivate(A,B,C,n), schedule(static)
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			for (int k=0; k<n; k++)
				C[i][j] += A[i][k] * B[k][j];
	double stop = omp_get_wtime();

	matrix_free(A);
	matrix_free(B);
	matrix_free(C);
    return stop-start;
}

/* Perform matrix multiplication serially */
double mm_serial(int n) {
	// Allocate arrays
	float **A = matrix(n);
	float **B = matrix(n);
	float **C = matrix(n);
	init(A, n);
	init(B, n);

	// Multiply
	double start = omp_get_wtime();
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			for (int k=0; k<n; k++)
				C[i][j] += A[i][k] * B[k][j];
	double stop = omp_get_wtime();

	matrix_free(A);
	matrix_free(B);
	matrix_free(C);
    return stop-start;
}

int main(int argc, char * argv[]) {
    int i, j;
    int n = N;
    time_t mytm;
	double time_var, temp, temp2;
    double mean, variance;
	int numTrials = 1;
	int max = omp_get_max_threads();
	double *serial_results = malloc(sizeof(double) * numTrials);
	double **omp_results = malloc(sizeof(double*) * max);
    for (i=0; i<numTrials; i++) omp_results[i] = malloc(sizeof(double) * numTrials);

    // print heading information
    time(&mytm);
    printf("Name:         Alan Cham\n");
    printf("Date:         %s", asctime(localtime(&mytm)));
    printf("Assignment:   Hw2 #2\n");
    printf("Thread limit: %d (on this machine)\n\n", max);

    printf("--------------------------------------------------------------------\n");
    printf("Part 1: Dependence of Runtime Mean and Variance on Number of Threads\n");
    printf("--------------------------------------------------------------------\n\n");

    // print heading information
    printf("Problem size N                     : %d\n", N);
    printf("Number of samples per test         : %d\n", numTrials);

    /* time serial case  */
    printf("\nRunning serial case %2d times       : ", numTrials); fflush(stdout);
    for (j=1; j<=numTrials; j++) {
        printf("x"); fflush(stdout);
        serial_results[j-1] = mm_serial(n);
    }

    /* time omp case */
    for (i=1; i<=max; i++) {
        printf("\nRunning %02d-thread omp case %d times: ", i, numTrials);
        for (j=1; j<=numTrials; j++) {
            printf("x"); fflush(stdout);
            omp_results[i-1][j-1] =  mm_omp(n, i);
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
    printf("Serial   : (%3.3lf, %lf, %3.3lf)\n", mean, variance, 1.0); fflush(stdout);
    
    // calculate omp mean and variance
    for(j=1; j<=max;j++) {
        for(time_var = 0, i=0; i<numTrials; i++) 
            time_var += omp_results[j-1][i];
        mean = time_var/numTrials;
        for(variance = 0, i=0; i<numTrials; i++)
            variance += mysqr(omp_results[j-1][i] - mean);
        variance = variance/numTrials;
        printf("%02d-thread: (%3.3lf, %lf, %3.3lf)\n", j, mean, variance, mean/temp); fflush(stdout);
    }

    printf("\n---------------------------------------------------------------\n");
    printf("Part 2: Dependence of Runtime Mean and Variance on Problem Size\n");
    printf("---------------------------------------------------------------\n\n");

    printf("The following omp timing results use %d threads:\n\n", bound(max/2)); fflush(stdout);
    for (i=1; i<= 10*N; i*=10) {
        // print heading information
        n = i;
        printf("Problem size N              : %d\n", i); fflush(stdout);
        printf("Running serial case %02d times: ", numTrials); fflush(stdout);

        // print progress update during multiplication kernel
        for(j=1; j<=numTrials; j++) {
            printf("x"); fflush(stdout);
            serial_results[j-1] = mm_serial(n);
        }

        // compute mean and variance
        for(time_var = 0, j=1; j<=numTrials; j++) 
            time_var += serial_results[j-1];
        temp = mean = time_var/numTrials;
        for(variance = 0, j=0; j<numTrials; j++) 
            variance += mysqr(serial_results[j] - mean);
        temp2 = variance = variance/numTrials;

        // print progress update during multiplication kernel
        printf("\nRunning omp case %02d times   : ", numTrials); fflush(stdout);
        for(j=1; j<=numTrials; j++) {
            printf("x"); fflush(stdout);
            omp_results[bound(max/2) - 1][j-1] = mm_omp(n, bound(max/2));
        }

        // compute mean and variance
        for(time_var = 0, j=1; j<=numTrials; j++) 
            time_var += omp_results[bound(max/2)-1][j-1];
        mean = time_var/numTrials;
        for(variance = 0, j=0; j<numTrials; j++) 
            variance += mysqr(omp_results[bound(max/2)-1][j] - mean);
        variance = variance/numTrials;

        // print results summary
        printf("\nSerial (mean, variance)     : %3.3lf, %lf\n", temp, temp2); fflush(stdout);
        printf("%02d-thread (mean, variance)  : %3.3lf, %lf\n", bound(max/2), mean, variance); fflush(stdout);
    	printf("OMP Time Ratio to Serial    : %3.3lf\n\n", mean/temp); fflush(stdout);
    }

    free(omp_results);
    free(serial_results);
    return 0;
}

