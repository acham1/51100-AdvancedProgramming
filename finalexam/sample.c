#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define START 1
#define END 2

double normalization_coeff;

// return e^-x after normalization
double normed_boltzman(double x) {
    if (x < START || x > END) {
        return 0;
    }
    return exp(-x) / normalization_coeff;
}

// returns cdf of boltzman e^-x, via integrate from START to x
double boltzman_cdf(double x) {
    if (x < START) {
        return 0;
    } else if (x > END) {
        return 1;
    } else {
        return (-exp(-x) + exp(-START))/normalization_coeff;
    }
}

double invert_boltzman_cdf(double u) {
    if (u < 0) {
        return START;
    } else if (u > 1) {
        return END;
    } else {
        return -log(-(u*normalization_coeff - exp(-START)));
    }
}

int main(void) {
    double u, sample;

    srand(time(NULL));
    normalization_coeff = exp(-START) - exp(-END);
    u = (double) rand() / RAND_MAX;
    sample = invert_boltzman_cdf(u);
    printf("Sample is %lf\n", sample);
    return EXIT_SUCCESS;
}
