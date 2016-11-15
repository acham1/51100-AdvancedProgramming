/** Alan Cham
  * MPCS 51100
  * November 13, 2016
  * Homework 3, p1 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "hashmap.h"

#define MAX_WORD 50 /*including terminating '\0'*/
#define MAX_DEF 500 /*including terminating '\0'*/
#define LOG_NAME "p1_log.txt"
#define DEFAULT_HASH_FN 1
#define SUPER_DIR "../"
#define TAB "        "
#define MAX_BUFFER 100
#define NUM_HASH_FNS 3
#define NUM_PRIMES 23
#define SUB_DIR "p1/"
#define HASH_BASE 31

typedef enum {
    FIND1, FIND2, DELETE, INSERT, PRINT, READ, ERROR, NONE
} Command;

Command getcommand(char* arg1, char* arg2, char* mssg);
int readlist(FILE* fptr, char* word, char* def);
void printheading(int whichfn);
Command txttocmd(char* txt);
unsigned prehash(char* str);
FILE* myfopen(char* arg1);
unsigned hash1(void* str);
unsigned hash2(void* str);
unsigned hash3(void* str);
void ungetch(char prev); 
void initpowers(void);
void burntoend(void);
int getch(void);

unsigned (*hashfunctions[NUM_HASH_FNS])(void* str) = {hash1, hash2, hash3};
int primes[NUM_PRIMES] = {2, 5, 11, 23, 47, 97, 197, 397, 797, 
    1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 
    411527, 823117, 1646237, 3292489, 6584983, 13169977};
unsigned powers[MAX_WORD];
char buffer[MAX_BUFFER];
int bufferpos = 0;
int primespos = 0;

int main(int argc, char** argv) {
    unsigned (*hashfn)(void* str) = hashfunctions[0];
    int whichfn = DEFAULT_HASH_FN;
    char arg1[MAX_DEF+1];
    char arg2[MAX_DEF+1];
    char mssg[MAX_DEF+1];
    char path[MAX_DEF+1];
    clock_t start, end;
    FILE* fptr = NULL;
    Element* elmnt;
    Hashmap* hmp;
    Command cmd;
    int counter;
    char* word;
    char* def;

    if (argc > 1) {
        whichfn = atoi(argv[1]);
        if (whichfn < 1 || whichfn > NUM_HASH_FNS) {
            whichfn = DEFAULT_HASH_FN;
        }
        hashfn = hashfunctions[whichfn-1];
    }

    initpowers();
    printheading(whichfn);
    hmp = new_hashmap();
    start = clock();
    while (!feof(stdin)) {
        switch(cmd = getcommand(arg1, arg2, mssg)) {
            case FIND1:
                printf("attempt: finding word \"%s\"\n", TAB, arg1);
                if (elmnt = hmp_find(hmp, arg1, hashfn)) {
                    printf("%ssuccess: found word\n", TAB);
                    printf("%s%s: %s\n", TAB, arg1, (char*) elmnt.value);
                } else {
                    printf("%serror: failed to find word; it may not exist\n", TAB);
                }
                break;
            case FIND2:
                printf("%sattempt: finding words between \"%s\" and \"%s\", inclusive\n", TAB, arg1, arg2);
                break;
            case DELETE:
                printf("%sattempt: deleting word \"%s\"\n", TAB, arg1);
                if (elmnt = hmp_remove(hmp, arg1, hashfn)) {
                    free(elmnt.key);
                    free(elmnt.value);
                    printf("%ssuccess: removed word\n", TAB);
                } else {
                    printf("%serror: failed to remove word; it may not exist\n", TAB);
                }
                break;
            case INSERT: 
                printf("%sattempt: inserting word \"%s\" with definition \"%s\"\n", TAB, arg1, arg2);
                break;
            case PRINT:
                printf("%sattempt: printing\n", TAB);
                break;
            case READ:
                printf("%sattempt: reading file \"%s\"\n", TAB, arg1);
                if (fptr = myfopen(arg1)) {
                    counter = 0;
                    while (readlist(fptr, arg1, arg2)) {
                        hmp_insert(hmp, arg1, arg2, hashfn);
                    }
                    fclose(fptr);
                } else {
                    printf("%serror: failed to open file\n", TAB);
                }
                break;
            case ERROR:
                printf("%serror: %s\n", TAB, mssg);
                break;
            case NONE:
                break;
            default:
                printf("%sspecial error: invalid Command value\n", TAB);
        }
    }
    end = clock();
    printf("---------------------------------------------------------\n");
    printf("Used hash function #%d of %d\n", whichfn, NUM_HASH_FNS);
    printf("Total processor time consumed: %lf\n", (double) (end-start) / CLOCKS_PER_SEC);
    printf("---------------------------END---------------------------\n\n");
    return EXIT_SUCCESS;
}

