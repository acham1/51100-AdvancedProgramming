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
#define p1_abs(a) ((a) < 0 ? (-a) : (a))
#define LOG_NAME "p1_log.txt"
#define DEFAULT_HASH_FN 1
#define BITS_PER_BYTE 8
#define SUPER_DIR "../"
#define TAB "        "
#define MAX_BUFFER 100
#define NUM_HASH_FNS 3
#define NUM_PRIMES 24
#define SUB_DIR "p1/"
#define HASH_BASE 31

typedef enum {
    FIND1, FIND2, DELETE, INSERT, PRINT, READ, ERROR, NONE
} Command;

Command getcommand(char* arg1, char* arg2, char* mssg);
int readlist(FILE* fptr, char* word, char* def);
void filterprint(void* word, void* def);
void printmap(void* word, void* def);
int cmp(void* key1, void* key2);
void printheading(int whichfn);
Command txttocmd(char* txt);
long prehash(char* str);
FILE* myfopen(char* arg1);
long hash1(Hashmap* hmp, void* str);
long hash2(Hashmap* hmp, void* str);
long hash3(Hashmap* hmp, void* str);
void ungetch(char prev); 
void initpowers(void);
void burntoend(void);
int getch(void);

long (*hashfunctions[NUM_HASH_FNS])(Hashmap*, void* str) = {hash1, hash2, hash3};
long primes[NUM_PRIMES] = {1, 2, 3, 7, 13, 31, 61, 127, 251, 509, 1021, 
    2039, 4093, 8191, 16381, 32749, 65521, 131071, 262139, 524287, 1048573,
    2097143, 4194301, 8388593};
long powers[MAX_WORD];
char buffer[MAX_BUFFER];
int getexp(long M);
int bufferpos = 0;
int primespos = 0;
char* externkey1;
char* externkey2;

