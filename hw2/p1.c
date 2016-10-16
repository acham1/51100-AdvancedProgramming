/** Name:       Alan Cham
 *  Assignment: HW2 Q1 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define M 10000
#define N 10000
#define mysqr(x) ((x)*(x))
#define bound(x) ((x) < 1 ? 1 : (x))
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

    int i,j,max;
    int m = M;
    int n = N;
    double time_var, mean, variance;
    int numTrials = 2;
    time_t mytm;

    max = omp_get_max_threads();
    double *serial_results = (double *) calloc(numTrials, sizeof(double));
    double **omp_results = (double **) calloc(max, sizeof(double*));
    double *B_block = (double *) malloc(sizeof(double) * m * n);
    double *V_block = (double *) malloc(sizeof(double) * m * n);
    double **B = (double **) malloc(sizeof(double*) * m); 
    double **V = (double **) malloc(sizeof(double*) * m);

    time(&mytm);
    printf("Name:         Alan Cham\n");
    printf("Date:         %s", asctime(localtime(&mytm)));
    printf("Assignment:   Hw1 #1\n");
    printf("Thread limit: %d (on this machine)\n\n", max);

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
    for(i=0; i<max; i++) {
        omp_results[i] = (double *) calloc(numTrials, sizeof(double));
    }
    
    goto section2;

    printf("--------------------------------------------------------------------\n");
    printf("Part 1: Dependence of Runtime Mean and Variance on Number of Threads\n");
    printf("--------------------------------------------------------------------\n\n");

    /* time serial case  */
    printf("Running serial case %d times:\n", numTrials); fflush(stdout);
    printf("\tCollecting trial: "); fflush(stdout);
    for(j = 1; j <= numTrials; j++) {
        printf("x"); fflush(stdout);
        serial_results[j-1] = work_kernel_serial(B, V, m, n);
    }
    printf("\n\n"); fflush(stdout);

    /* time omp case */
    for(i=1; i <= max; i++) {
        printf("Running (%2d)-thread omp case %d times:\n", i, numTrials);
        printf("\tCollecting trial: ");
        for(j=1; j <= numTrials; j++) {
            printf("x"); fflush(stdout);
            omp_results[i-1][j-1] =  work_kernel_omp(B, V, m, n, i);
        }
        printf("\n"); fflush(stdout);
    }
    printf("\n"); fflush(stdout);

    printf("Summary of Results (mean(s), variance(s^2)):\n"); fflush(stdout);
    for(time_var = 0, i=0; i<numTrials; i++) {
        time_var += serial_results[i];
    }
    mean = time_var/numTrials;
    for(variance = 0, i=0; i<numTrials; i++) {
        variance += mysqr(serial_results[i] - mean);
    }
    variance = variance/numTrials;
    printf("\t     Serial: (%3.3lf, %lf)\n", mean, variance); fflush(stdout);
    for(j=1; j<=max;j++) {
        for(time_var = 0, i=0; i<numTrials; i++) {
            time_var += omp_results[j-1][i];
        }
        mean = time_var/numTrials;
        for(variance = 0, i=0; i<numTrials; i++) {
            variance += mysqr(omp_results[j-1][i] - mean);
        }
        variance = variance/numTrials;
        printf("\t(%2d)-thread: (%3.3lf, %lf)\n", j, mean, variance); fflush(stdout);
    }
    printf("\n");

    printf("---------------------------------------------------------------\n");
    printf("Part 2: Dependence of Runtime Mean and Variance on Problem Size\n");
    printf("---------------------------------------------------------------\n\n");

 section2:

    printf("The following omp timing results use %d threads:\n\n", bound(max/2)); fflush(stdout);
    for (i=1; i<=M; i*=10) {
        m = n = i;
        printf("Problem size: m = n = %d\n", i); fflush(stdout);
        printf("Running serial case %d times:\n", numTrials); fflush(stdout);
        printf("\tCollecting trial: "); fflush(stdout);
        for(j=1; j<=numTrials; j++) {
            printf("x"); fflush(stdout);
            serial_results[j-1] = work_kernel_serial(B, V, m, n);
        }
        for(time_var = 0, j=1; j<=numTrials; j++) {
            time_var += serial_results[j-1];
        }
        mean = time_var/numTrials;
        for(variance = 0, j=0; j<numTrials; j++) {
            variance += mysqr(serial_results[j] - mean);
        }
        variance = variance/numTrials;
        printf("\n\t     Serial: (%3.3lf, %lf)\n", mean, variance); fflush(stdout);

        printf("Running omp case %d times:\n", numTrials); fflush(stdout);
        printf("\tCollecting trial: "); fflush(stdout);
        for(j=1; j<=numTrials; j++) {
            printf("x"); fflush(stdout);
            omp_results[bound(max/2) - 1][j-1] = work_kernel_omp(B, V, m, n, bound(max/2));
        }
        for(time_var = 0, j=1; j<=numTrials; j++) {
	  time_var += omp_results[bound(max/2)-1][j-1];
        }
        mean = time_var/numTrials;
        for(variance = 0, j=0; j<numTrials; j++) {
	  variance += mysqr(omp_results[bound(max/2)-1][j] - mean);
        }
        variance = variance/numTrials;
        printf("\n\t(%2d)-thread: (%3.3lf, %lf)\n\n", bound(max/2), mean, variance); fflush(stdout);
    }

    /* Free memory*/
    for(i=0; i<max; i++) free(omp_results[i]);
    free(serial_results);
    free(omp_results);
    free(B_block);
    free(V_block);
    free(B);
    free(V);

    return 0;

}

