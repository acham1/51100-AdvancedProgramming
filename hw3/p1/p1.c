/** Alan Cham
  * MPCS 51100
  * November 13, 2016
  * Homework 3, p1 */

#include "p1.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD 50 /*including terminating '\0'*/
#define MAX_DEF 500 /*including terminating '\0'*/
#define MAX_BUFFER 100

int get_command(char* cmd, char* arg1, char* arg2, char* mssg);
void print_heading(void);
void ungetch(char prev); 
int getch(void);

char buffer[MAX_BUFFER];
int bufferpos = 0;

int main(void) {
    char cmd[MAX_WORD];
    char arg1[MAX_DEF];
    char arg2[MAX_DEF];
    char mssg[MAX_DEF];
    int errorsig;

    print_heading();
    while (!feof(stdin)) {
        if (errorsig = get_command(cmd, arg1, arg2, mssg)) {
            printf("error: %s\n");
            continue;
        }


    }
    return EXIT_SUCCESS;
}

// return 1 if problem getting command
int get_command(char* command, char* word, char* defn) {
    return 0;
}

void print_heading(void) {
    printf("Welcome to hw3 p1 dictionary. The following operations are supported:\n");
    printf("%%find [key]\n");
    printf("%%delete [key]\n");
    printf("%%insert [key]\n");
    printf("%%find [key1] [key2]\n");
    printf("%%print\n");
    printf("%%read [filename]\n");
}

void ungetch(char prev) {
    if (bufferpos < MAX_BUFFER) {
        buffer[bufferpos++] = prev;
    } else {
        printf("error: exceeded max ungetch buffer\n");
    }
}

int getch(void) {
    if (bufferpos > 0) {
        return buffer[--bufferpos];
    } else {
        return getc(stdin);
    }
}