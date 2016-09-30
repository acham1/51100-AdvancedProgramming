/* ==============================================================================

7 - Array Performance - p7.c

Write a program that tests the performance difference between three different 2D
array of doubles implementation:

	a) Statically allocated 2D array
	b) Dynamically allocated 2D array, contiguous in memory
	c) Dynamically allocated 2D array, distributed through memory

Let the dimensions of each array be m = n = 1000, so that each array will 
have 10^6 elements. Pass the array to the provided kernel functions and time each array. You 
may find functions in the `time.h’ library to be helpful. The structure of the program 
will look like:

// See below

============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 1000
#define N 1000

/* returns dynamically allocated 2D array, contiguous in memory */
double **get_dynamic_contiguous(size_t m, size_t n) {
	double *one_dim = malloc(sizeof(double) * m*n);
	double **two_dim = malloc(sizeof(double *) * m);
	while (m-- > 0) {
		two_dim[m] = one_dim + n*m;
	}
	return two_dim;
}

/* returns dynamically allocated 2D array, distributed in memory */
double **get_dynamic_distributed(size_t m, size_t n) {
	double ** matrix = malloc(m * sizeof(double *));
	while (m-- > 0) {
		matrix[m] = malloc(n * sizeof(double));
	}
	return matrix;
}

void work_kernel_dynamic(double **U, int m, int n)
{
	int i,j;
	double a = 1.0, b = 0.5, c;

	for( i=1; i < (m-1); i++)
		for( j=1; j < (n-1); j++)
		{
			c = ( a * (U[i+1][j] + U[i-1][j]) ) +
		            ( b * (U[i][j+1] + U[i][j-1]) ) +
	                    ( (1 - (2*a) - (2*b)) * U[i][j] );
		}

	return;
}

void work_kernel_static(double U[M][N], int m, int n)
{
	int i,j;
	double a = 1.0, b = 0.5, c;

	for( i=1; i < (m-1); i++)
		for( j=1; j < (n-1); j++)
		{
			c = ( a * (U[i+1][j] + U[i-1][j]) ) +
		            ( b * (U[i][j+1] + U[i][j-1]) ) +
	                    ( (1 - (2*a) - (2*b)) * U[i][j] );
		}

	return;
}



int main(int argc, char * argv[])
{
	int m = 1000;
	int n = 1000;
	time_t start, end;
	double time_A, time_B, time_C;

	/* Declare and allocate your arrays A,B,C */
	double A[M][N];
	double **B = get_dynamic_contiguous(m, n);
	double **C = get_dynamic_distributed(m, n);
	/* Initialize arrays */

	/* time A */
	start = time(NULL);
	work_kernel_static( A, m, n);
	end = time(NULL);
	time_A = difftime(end, start);

	/* time B */
	start = time(NULL);
	work_kernel_dynamic( B, m, n);
	end = time(NULL);
	time_B = difftime(end, start);

	/* time C */
	start = time(NULL);
	work_kernel_dynamic( C, m, n);
	end = time(NULL);
	time_C = difftime(end, start);

	/* Print out timing to stdout in seconds for each array */
	printf("A: %fs\n", time_A);
	printf("B: %fs\n", time_B);
	printf("C: %fs\n", time_C);

	/* Free memory*/
	free(B[0]);
	free(B);

	while (m-- > 0) free(C[m]);
	free(C);	
	return 0;

}
