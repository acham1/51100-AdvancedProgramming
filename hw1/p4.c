/* ==============================================================================

	4 - 2D Array - p4.c	

	Write a function that returns a pointer to a pointer to a double
	where the pointer points to a valid address of m pointers-to-double each
	of which points to a valid address of n doubles.	

	      double **dmatrix(size_t m, size_t n);	

	Then, write a test main that uses your dmatrix function to allocate
	an array of dimension n x n (inputted via command line, argv[1]).
	Have your test main fill this array with sequential values beginning
	with 0. Then, print these values to standard out in matrix format.
	Specifically, a sample run should look like:	

	PROMPT>> ./p4 4
	0.0 1.0 2.0 3.0
	4.0 5.0 6.0 7.0
	8.0 9.0 10.0 11.0
	12.0 13.0 14.0 15.0
	(program ends)

============================================================================== */

#include <stdio.h>
#include <stdlib.h>

double **dmatrix(size_t m, size_t n) {
	double ** matrix = malloc(m * sizeof(double *));
	while (m-- > 0) {
		matrix[m] = malloc(n * sizeof(double));
	}
	return matrix;
}

int main(int argc, char ** argv) {
	int row, col, n = atoi(argv[1]);
	double val = 0, ** matrix = dmatrix(n, n);

	for (row = 0; row < n; row++) {
		for (col = 0; col < n; col++) {
			matrix[row][col] = val++;
			printf("%.1f ", matrix[row][col]);
		}
		free(matrix[row]);
		printf("\n");
	}

	free(matrix);
	return EXIT_SUCCESS;
}