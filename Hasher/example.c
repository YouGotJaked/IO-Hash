#include <stdio.h>
#include <stdlib.h>
#include "Hasher.c"

void parseArguments(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Incorrect arguments. Usage:\n\t./testHash astring\n\nWhere astring a string to get the hash of.\n");
        exit(-1);
    }
}

// takes a string as a command line argument and prints its sha512 hash to stdout
int main(int argc, char *argv[]) {
    unsigned char *hashValue;
    int hashLen;
    parseArguments(argc, argv);
    
    Hasher *h = createHasher();
    hashLen = h->hash(argv[1], &hashValue);

    printf("%s was hashed to ", argv[1]);
    printHash(hashValue, hashLen);
    printf("\n");

    cleanup(h);
    free(hashValue);

    return 0;
}
