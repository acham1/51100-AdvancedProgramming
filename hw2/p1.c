/** Name:       Alan Cham
 *  Assignment: HW2 Q1 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define M 10000
#define N 10000

// Added argument t for number of threads to use
double work_kernel_omp(double **U, double **V, int m, int n, int t)
{
    int i,j;
    double a = 1.0, b = 0.5, c;

    double start = omp_get_wtime();
    for( i=1; i < (m-1); i++) {
#pragma omp parallel for num_threads(t) schedule(static) firstprivate(m, n, U, V)
        for( j=1; j < (n-1); j++) {
            V[i][j] = ( a * (U[i+1][j] + U[i-1][j]) ) +
                      ( b * (U[i][j+1] + U[i][j-1]) ) +
                      ( (1 - (2*a) - (2*b)) * U[i][j] );
        }
    }
    double stop = omp_get_wtime();

    return stop-start;    
}

double work_kernel_serial(double **U, double **V, int m, int n)
{
    int i,j;
    double a = 1.0, b = 0.5, c;

	double start = omp_get_wtime();
    for( i=1; i < (m-1); i++)
        for( j=1; j < (n-1); j++)
        {
            V[i][j] = ( a * (U[i+1][j] + U[i-1][j]) ) +
                      ( b * (U[i][j+1] + U[i][j-1]) ) +
                      ( (1 - (2*a) - (2*b)) * U[i][j] );
        }
	double stop = omp_get_wtime();

    return stop-start;
}

int main(int argc, char * argv[])
{

    int i,j;
    int m = M;
    int n = N;
    double time, temp;
    int numTrials = 10;

    double *thread_results = (double *) calloc(omp_get_num_threads(), sizeof(double));
    double *B_block = (double *) malloc(sizeof(double) * m * n);
    double *V_block = (double *) malloc(sizeof(double) * m * n);
    double **B = (double **) malloc(sizeof(double*) * m); 
    double **V = (double **) malloc(sizeof(double*) * m);

    for(i=0; i<m; i++){
        B[i] = B_block + n*i; 
        V[i] = B_block + n*i; 
    }

    /* Initialize arrays */
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            B[i][j] = i*n + j;
        }
    }

    /* time serial case  */
    printf("Running serial case 10 times:\n");
    for(time = 0, j = 1; j <= numTrials; j++) {
      temp = work_kernel_serial(B, V, m, n);
      time += temp;
      //      printf("\tIteration %d: %lf s\n", j, temp);
    }
    printf("Average serial time: %lf seconds\n\n", time/numTrials);

    /* time omp case */
    printf("Running omp case 10 times:\n");
    for(i=1; i <= omp_get_max_threads(); i*=2) {
      time = 0;
      for(j=0; j < numTrials; j++) {
	temp =  work_kernel_omp(B, V, m, n, i);
	time += temp;
	printf("\tIteration %d using %d threads: %lf\n", j+1, i, temp);
      }
      printf("Average %d thread time: %lf\n", i, time/numTrials);
    }
    printf("\n");

    /* Free memory*/
    free(thread_results);
    free(B_block);
    free(V_block);
    free(B);
    free(V);

    return 0;

}

