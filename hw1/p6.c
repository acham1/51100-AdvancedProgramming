/* ==============================================================================
	6 - 3D Contiguous Array - p6.c	

	Redo (5) for a pointer to pointer to pointer to double (3D array of doubles) as:	

	      double ***d3darr(size_t l, size_t m, size_t n);	

	The allocation must be contiguous. I.e., for an array of 5 x 5 x
	5, we should be able to access the last element with your returned
	double *** pointer using 1-D or 3-D as:	

	double *** ptr = d3arr(5, 5, 5);	

	ptr[4][4][4] = 26.0;	

	if( ptr[4][4][4] == 26.0 && ptr[0][0][ (5*5*5) - 1 ] == 26.0 )
		printf("Passed Contiguous check\n");	

	Now, write a test main that uses your dmatrix function to allocate
	an array of dimension n x n x n (n inputted via command line, argv[1]).
	Have your test main fill this array with sequential values beginning
	with 0. Then, print these values to standard out in matrix format
	using both 3D and 1D indexing.	

	Specifically, a sample run should look like:	

	PROMPT>> ./p6 3
	Matrix with 1D indexing:
	0.0 1.0 2.0
	3.0 4.0 5.0
	6.0 7.0 8.0	

	9.0 10.0 11.0
	12.0 13.0 14.0
	15.0 16.0 17.0	

	18.0 19.0 20.0
	21.0 22.0 23.0
	24.0 25.0 26.0	

	Matrix with 3D indexing:
	0.0 1.0 2.0
	3.0 4.0 5.0
	6.0 7.0 8.0	

	9.0 10.0 11.0
	12.0 13.0 14.0
	15.0 16.0 17.0	

	18.0 19.0 20.0
	21.0 22.0 23.0
	24.0 25.0 26.0
	(program ends)

============================================================================== */

#include <stdio.h>
#include <stdlib.h>

double ***d3darr(size_t l, size_t m, size_t n) {
	int l_counter = l, m_counter = m;
	double *one_dim = malloc(sizeof(double) * l*m*n);
	double **two_dim = malloc(sizeof(double *) * l*m);
	double ***three_dim = malloc(sizeof(double **) * l);

	while (l_counter-- > 0) {
		three_dim[l_counter] = two_dim + l_counter*m;
		while (m_counter-- > 0) {
			three_dim[l_counter][m_counter] = one_dim + (l_counter*m*n) + (m_counter*n);
		}
		m_counter = m;
	}
	return three_dim;
}


int main(int argc, char ** argv) {
	int row, col, layer, index, n = atoi(argv[1]);
	double ***matrix = d3darr(n, n, n);

	printf("Matrix with 1D indexing:\n");
	for (index = 0; index < n*n*n; index++) {
		matrix[0][0][index] = (double) index;
		printf("%.1f ", matrix[0][0][index]);
		if (index > 0 && index % n == n - 1) {
			printf("\n");
			if (index % (n*n) == n*n - 1) {
				printf("\n");
			}
		}
	}

	printf("Matrix with 3D indexing:\n");
	for (layer = 0; layer < n; layer++) {
		for (row = 0; row < n; row++) {
			for (col = 0; col < n; col++) {
				printf("%.1f ", matrix[layer][row][col]);
			}
			printf("\n");
		}
		if (layer != n - 1) printf("\n");
	}

	free(matrix[0][0]);
	free(matrix[0]);
	free(matrix);
	return EXIT_SUCCESS;
}
