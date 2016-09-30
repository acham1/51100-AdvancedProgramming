/* ==============================================================================

	10. - Repeat Counter - p10.c	

	Write a program that lists all the words in a file that contain
	a repeated letter (two consecutive occurrences of same letter). Include the number of occurrences of each word. Note that the file can contain any words as well
	as the common punctuations marks ‘.’, ‘;’, ‘?’, ‘;’, ‘:’, ‘-‘.	

	PROMPT>> ./p10 <input_file_name>
	better : 3
	butter : 1
	tall : 1
	(program ends)	

	You may assume that the maximum number of words in a file is 1000.

============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

typedef struct word Word;

struct word {
	char * string;
	int occurrences;
	Word * leftChild;
	Word * rightChild;
};

Word * getword(FILE * fptr) {
	static int default_word_len = 5;
	char * nextword = malloc(sizeof(char) * default_word_len);
	char * expanded_mem;
	char temp;
	int pos = 0;
	Word * output = malloc(sizeof(Word));

	while (!feof(fptr) && !isalnum(temp = fgetc(fptr)));
	if (feof(fptr)) return NULL;

	nextword[pos++] = tolower(temp);
	while (isalnum(temp = fgetc(fptr))) {
		nextword[pos++] = tolower(temp);
		if (pos >= default_word_len) {
			default_word_len *= 2;
			expanded_mem = malloc(sizeof(char) * default_word_len);
			memcpy(expanded_mem, nextword, sizeof(char) * pos);	
			free(nextword);
			nextword = expanded_mem;
		}
	} 
	nextword[pos++] = '\0';
	
	output->string = nextword;
	output->occurrences = 1;
	output->leftChild = NULL;
	output->rightChild = NULL;
	return output;	
}

int has_repeat(char * string) {
	int pos = 0;
	int len = strlen(string);

	while (pos++ < len) {
		if (strchr(string + pos, string[pos - 1])) return 1;
	}
	return 0;
}

void free_tree(Word *root) {
	if (root == NULL) return;
	free_tree(root->leftChild);
	free_tree(root->rightChild);
	free(root->string);
	free(root);
}

void insert_node(Word * newword, Word * root) {
	int diff = strcmp(root->string, newword->string);
	if (!diff) {
		root->occurrences++;
		free_tree(newword);
	} else if (diff < 0) {
		if (root->rightChild == NULL) {
			root->rightChild = newword;
		} else {
			insert_node(newword, root->rightChild);
		}
	} else {
		if (root->leftChild == NULL) {
			root->leftChild = newword;
		} else {
			insert_node(newword, root->leftChild);
		}
	}
}

int print_tree(Word * root) {
	int seen = 0;
	if (root == NULL) return 0;
	seen += print_tree(root->leftChild);
	printf("%s : %d\n", root->string, root->occurrences);
	seen += print_tree(root->rightChild);
	return seen + root->occurrences;
}

int main(int argc, char * argv[]) {
	FILE * fpointer = fopen(argv[1], "r");
	int words_seen = 0;
	Word * root, * temp;

	while ((temp = getword(fpointer))) {
		if (!has_repeat(temp->string)) {
			free_tree(temp);
			continue;
		} else if (!words_seen) {
			root = temp;
		} else {
			insert_node(temp, root);
		}
		words_seen++;
	}			

	free_tree(root);
	return EXIT_SUCCESS;
}