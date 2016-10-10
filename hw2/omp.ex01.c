#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
	char D[20];
	memset(D, 50, sizeof(char) * 20);
	printf("Num threads available: %d\n", omp_get_max_threads());
	#pragma omp parallel	
	{
		int i;
		int sum = 0;
		for (i = 0; i < 20; i++) {
			sum += D[i];
			printf("%c ", D[i]);
		}
		printf("Thread %d computes %d\n", omp_get_thread_num(), sum);
	}
	return EXIT_SUCCESS;
}