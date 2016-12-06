#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define START 1
#define END 2
#define NUM_SAMPLES 10000

double normalization_coeff;

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

double sample() {
    double u, x;
    u = (double) rand() / RAND_MAX;
    x = invert_boltzman_cdf(u);
    return x;
}
int main(void) {
    double total, x, h, integral;

    srand(time(NULL));
    normalization_coeff = exp(-START) - exp(-END);
    for (int i = 0; i < NUM_SAMPLES; i++) {
        x = sample();
        h = f(x) / normed_boltzman(x);
        total += h;
    }
    integral = total/NUM_SAMPLES;
    printf("Estimate is %lf\n", integral);
    return EXIT_SUCCESS;
}
