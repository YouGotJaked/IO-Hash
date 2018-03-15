#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hasher/Hasher.c"
#include "helper.h"

data *create_data() {
    data *d;
    d = malloc(sizeof(data));
    d->lenStr = 0;
    d->lenHash = 0;
    d->lenCatHash = 0;
    d->str = malloc(sizeof(char) * SIZE);
    d->strHash = malloc(sizeof(unsigned char) * HASH_LEN);
    d->catHash = malloc(sizeof(unsigned char) * HASH_LEN);
    return d;
}

int check_argc(int argc, int n, char **argv) {
    if (argc != n) {
        char *msg;
        if (strcmp(argv[0], "./output") == 0) {
            msg = "Usage: %s <input file> 2>&1 | tee <output file>\n";
        } else {
            msg = "Usage: %s <input file>\n";
        }
        fprintf(stderr, msg, argv[0]);
        exit(-1);
    }
    return n;
}

void check_file(FILE *fp, char **argv) {
    if (fp == NULL) {
        printf("File %s not found.\n", argv[1]);
        exit(-1);
    }
}

// append previous cat hash to str, then append '\0' as string literal
unsigned char *concatenate(char *str, unsigned char *catHash) {
    unsigned char *append = (unsigned char*) malloc(SIZE + HASH_LEN);
    memcpy(append, str, SIZE);
    memcpy(append + SIZE, catHash, HASH_LEN);
    append[SIZE + HASH_LEN + 1] = '\0';
    return append;
}

void invalid_hash(char *calc, unsigned char *read, int flag) {
    for (int i = 0; i < HASH_LEN; i++) {
     // printf("calc[%d] = %c\tread[%d] = %c\n", i, calc[i], i, read[i]);
        if (calc[i] != read[i]) {
            printf("%s\n", msg[flag]);
            exit(-1);
        }
    }
}

// convert calculated string to hexadecimal
char *char_to_hex(unsigned char *hash) {
    char *converted = (char*) malloc(2*HASH_LEN + SIZE);
    for (int i = 0; i < 2*HASH_LEN; i++) {
        sprintf(&converted[2*i], "%02x", hash[i]);
    }
    return converted;
}
