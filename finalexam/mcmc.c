#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define START 1
#define END 2
#define NUM_SAMPLES 10000
#define NUM_INCREMENTS 10000

double normalization_coeff;
double** Q;

// return the value of ln x^2
double f(double x) {
    return log(x * x);
}

// return e^-x after normalization
double normed_boltzman(double x) {
    if (x < START || x > END) {
        return 0;
    }
    return exp(-x) / normalization_coeff;
}

double mcmc_sample(double x) {
    double r, total;
    int i, j;

    i = 0;
    total = 0;
    j = trunc((x-START)/ (END-START) * NUM_INCREMENTS);
    r = (double) rand() / RAND_MAX;
    while (r > total) {
        total += Q[j][i++];
    }
    return START + (double) --i / NUM_INCREMENTS;
}

int main(void) {
    double total, x, h, integral, a, newx, r;

    srand(time(NULL));
    normalization_coeff = exp(-START) - exp(-END);
    Q = malloc(sizeof(double*) * NUM_INCREMENTS);
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        Q[i] = malloc(sizeof(double) * NUM_INCREMENTS);
        for (int j = 0; j < NUM_INCREMENTS; j++) {
            Q[i][j] = (double) 1 / NUM_INCREMENTS;
        }
    }
    x = START;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        newx = mcmc_sample(x);
        r = (double) rand() / RAND_MAX;
        a = f(newx)/f(x);
        if (a >= 1) {
            x = newx;
        } else {
            if (r <= a) {
                x = newx;
            }
        }
        h = f(x) / normed_boltzman(x);
        total += h;
    }
    integral = total/NUM_SAMPLES;
    printf("Estimate is %lf\n", integral);
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        free(Q[i]);
    }
    free(Q);
    return EXIT_SUCCESS;
}
