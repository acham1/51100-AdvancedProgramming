/** Alan Cham
  * MPCS 51100
  * November 13, 2016
  * Homework 3, p1 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include "hashmap.h"

#define MAX_WORD 50 /*including terminating '\0'*/
#define MAX_DEF 500 /*including terminating '\0'*/
#define MAX_BUFFER 100
#define NUM_HASH_FNS 3
#define DEFAULT_HASH_FN 1
#define LOG_NAME "p1_log.txt"

typedef enum {
    FIND1, FIND2, DELETE, INSERT, PRINT, READ, ERROR
} Command;

Command get_command(char* arg1, char* arg2, char* mssg);
void print_heading(int whichfn);
void ungetch(char prev); 
void burntoend(void);
int getch(void);

int primes[] = {2, 5, 11, 23, 47, 97, 197, 397, 797, 1597, 3203, 
    6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117, 
    1646237, 3292489, 6584983, 13169977};

char buffer[MAX_BUFFER];
int bufferpos = 0;

int main(int argc, char** argv) {
    clock_t start, end;
    char arg1[MAX_DEF];
    char arg2[MAX_DEF];
    char mssg[MAX_DEF];
    int whichfn = DEFAULT_HASH_FN;
    Command cmd;

    if (argc > 1) {
        whichfn = atoi(argv[1]);
        if (whichfn < 1 || whichfn > NUM_HASH_FNS) {
            whichfn = DEFAULT_HASH_FN;
        }
    }

    print_heading(whichfn);
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
                printf("error: %s", mssg);
                break;
            default:
                printf("special error: invalid Command value\n");
        }
    }
    end = clock();
    printf("---------------------------------------------------------\n\n");
    printf("Used hash function #%d of %d\n", whichfn, NUM_HASH_FNS);
    printf("Total processor time consumed: %lf", (double) (end-start) / CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}

// return 1 if problem getting command
Command get_command(char* arg1, char* arg2, char* mssg) {
    Command cmd = ERROR;
    char c;
    return cmd;
}

void print_heading(int whichfn) {
    printf("Welcome to hw3 p1 dictionary.\n");
    printf("[Reminder] Enter option command-line argument (integer between\n" 
        "1 to %d, inclusive) to specify which of %d hash functions to use.\n"
        "e.g. use the second hash function by entering ./a.out 1\n\n", 
        NUM_HASH_FNS, NUM_HASH_FNS);
    printf("Currently using hashfn %d\n\n", whichfn);
    printf("The following operations are supported:\n");
    printf("%%find [key]\n");
    printf("%%delete [key]\n");
    printf("%%insert [key]\n");
    printf("%%find [key1] [key2]\n");
    printf("%%print\n");
    printf("%%read [filename]\n\n");
    printf("Please enter your operations below: \n");
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

void burntoend(void) {
    char c;
    while ((c = getch()) != EOF && c != '\n');
}