Command getcommand(char* arg1, char* arg2, char* mssg) {
    char cmdtxt[MAX_WORD+1];
    int wordpos = 0;
    Command cmd;
    char c;

    printf("    %%   ");
    /** receive the operation name **/
    while ((c = getch()) != EOF && c != '\n' && isspace(c));
    if (c == EOF || c == '\n') {
        if (c == EOF) {
            printf("\n");
        }
        return NONE;
    }
    ungetch(c);
    while ((c = getch()) != EOF && !isspace(c) && wordpos < MAX_WORD) {
        cmdtxt[wordpos++] = tolower(c);
    }
    ungetch(c);
    cmdtxt[wordpos++] = '\0';
    cmd = txttocmd(cmdtxt);
    if (cmd == ERROR) {
        burntoend();
        strcpy(mssg, "not a valid operation");
        return ERROR;
    } else if (cmd == PRINT) {
        burntoend();
        return PRINT;
    }
    /** receive the first argument **/
    wordpos = 0;
    while ((c = getch()) != EOF && c != '\n' && isspace(c));
    if (c == EOF || c == '\n') {
        if (c == EOF) {
            printf("\n");
        }
        strcpy(mssg, "missing argument 1");
        return ERROR;
    }
    ungetch(c);
    while ((c = getch()) != EOF && !isspace(c) && wordpos < MAX_WORD) {
        arg1[wordpos++] = (cmd == READ) ? c : tolower(c);
    }
    ungetch(c);
    arg1[wordpos++] = '\0';
    if (c != EOF && !isspace(c)) {
        burntoend();
        strcpy(mssg, "word exceeds char limit");
        return ERROR;
    }    
    if (cmd == READ || cmd == DELETE) {
        burntoend();
        return cmd;
    }
    /** receive the second argument **/
    wordpos = 0;
    while ((c = getch()) != EOF && c != '\n' && isspace(c));
    if (c == EOF || c == '\n') {
        if (c == EOF) {
            printf("\n");
        }
        if (cmd == FIND1) {
            return FIND1;
        } else {
            strcpy(mssg, "missing argument 2");
            return ERROR;
        }
    }
    ungetch(c);
    if (cmd == FIND1) {
        while ((c = getch()) != EOF && !isspace(c) && wordpos < MAX_WORD) {
            arg2[wordpos++] = tolower(c);
        }
        ungetch(c);
        arg2[wordpos++] = '\0';
        burntoend();
        if (c != EOF && !isspace(c)) {
            strcpy(mssg, "word exceeds char limit");
            return ERROR;
        }    
        return FIND2;
    } else {
        while ((c = getch()) != EOF && c != '\n' && wordpos < MAX_DEF) {
            arg2[wordpos++] = tolower(c);
        }
        ungetch(c);
        arg2[wordpos++] = '\0';
        burntoend();
        if (c != EOF && c != '\n') {
            strcpy(mssg, "definition exceeds char limit");
            return ERROR;
        }    
        return INSERT;         
    }
    return cmd;
}

void printheading(int whichfn) {
    printf("\n--------------------------START--------------------------\n");
    printf("Now using hash function #%d of %d\n\n", whichfn, NUM_HASH_FNS);
    printf("    Note: use optional command-line argument (integer from 1 to %d,\n" 
        "    inclusive) to specify which of %d hash functions to use.\n"
        "    example: ./a.out 1\n", NUM_HASH_FNS, NUM_HASH_FNS);
    printf("---------------------------------------------------------\n");
    printf("The following operations are supported:\n\n");
    printf("    %%   insert [key] [value]\n");
    printf("    %%   find [key1] [key2]\n");
    printf("    %%   read [filename]\n");
    printf("    %%   delete [key]\n");
    printf("    %%   find [key]\n");
    printf("    %%   print\n");
    printf("---------------------------------------------------------\n");
    printf("Please enter your operations below: \n\n");
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

void initpowers(void) {
    powers[0] = (unsigned) 1;
    for (int i = 1; i < MAX_WORD; i++) {
        powers[i] = (unsigned) (HASH_BASE * powers[i-1]);
    }
}

void burntoend(void) {
    char c;
    while ((c = getch()) != EOF && c != '\n');
}

Command txttocmd(char* txt) {
    if (!strcmp(txt, "find")) {
        return FIND1;
    } else if (!strcmp(txt, "delete")) {
        return DELETE;
    } else if (!strcmp(txt, "insert")) {
        return INSERT;
    } else if (!strcmp(txt, "print")) {
        return PRINT;
    } else if (!strcmp(txt, "read")) {
        return READ;
    } else {
        return ERROR;
    }
}

unsigned prehash(char* str) {
    int len = strlen(str);
    unsigned out = 0;

    for (int i = 0; i < len; i++) {
        out += powers[len-1-i] * str[i];
    }
    return out;
}

unsigned hash1(void* str) {
    unsigned k = prehash(str);
    return k;
}

unsigned hash2(void* str) {
    unsigned k = prehash(str);
    return k;
}

unsigned hash3(void* str) {
    unsigned k = prehash(str);    
    return k;
}

FILE* myfopen(char* arg1) {
    FILE* fptr = fopen(arg1, "r");
    char* path[MAX_DEF+1];
    char* path2[MAX_DEF+1];

    if (fptr == NULL) {
        strcpy(path, SUPER_DIR);
        strcat(path, arg1);
        printf("error: failed to open file at %s; now trying %s\n", arg1, path);
        fptr = fopen(path);
        if (fptr == NULL) {
            strcpy(path, SUB_DIR);
            strcat(path, arg1);
            printf("error: failed to open file at %s; now trying %s\n", path, path2);
            fptr = fopen(path2);                        
        }
    }
    return fptr;
}

// return num words read
int readlist(FILE* fptr, char* word, char* def) {
    int wordpos = 0;
    int defpos = 0;
    char c;
    while (!feof(fptr) && isspace(c = getc(fptr)));
    if (feof(fptr) || c == '\n') {
        return 0;
    }
    word[wordpos++] = c;
    while (!feof(fptr) && !isspace(c = getc(fptr))) {
        word[wordpos++] = c;
    }
    word[wordpos++] = '\0';
    while (!feof(fptr) && (c = getc(fptr)) != '"');
    while (!feof(fptr) && (c = getc(fptr)) != '"') {
        def[defpos++] = c;
    }
    def[defpos++] = '\0';
    while (!feof(fptr) && getc(fptr) != '\n');
    return 1;
}