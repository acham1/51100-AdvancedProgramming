/* ==============================================================================

	1 - Integer Endianness - p1.c	

	Write a program that takes a single integer as input and flips its endianness.
	The integer should be a 4 byte (32 bit) integer (usually type 'int' in C). You 
	will need use bitshifting and the bitwise operators to accomplish this task.	

	Note that endianness is usually thought of in terms of byte ordering, not
	bit ordering. I.e, if we take the number 457,553 we should get the following
	bit patterns:  	

	Integer: 457553
	Little Endian Bit Pattern: 10001010 11011111 01100000 00000000
	Big Endian Bit Pattern:    00000000 01100000 11011111 10001010
	Integer: 1375405568	

	Your program should run as follows:	

	PROMPT>> ./p1 1
	16777216
	(program ends)	

	PROMPT>> ./p1 453
	-989790208
	(program ends)	

	PROMPT>> ./p1 12312
	405798912
	(program ends)

============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#define NUM_BYTES 4
#define LAST_BYTE_MASK 255
#define BYTE_SHIFT_FACTOR 256

int main(int argc, char ** argv) {
	unsigned int input = atoi(argv[1]);
	unsigned int output = 0;
	int bytes = 0;

	while (bytes++ < NUM_BYTES) {
		output *= BYTE_SHIFT_FACTOR;
		output += input & LAST_BYTE_MASK;
		input /= BYTE_SHIFT_FACTOR;
	}
	printf("%d\n", output);
	return EXIT_SUCCESS;	
}