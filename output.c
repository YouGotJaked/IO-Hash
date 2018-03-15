#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.c"

int main(int argc, char **argv) {
    // check arguments
    check_argc(argc, 2, argv);
    
    // open input file for reading
    char buffer[SIZE];
    FILE *fr;
    fr = fopen(argv[1], "r");
    check_file(fr, argv);
    
    Hasher *h = createHasher();
    data *hashData = create_data(), *prevHashData = create_data();
    unsigned char *cat;

    // accept sequences of strings until EOF
    while (fgets(buffer, SIZE, fr) != NULL) {
        // remove '\n' character from buffer
        buffer[strcspn(buffer, "\r\n")] = 0;
        hashData->lenStr = strlen(buffer);
        strcpy(hashData->str, buffer);
        hashData->lenHash = h->hash(hashData->str, &hashData->strHash); // 64 bytes, 128 char

        cat = concatenate(hashData->str, prevHashData->catHash);
        hashData->lenCatHash = h->chainHash(cat, &hashData->catHash);

        // LENGTH       STRING       HASH_RESULT        HASH_CAT
        printf("%d\t %s\t", hashData->lenStr, hashData->str);
        printHash(hashData->strHash, hashData->lenHash);
        printf("\t");
        printHash(hashData->catHash, hashData->lenCatHash);
        printf("\n");

        prevHashData = hashData;
    }
    
    cleanup(h);
    free(hashData->strHash);
    free(hashData->catHash);
    free(cat);
    return 0;
}
