/* ==============================================================================

	2 - Floating Point Bit Pattern - p2.c	

	Write a program that prints the bit pattern of a float. To accomplish this
	task, you will need use bitshifting and the bitwise operators. What are
	the max and min values of a float on the platform you're using?	

	PROMPT>> ./p2 <input float>
	<output bit pattern (sign exponent mantissa)>
	(program ends)	

	PROMPT>> ./p2 19.86
	0 10000011 00111101110000101001000
	(program ends)	

	PROMPT>> ./p2 -19.86
	1 10000011 00111101110000101001000
	(program ends)	

	PROMPT>> ./p2 4.65e7
	0 10011000 01100010110001000101000
	(program ends)

============================================================================== */

/** I got the idea of casting the float to unsigned integer type from here:
	https://stackoverflow.com/questions/12342926/casting-float-to-int-bitwise-in-c */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#define BITS_IN_INT 32
#define SPACE1 1
#define SPACE2 9

int main(int argc, char ** argv) {
	float input = atof(argv[1]);
	void * myvoid = &input;
	unsigned int i = 0, myint = * (unsigned int * ) myvoid;

	while (i++ < BITS_IN_INT) {
		printf("%d", myint >> (BITS_IN_INT - i) & 1);
		if (i == SPACE1 || i == SPACE2) {
			printf(" ");
		}
	}
	printf("\n");

	return EXIT_SUCCESS;
}