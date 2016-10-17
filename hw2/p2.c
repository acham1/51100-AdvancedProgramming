#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 1000

float ** matrix( int n )
{
	float *data = (float *) calloc( n*n, sizeof(float) );
	float **M  = (float **) malloc( n  * sizeof(float*));

	for( int i = 0; i < n; i++ )
		M[i] = &data[i*n];

	return M;
}

void matrix_free( float ** M)
{
	free(M[0]);
	free(M);
}

void init(float ** M, int n)
{
	for( int i = 0; i < n; i++ )
		for( int j = 0; j < n; j++ )
			M[i][j] = (float) ( rand() % 100 );
}

/* Perform matrix multiplication using OpenMP */
double mm_omp(int n) {
	// Allocate arrays
	float ** A = matrix(n);
	float ** B = matrix(n);
	float ** C = matrix(n);
	init(A,n);
	init(B,n);

	double start = omp_get_wtime();
	// Multiply
#pragma omp parallel for firstprivate(i,j,k,A,B,C,n), schedule(static)
	for( int i = 0; i < n; i++ )
		for( int j = 0; j < n; j++ )
			for( int k = 0; k < n; k++ )
				C[i][j] += A[i][k] * B[k][j];
	double stop = omp_get_wtime();

	matrix_free(A);
	matrix_free(B);
	matrix_free(C);

    return stop-start;
}

/* Perform matrix multiplication serially */
double mm_serial( int n ) {
	// Allocate arrays
	float ** A = matrix(n);
	float ** B = matrix(n);
	float ** C = matrix(n);
	init(A,n);
	init(B,n);

	double start = omp_get_wtime();
	// Multiply
	for( int i = 0; i < n; i++ )
		for( int j = 0; j < n; j++ )
			for( int k = 0; k < n; k++ )
				C[i][j] += A[i][k] * B[k][j];
	double stop = omp_get_wtime();

	matrix_free(A);
	matrix_free(B);
	matrix_free(C);

    return stop-start;
}

int main(int argc, char * argv[]) {
    int i,j;
    int n = N;
    time_t mytm;

    // print heading information
    time(&mytm);
    printf("Name:         Alan Cham\n");
    printf("Date:         %s", asctime(localtime(&mytm)));
    printf("Assignment:   Hw2 #2\n");
    printf("Thread limit: %d (on this machine)\n\n", max);

	double time = mm_serial(n);
	printf("Time for serial: %lf seconds\n", time);

    return 0;
}

