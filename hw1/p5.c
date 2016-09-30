/* ==============================================================================
5 - 2D Contiguous Array - p5.c

Redo (4) now enforcing that the entire allocated block of data
be contiguous in memory -- ie that each allocated block of size n
doubles is adjacent to its neighbor block. The prototype should be the same:
      
	  double **dmatrix(size_t m, size_t n);

I.e., for an array of 4 x 4, we should be able to access the last element
with your returned double ** pointer using 1-D or 2-D as:

double ** ptr = dmatrix(4, 4);

ptr[3][3] = 15.0;

if( ptr[3][3] == 15.0 && ptr[0][ (4*4) - 1 ] == 15.0 )
	printf("Passed Contiguous check\n");


Above, we can see that both 2D indexing (ptr[3][3]) and 1D indexing
(ptr[0][(4*4) - 1]) both work correctly, showing that our matrix
is indeed contiguous.

Now, write a test main that uses your dmatrix function to allocate
an array of dimension n x n (inputted via command line, argv[1]).
Have your test main fill this array with sequential values beginning
with 0. Then, print these values to standard out in matrix format in
using both 2D and 1D indexing.

Specifically, a sample run should look like:

PROMPT>> ./p5 4
Matrix with 1D indexing:
0.0 1.0 2.0 3.0
4.0 5.0 6.0 7.0
8.0 9.0 10.0 11.0
12.0 13.0 14.0 15.0

Matrix with 2D indexing: 
0.0 1.0 2.0 3.0
4.0 5.0 6.0 7.0
8.0 9.0 10.0 11.0
12.0 13.0 14.0 15.0
(program ends)

============================================================================== */

#include <stdio.h>
#include <stdlib.h>

double **dmatrix(size_t m, size_t n) {
	double *one_dim = malloc(sizeof(double) * m*n);
	double **two_dim = malloc(sizeof(double *) * m);
	while (m-- > 0) {
		two_dim[m] = one_dim + n*m;
	}
	return two_dim;
}

int main(int argc, char ** argv) {
	int row, col, index, n = atoi(argv[1]);
	double **matrix = dmatrix(n, n);

	printf("Matrix with 1D indexing:\n");
	for (index = 0; index < n*n; index++) {
		matrix[0][index] = (double) index;
		printf("%.1f ", matrix[0][index]);
		if (index > 0 && index % n == n - 1) {
			printf("\n");
		}
	}

	printf("\nMatrix with 2D indexing:\n");
	for (row = 0; row < n; row++) {
		for (col = 0; col < n; col++) {
			printf("%.1f ", matrix[row][col]);
		}
		printf("\n");
	}

	free(matrix[0]);
	free(matrix);
	return EXIT_SUCCESS;
}
