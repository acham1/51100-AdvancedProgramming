/* ==============================================================================

	8 - Alphabetizer - p8.c	

	Write a function that alphabetizes lines of text. The sort
	must be done by swapping the pointers themselves and not moving or copying the
	actual text. The function prototype must be:	

	       void alphabetize(char *text[], int nlines);	

	Write a test program to read lines from stdin, use alphabetize,
	and send the alphabetized list to stdout. Your program should continue
	reading lines from stdin until it receives EOF (this can be sent from
	the terminal using ctrl+D - or, you can redirect stdin from a file
	using <).	

	You can assume a maximum number of 500 lines and 200 chars per line.	

	For example:	

	if input file "students.txt" reads:	

	Fan, Aaron
	Sturt, Adam
	Chakravarty, Arnav
	Ali, Asad
	Sandman, Benjamin
	Cunningham, Bryce 
	Braun, Joseph 
	Mai, Conway 
	Du, Mu
	Tong, Jiayang
	Yang, Jinpu 
	O'Harrow, Joseph
	Liang, Junchi
	Mandava, Mayank
	Zhang, Mengyu
	Atanasov, Pero 
	Kramer, Scott 
	Liu, Sen
	Zhu, Wanqi
	Warner, Stephanie
	Wu, Yichen	

	Running your code should look like:	

	PROMPT>> ./p8 < students.txt
	Ali, Asad
	Atanasov, Pero 
	Braun, Joseph 
	Chakravarty, Arnav
	Cunningham, Bryce 
	Du, Mu
	Fan, Aaron
	Kramer, Scott 
	Liang, Junchi
	Liu, Sen
	Mai, Conway 
	Mandava, Mayank
	O'Harrow, Joseph
	Sandman, Benjamin
	Sturt, Adam
	Tong, Jiayang
	Warner, Stephanie
	Wu, Yichen
	Yang, Jinpu 
	Zhang, Mengyu
	Zhu, Wanqi

============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LEN 200
#define MAX_LINES 500

char **get_char_matrix(size_t m, size_t n) {
	char *one_dim = malloc(sizeof(double) * m*n);
	char **two_dim = malloc(sizeof(double *) * m);
	while (m-- > 0) {
		two_dim[m] = one_dim + n*m;
	}
	return two_dim;
}

void mergesort(char **lines, int rows) {
	int middle = (rows - 1)/2;
	int leftPos = 0, rightPos = middle + 1, tempPos = 0;
	char ** temp = malloc(sizeof(char *) * rows);

	if (rows < 2) return;
	mergesort(lines, middle + 1);	
	mergesort(lines + middle + 1, rows - (middle + 1));
	
	while (tempPos < rows) {
		if (leftPos == middle + 1) {
			temp[tempPos++] = lines[rightPos++];
		} else if (rightPos == rows) {
			temp[tempPos++] = lines[leftPos++];
		} else if (strcmp(lines[leftPos], lines[rightPos]) >= 0) {
			temp[tempPos++] = lines[rightPos++];
		} else {
			temp[tempPos++] = lines[leftPos++];
		}
	}

	while (rows-- > 0) lines[rows] = temp[rows];
	free(temp);
}

int main(int argc, char **argv) {
	int temp = 0, rows = 0;
	char **lines = get_char_matrix(MAX_LINES, MAX_LEN + 1);
	char *block = *lines;

	
	while (!feof(stdin) && rows < MAX_LINES && fgets(lines[rows], MAX_LEN + 1, stdin)) {
		rows++;
	}

	mergesort(lines, rows);
	while (temp < rows) {
		printf("%s", lines[temp++]);
	}

	free(block);
	free(lines);
	return EXIT_SUCCESS;
}