int main(int argc, char** argv) {
    long (*hashfn)(Hashmap*, void*) = hashfunctions[0];
    int whichfn = DEFAULT_HASH_FN;
    FILE* logfile = NULL;
    char arg1[MAX_DEF+1];
    char arg2[MAX_DEF+1];
    char mssg[MAX_DEF+1];
    clock_t start, end;
    FILE* fptr = NULL;
    Element elmnt;
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
    start = clock();
    hmp = hmp_create();
    hmp->hashfn = hashfn;
    logfile = fopen(LOG_NAME, "w");
    fprintf(logfile, "HW3 P1 dictionary event log\n");
    fprintf(logfile, "---------------------------\n");
    while (!feof(stdin)) {
        switch(cmd = getcommand(arg1, arg2, mssg)) {
            case FIND1:
                printf("%sATTEMPT: finding word \"%s\"\n", TAB, arg1);
                elmnt = hmp_find(hmp, arg1, cmp);
                if (elmnt.key != NULL && elmnt.value != NULL) {
                    printf("%sSUCCESS: found word\n", TAB);
                    printf("%s%s: %s\n", TAB, arg1, (char*) elmnt.value);
                } else {
                    printf("%sERROR: failed to find word; it may not exist\n", TAB);
                }
                break;
            case FIND2:
                printf("%sATTEMPT: finding words between \"%s\" and \"%s\", inclusive\n", TAB, arg1, arg2);
                if (strcmp(arg1, arg2) < 0) {
                    externkey1 = arg1;
                    externkey2 = arg2;
                    hmp_traverse(hmp, cmp, filterprint);
                } else if (strcmp(arg1, arg2) > 0) {
                    externkey1 = arg2;
                    externkey2 = arg1;
                    hmp_traverse(hmp, cmp, filterprint);
                } else {
                    elmnt = hmp_find(hmp, arg1, cmp);
                    if (elmnt.key != NULL && elmnt.value != NULL) {
                        printf("%s%s: %s\n", TAB, arg1, (char*) elmnt.value);
                    }
                }
                printf("%sSUCCESS: printed all pairs between \"%s\" and \"%s\", inclusive\n", TAB, arg1, arg2);
                break;
            case DELETE:
                printf("%sATTEMPT: deleting word \"%s\"\n", TAB, arg1);
                elmnt = hmp_remove(hmp, arg1, cmp);
                if (elmnt.key != NULL && elmnt.value != NULL) {
                    free(elmnt.key);
                    free(elmnt.value);
                    printf("%sSUCCESS: removed word\n", TAB);
                    fprintf(logfile, "<delete> totalkeys: %ld, totaladdress: %ld, loadfactor: %f\n", hmp->numkeys, hmp->numbuckets, (double) hmp->numkeys/hmp->numbuckets);
                    fprintf(logfile, "         min_occupancy: %ld, max_occupancy: %ld\n", hmp->minoccupancy, hmp->maxoccupancy);
                } else {
                    printf("%sERROR: failed to remove word; it may not exist\n", TAB);
                }
                break;
            case INSERT: 
                printf("%sATTEMPT: inserting word \"%s\" with definition \"%s\"\n", TAB, arg1, arg2);
                word = malloc(sizeof(char) * (strlen(arg1) + 1));
                def = malloc(sizeof(char) * (strlen(arg2) + 1));
                strcpy(word, arg1);
                strcpy(def, arg2);
                if (!hmp_insert(hmp, word, def, cmp)) {
                    printf("%sSUCCESS: inserted word\n", TAB);
                    fprintf(logfile, "<insert> totalkeys: %ld, totaladdress: %ld, loadfactor: %f\n", hmp->numkeys, hmp->numbuckets, (double) hmp->numkeys/hmp->numbuckets);
                    fprintf(logfile, "         min_occupancy: %ld, max_occupancy: %ld\n", hmp->minoccupancy, hmp->maxoccupancy);
                } else {
                    printf("%sERROR: failed to insert word; it may already exist\n", TAB);
                    free(word);
                    free(def);
                }
                break;
            case PRINT:
                printf("%sATTEMPT: printing map alphabetically\n", TAB);
                hmp_traverse(hmp, cmp, printmap);
                printf("%sSUCCESS: printed map alphabetically\n", TAB);
                break;
            case READ:
                printf("%sATTEMPT: reading file \"%s\"\n", TAB, arg1);
                fptr = myfopen(arg1);
                if (fptr != NULL) {
                    counter = 0;
                    while (readlist(fptr, arg1, arg2)) {
                        word = malloc(sizeof(char) * (strlen(arg1) + 1));
                        def = malloc(sizeof(char) * (strlen(arg2) + 1));
                        strcpy(word, arg1);
                        strcpy(def, arg2);
//                        printf("%d) %s: %s\n", counter, word, def);
                        if (!hmp_insert(hmp, word, def, cmp)) {
                            counter++;
                        } else {
                            free(word);
                            free(def);
                        }
                    }
                    fclose(fptr);
                    printf("%sSUCCESS: read file\n", TAB);
                    fprintf(logfile, "< read > totalkeys: %ld, totaladdress: %ld, loadfactor: %f\n", hmp->numkeys, hmp->numbuckets, (double) hmp->numkeys/hmp->numbuckets);
                    fprintf(logfile, "         min_occupancy: %ld, max_occupancy: %ld\n", hmp->minoccupancy, hmp->maxoccupancy);
                } else {
                    printf("%sERROR: failed to open file\n", TAB);
                }
                break;
            case ERROR:
                printf("%sERROR: %s\n", TAB, mssg);
                break;
            case NONE:
                break;
            default:
                printf("%sspecial ERROR: invalid Command value\n", TAB);
        }
    }
    end = clock();
    printf("\n---------------------------------------------------------\n");
    printf("Used hash function #%d of %d\n", whichfn, NUM_HASH_FNS);
    printf("Total processor time consumed: %lf\n", (double) (end-start) / CLOCKS_PER_SEC);
    printf("---------------------------END---------------------------\n\n");
    hmp_deepdestroy(hmp);
    fprintf(logfile, "---------------------------\n");
    fprintf(logfile, "End of log\n");
    fclose(logfile);
    return EXIT_SUCCESS;
}

