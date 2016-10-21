#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    printf("// This file is to test sequential adding only.\n");
    printf("// The output of this file can be saved and redirected to stdin\n"
        "when running p4a.c or p4b.c");

    int max = 10000;
    for (int i = 0; i < max; i++) {
        printf("add %05d \"%05d\"\n", i, i);
    }
    return EXIT_SUCCESS;
}