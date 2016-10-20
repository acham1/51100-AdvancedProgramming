#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <p4_tree.h>

typedef Node Dictionary;

Dictionary* create_dictionary(void);

// return 1 if problem, 0 otherwise
int add_word(Dictionary* dic, char* word, char* definition);

// find word in dic and store definition in def
// return 1 if problem, 0 otherwise
int find_word(Dictionary* dic, char* word, char* def);

// return 1 if problem, 0 otherwise
int print_dict(Dictionary* dic);

// return 1 if problem, 0 otherwise
int delete_word(Dictionary* dic, char* word);

// return 1 if problem, 0 otherwise
int free_dictionary(Dictionary* dic);

// return 1 is str1 is alphabetically later
// return 0 if str1 is equal to str2
// return -1 if str1 is alphabetically earlier
int word_cmp(const void* str1, const void* str2);

#endif