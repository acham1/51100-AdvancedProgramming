/** Alan Cham
  * HW2 Q4 */

#include <p4a_dictionary.h>
#include <p4a_tree.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// return NULL if problem
Dictionary* create_dictionary(void) {
    return create_tree();
}

// return 1 if problem, 0 otherwise
int add_word(Dictionary* dic, char* word, char* definition) {
    int result;
    char* new_word, * new_def;

    new_word = malloc(sizeof(char) * (strlen(word)+1));
    memcpy(new_word, word, strlen(word)+1);
    new_def = malloc(sizeof(char) * (strlen(definition) + 1));
    memcpy(new_def, definition, strlen(definition)+1);
    result = insert_node(dic, new_word, new_def, word_cmp);
    if (result) {
        free(new_word);
        free(new_def);
    }
    return result;
}

// return 1 if problem, 0 otherwise
// find word in dic and store definition in def
int find_word(Dictionary* dic, char* word, char* def) {
    char* retrieved = find_obj(dic, word, word_cmp);
    if (!retrieved) {
        return 1;
    } else {
        memcpy(def, retrieved, strlen(retrieved)+1);
    }
    return 0;
}

// return 1 if problem, 0 otherwise
int print_dict(Dictionary* dic) {
    if (dic->right == NULL) {
        if (dic->left != NULL) {
            printf("> %s: %s\n", (char*) dic->key, (char*) dic->left);
        }
    } else {
        print_dict(dic->left);
        print_dict(dic->right);
    }
    return 0;
}

// return 1 if problem, 0 otherwise
int delete_word(Dictionary* dic, char* word) {
    return delete_node(dic, word, word_cmp);    
}

// return 1 if problem, 0 otherwise
int free_dictionary(Dictionary* dic) {
    return free_tree(dic);
}

// return 1 is str1 is alphabetically later
// return 0 if str1 is equal to str2
// return -1 if str1 is alphabetically earlier
int word_cmp(const void* str1, const void* str2) {
    return strcmp((char*) str1, (char*) str2);
}