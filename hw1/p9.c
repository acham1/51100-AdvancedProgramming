/* ==============================================================================

	9. File Read In - p9.c	

	Write a function (not main) named read_file that reads a text
	file into an array of strings. In C one way to implement this is
	as an array of array of char of fixed length. This is declared as	

	  char text[MAX_LINES][MAX_CHAR_PER_LINE]	

	Where MAX_LINES and MAX_CHAR_PER_LINE are #define preprocessor macros.	

	Write a test main that calls tests read_file (remember to call file
	p9.c) and prints contents to standard out:	

	PROMPT>> ./p9 <input_file_name>
	(input file printed here)
	(program ends)	

	For the purposes of this problem, please #define MAX_LINES to 1000 and 
	MAX_CHAR_PER_LINE to 1000.

============================================================================== */

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 1000
#define MAX_CHAR_PER_LINE 1000

int read_file(FILE * stream, char storage[][MAX_CHAR_PER_LINE]) {
	int numlines = 0;
	while (!feof(stream) && numlines < MAX_LINES &&
		fgets(storage[numlines], MAX_CHAR_PER_LINE + 1, stream)) {
		numlines++;
	}
	return numlines;
}

int main(int argc, char *argv[]) {
	char text[MAX_LINES][MAX_CHAR_PER_LINE];
	FILE * fpointer = fopen(argv[1], "r");
	int i = 0, numlines = read_file(fpointer, text);

	while (i < numlines) printf("%s", text[i++]);
	fclose(fpointer);
	return EXIT_SUCCESS;
}