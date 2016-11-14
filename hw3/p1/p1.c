/** Alan Cham
  * MPCS 51100
  * November 13, 2016
  * Homework 3, p1 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashmap.h"

#define MAX_WORD 50 /*including terminating '\0'*/
#define MAX_DEF 500 /*including terminating '\0'*/
#define MAX_BUFFER 100
#define LOG_NAME "p1_log.txt"

typedef enum {
    FIND1, FIND2, DELETE, INSERT, PRINT, READ, ERROR
} Command;

Command get_command(char* arg1, char* arg2, char* mssg);
void print_heading(void);
void ungetch(char prev); 
int getch(void);

char buffer[MAX_BUFFER];
int bufferpos = 0;

int main(void) {
    clock_t start, end;
    char cmd[MAX_WORD];
    char arg1[MAX_DEF];
    char arg2[MAX_DEF];
    char mssg[MAX_DEF];
    Command cmd;

    print_heading();
    start = clock();
    while (!feof(stdin)) {
        switch(cmd = get_command(arg1, arg2, mssg)) {
            case FIND1:
                break;
            case FIND2:
                break;
            case DELETE:
                break;
            case INSERT: 
                break;
            case PRINT:
                break;
            case READ:
                break;
            case ERROR:
                printf("error: %s", error);
                break;
            default:
                printf("special error: invalid Command value\n");
        }
    }
    end = clock();
    printf("---------------------------------------------------------\n\n");
    printf("Total processor time consumed: %lf", (double) (end-start) / CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}

// return 1 if problem getting command
Command get_command(char* arg1, char* arg2, char* mssg) {
    Command cmd = ERROR;

    return cmd;
}

void print_heading(void) {
    printf("Welcome to hw3 p1 dictionary. The following operations are supported:\n");
    printf("%%find [key]\n");
    printf("%%delete [key]\n");
    printf("%%insert [key]\n");
    printf("%%find [key1] [key2]\n");
    printf("%%print\n");
    printf("%%read [filename]\n");
    printf("\nPlease enter your operations below: \n");
    printf("---------------------------------------------------------\n\n");
}

void ungetch(char prev) {
    if (bufferpos < MAX_BUFFER) {
        buffer[bufferpos++] = prev;
    } else {
        printf("special error: exceeded max ungetch buffer\n");
    }
}

int getch(void) {
    if (bufferpos > 0) {
        return buffer[--bufferpos];
    } else {
        return getc(stdin);
    }
}