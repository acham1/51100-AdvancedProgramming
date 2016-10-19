/** Alan Cham
  * HW2 Q3 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 500

typedef enum command {ADD, DELETE, FIND, PRINT, IGNORE, EXCESS, OTHER} COMMAND;

void print_heading(void);
COMMAND load_command(char* command_text, char* word, char* definition);

int main(int argc, char* argv[]) {
    char word[MAX_LEN + 1];
    char definition[MAX_LEN + 1];
    char command_text[MAX_LEN + 1];
    clock_t start, end;
    COMMAND new_command;

    print_heading();
    start = clock();
    while (!feof(stdin)) {
        new_command = load_command(command_text, word, definition);
        switch (new_command) {
        case ADD:
            if (!strlen(word)) {
                printf("Error: no word detected.\n");
            } else if (definition[0] != '"' || definition[strlen(definition) - 1] != '"') {
                printf("Error: definition must be enclosed by quotation marks.\n");
            } else {
                printf("Adding word %s with definition %s.\n", word, definition);
            }
            break;
        case DELETE:
            if (!strlen(word)) {
                printf("Error: no word detected.\n");
            } else {
                printf("Deleting word %s.\n", word);
            }
            break;
        case FIND:
            if (!strlen(word)) {
                printf("Error: no word detected.\n");
            } else {
                printf("Finding word %s.\n", word);
            }
            break;
        case PRINT:
            printf("Printing dictionary.\n");
            break;
        case IGNORE:
            break;
        case EXCESS:
            printf("Error: excessive input length (limit %d chars).\n", MAX_LEN);
            break;
        default:
            printf("Error: %s is not a recognized command.\n", command_text);
            break;
        }
    }
    end = clock();
    printf("\nTotal Runtime: %lf\n", (double) (start-end)/CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}

COMMAND load_command(char* command_text, char* word, char* definition) {
    int i = 0, j = 0, k = 0;
    COMMAND new_command = OTHER;
    char c;

    printf("%% ");
    while (isspace(c = fgetc(stdin)) && c != '\n');
    if (feof(stdin) || c == '\n') {
        printf("%s", c == '\n' ? "" : "\n");
        return IGNORE;
    }
    // get first word
    while (c != EOF && !isspace(c) && i < MAX_LEN) {
        command_text[i++] = c;
        c = fgetc(stdin);
    }
    if (i == MAX_LEN && !isspace(c) && c != EOF) {
        while ((c = fgetc(stdin)) != EOF && c != '\n');
        printf("%s", c == '\n' ? "" : "\n");
        return EXCESS;
    } else {
        command_text[i++] = '\0';
    }
    // process first word
    if (strstr(command_text, "\\") == command_text) {
        return IGNORE;
    } else if (!strcmp("add", command_text)) {
        new_command = ADD;
    } else if (!strcmp("delete", command_text)) {
        new_command = DELETE;
    } else if (!strcmp("find", command_text)) {
        new_command = FIND;
    } else if (!strcmp("print", command_text)) {
        while ((c = fgetc(stdin)) != EOF && c != '\n');
        return PRINT;
    }
    // get second word
    while (c != '\n' && !feof(stdin) && isspace(c)) c = fgetc(stdin);
    while (c != '\n' && !feof(stdin) && j < MAX_LEN && !isspace(c)) {
        word[j++] = c;
        c = fgetc(stdin);
    }
    if (j == MAX_LEN && !isspace(c) && c != EOF) {
        while ((c = fgetc(stdin)) != EOF && c != '\n');
        printf("%s", c == '\n' ? "" : "\n");
        return EXCESS;
    } else {
        word[j++] = '\0';
    }
    // get third word
    while (c != '\n' && !feof(stdin) && isspace(c)) c = fgetc(stdin);
    if (c != '\n' && !feof(stdin)) word[j++] = c;
    while (c != '\n' && !feof(stdin) && j < MAX_LEN && (c = fgetc(stdin)) != '"') {
        word[j++] = c;
    }
    if (j == MAX_LEN && !isspace(c) && c != EOF) {
        while ((c = fgetc(stdin)) != EOF && c != '\n');
        printf("%s", c == '\n' ? "" : "\n");
        return EXCESS;
    } else {
        if (c != '\n' && !feof(stdin)) word[j++] = c;
        word[j++] = '\0';
    }
    if (c != '\n' && c != EOF) {
        while ((c = fgetc(stdin)) != EOF && c != '\n');
        printf("%s", c == '\n' ? "" : "\n");
    }
    return new_command;
}

void print_heading(void) {
    printf("Alan Cham\n");
    printf("p4.a: Simple Dictionary via Unbalanced Model 1 Binary Tree\n\n");
    printf("Acceptable case-sensitive commands (maximum line length %d chars): \n", MAX_LEN);
    printf("    %% add word \"definition\"\n");
    printf("    %% delete word\n");
    printf("    %% find word\n");
    printf("    %% print\n");
    printf("    %% // <rest of line to ignore>\n\n");
    printf("Begin here: \n");
}