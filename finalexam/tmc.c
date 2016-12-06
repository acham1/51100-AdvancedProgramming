#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SAMPLES 10000
#define START 1
#define END 2

// return the value of ln x^2
double f(double x) {
    return log(x * x);
}

int main(void) {
    double total, x, integral;

    total = 0;
    srand(time(NULL));
    for (int i = 0; i < NUM_SAMPLES; i++) {
        x = (double) rand() / RAND_MAX * (END-START) + START;
        total += f(x);
    }
    integral = total * (END-START) / NUM_SAMPLES;
    printf("Integral estimate is %lf\n", integral);
    return EXIT_SUCCESS;
}