Command getcommand(char* arg1, char* arg2, char* mssg) {
    char cmdtxt[MAX_WORD+1];
    int wordpos = 0;
    Command cmd;
    char c;

    printf("\n    %%   ");
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
        "    example: ./a.out 1\n"
        "    Hash function 1: prehash, then mod on numbuckets\n"
        "    Hash function 2: prehash, then middle-square\n"
        "    Hash function 3: prehash, then mod on largest prime < numbuckets\n", 
        NUM_HASH_FNS, NUM_HASH_FNS);
    printf("---------------------------------------------------------\n");
    printf("The following operations are supported:\n\n");
    printf("    %%   insert [key] [value]\n");
    printf("    %%   find [key1] [key2]\n");
    printf("    %%   read [filename]\n");
    printf("    %%   delete [key]\n");
    printf("    %%   find [key]\n");
    printf("    %%   print\n");
    printf("---------------------------------------------------------\n");
    printf("Please enter your operations below: \n");
}

void ungetch(char prev) {
    if (bufferpos < MAX_BUFFER) {
        buffer[bufferpos++] = prev;
    } else {
        printf("special ERROR: exceeded max ungetch buffer\n");
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
    powers[0] = (long) 1;
    for (int i = 1; i < MAX_WORD; i++) {
        powers[i] = (long) (HASH_BASE * powers[i-1]);
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

long prehash(char* str) {
    int len = strlen(str);
    long out = 0;

    for (int i = 0; i < len; i++) {
        out += powers[len-1-i] * str[i];
    }
    return out;
}

// simple mod
long hash1(Hashmap* h, void* str) {
    long k = prehash(str);
    k = k % h->numbuckets;
    return p1_abs(k);
}

// middle square, assume numbuckets is power of 2
long hash2(Hashmap* h, void* str) {
    int w = sizeof(long) * BITS_PER_BYTE;
    long M = h->numbuckets;
    int k = getexp(M);
    long x = prehash(str);
    return p1_abs((x*x) >> (w-k));
}

// mod over greatest lesser prime
long hash3(Hashmap* h, void* str) {
    long prime = 1, lastprime = 1;
    long k = prehash(str);

    for (int i=0; i < NUM_PRIMES; i++) {
        prime = primes[i];
        if (prime > h->numbuckets) {
            break;
        }
        lastprime = prime;
    }    
    if (prime < h->numbuckets) {
        return hash1(h, str); // more than 8,388,593 buckets
    }
    k = k % lastprime;
    return p1_abs(k);
}

FILE* myfopen(char* arg1) {
    FILE* fptr = fopen(arg1, "r");
    char path[MAX_DEF+1];
    char path2[MAX_DEF+1];

    if (fptr == NULL) {
        strcpy(path, SUPER_DIR);
        strcat(path, arg1);
        printf("%sERROR: failed to open file at %s; now trying %s\n", TAB, arg1, path);
        fptr = fopen(path, "r");
        if (fptr == NULL) {
            strcpy(path2, SUB_DIR);
            strcat(path2, arg1);
            printf("%sERROR: failed to open file at %s; now trying %s\n", TAB, path, path2);
            fptr = fopen(path2, "r");                        
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
    word[wordpos++] = tolower(c);
    while (!feof(fptr) && !isspace(c = getc(fptr))) {
        word[wordpos++] = tolower(c);
    }
    word[wordpos++] = '\0';
    while (!feof(fptr) && (c = getc(fptr)) != '"');
    while (!feof(fptr) && (c = getc(fptr)) != '"') {
        def[defpos++] = tolower(c);
    }
    def[defpos++] = '\0';
    while (!feof(fptr) && getc(fptr) != '\n');
    return 1;
}

int cmp(void* key1, void* key2) {
    int result;
//    printf("in cmp\n");
    result = strcmp((char*) key1, (char*) key2);
//    printf("out cmp\n");
    return result;
}

void printmap(void* word, void* def) {
    printf("%s%15s: \"%s\"\n", TAB, (char*) word, (char*) def);
}

void filterprint(void* word, void* def) {
    if (strcmp(externkey1, word) <= 0 && strcmp(externkey2, word) >= 0) {
        printf("%s%15s: \"%s\"\n", TAB, (char*) word, (char*) def);
    }
}

int getexp(long M) {
    int k = 0;

//    printf("M: %ld ", M);
    while (M) {
        M = M >> 1;
        k++;
    }
//    printf("k: %d\n", k);
    return k;
}