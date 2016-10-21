/** Alan Cham
  * HW2 Q4 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <p4b_dictionary.h>
#define MAX_LEN 500

typedef enum command_ {
    ADD, DELETE, FIND, PRINT, IGNORE, EXCESS, EXIT, OTHER
} Command;

char burn_to_end(void);
void print_heading(void);
char get_string(char* destination, int maximum);
Command load_command(char* command_text, char* word, char* definition);

int main(int argc, char* argv[]) {
    int quit = 0;
    char word[MAX_LEN + 1];
    char definition[MAX_LEN + 1];
    char command_text[MAX_LEN + 1];
    clock_t start, end;
    Command new_command;
    Dictionary* D = create_dictionary();

    print_heading();
    start = clock();
    while (!feof(stdin) && !quit) {
        new_command = load_command(command_text, word, definition);
        if ((new_command == ADD || new_command == FIND || new_command == DELETE) 
            && !strlen(word)) {
            printf("> Error: no word detected.\n");
            continue;
        }
        
        switch (new_command) {
        case ADD:
            if (definition[0] != '"' || definition[strlen(definition) - 1] != '"' 
                || strlen(definition) < 2) {
                printf("> Error: definition must be enclosed by quotation marks.\n");
            } else {
                if (add_word(D, word, definition)) {
                    printf("> Failed. Word exists.\n");
                }
            }
            break;
        case DELETE:
            if (delete_word(D, word)) {
                printf("> Failed. Word not found. \n");
            }
            break;
        case FIND:
            if (find_word(D, word, definition)) {
                printf("> Failed. Word not found. \n");
            } else { 
                printf("> %s: %s\n", word, definition);
            }
            break;
        case PRINT:
            if (print_dict(D)) {
                printf("> Failed.\n");
            }
            break;
        case EXCESS:
            printf("> Error: excessive input length (limit %d chars).\n", MAX_LEN);
            break;
        case EXIT:
            printf("> Good-bye.\n");
            quit = 1;
            break;
        case IGNORE:
            break;
        default:
            printf("> Error: %s is not a recognized command.\n", command_text);
            break;
        }
    }
    end = clock();
    printf("\n==================================================================\n");
    printf("\nTotal Runtime: %lf\n\n", (double)(end-start)/CLOCKS_PER_SEC);

    free_dictionary(D);
    return EXIT_SUCCESS;
}

char burn_to_end(void) {
    char c;
    while (!feof(stdin) && (c = getchar()) != '\n');
    if (c != '\n') 
        printf("\n");
    return c;
}

// returns character after the last stored character
char get_string(char* destination, int maximum) {
    int i = 0;
    char c = EOF;

    while (!feof(stdin) && isspace(c = getchar()) && c != '\n');
    ungetc(c, stdin);
    while (!feof(stdin) && !isspace(c = getchar()) && c != EOF && c != '\n' && i < MAX_LEN) 
        destination[i++] = c;
    destination[i++] = '\0';
    return c;
}

Command load_command(char* command_text, char* word, char* definition) {
    Command new_command;
    int i = 0;
    char c;

    printf("\n%% ");
    // get first word
    c = get_string(command_text, MAX_LEN);
    ungetc(c, stdin);
    if (c != '\n' && !feof(stdin) && !isspace(c)) {
        burn_to_end();
        return EXCESS;
    } else if (!strcmp(command_text, "add")) {
        new_command = ADD;
    } else if (!strcmp(command_text, "find")) {
        new_command = FIND;
    } else if (!strcmp(command_text, "delete")) {
        new_command = DELETE;
    } else if ((c == '\n' && !strlen(command_text)) || strstr(command_text, "//") == command_text) {
        burn_to_end();
        return IGNORE;
    } else if (!strcmp(command_text, "print")) {
        burn_to_end();
        return PRINT;
    } else if ((!strlen(command_text) && c == EOF) || !strcmp(command_text, "exit")) {
        burn_to_end();
        return EXIT;
    } else if (!strlen(command_text) && (c == '\n' || c == EOF)) {
        printf(c == EOF ? "\n" : "");
        return IGNORE;
    } else {
        burn_to_end();
        return OTHER;
    }

    // get second word
    c = get_string(word, MAX_LEN);
    if (feof(stdin)) {
        word[0] = '\0';
        definition[0] = '\0';
        printf("\n");
        return new_command;
    }
    ungetc(c, stdin);
    if (c != '\n' && c != EOF && !isspace(c)) {
        burn_to_end();
        return EXCESS;
    } else if (new_command != ADD) {
        burn_to_end();
        return new_command;
    }

    // get third word(s)
    while (!feof(stdin) && isspace(c = getchar()) && c != '\n');
    if (c != EOF && c != '\n') {
        definition[i++] = c;
        while ((c = getchar()) != EOF && c != '\n' && c != '"' && i < MAX_LEN) {
            definition[i++] = c;
        }
        if (c == '"' && i < MAX_LEN) {
            definition[i++] = c;
        } else if (c != EOF && c != '\n' && i == MAX_LEN) {
            burn_to_end();
            return EXCESS;
        }
        definition[i++] = '\0';
        if (c != EOF) {
            ungetc(c, stdin);
            burn_to_end();
        }
    } else {
        definition[0] = '\0';
    }
    return ADD;
}

void print_heading(void) {
    printf("\n==================================================================\n\n");
    printf("Alan Cham\n");
    printf("p4.b: Simple Dictionary via Balanced Model 1 Binary Tree\n\n");
    printf("Acceptable case-sensitive commands (maximum line length %d chars): \n", MAX_LEN);
    printf("    %% add word \"definition\"\n");
    printf("    %% delete word\n");
    printf("    %% find word\n");
    printf("    %% print\n");
    printf("    %% exit\n");
    printf("    %% // <rest of line to ignore>\n");
    printf("\n==================================================================\n");
    printf("\nBegin here:\n");
}
