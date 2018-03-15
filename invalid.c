#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.c"

int main(int argc, char **argv) {
    // check arguments
    check_argc(argc, 2, argv);
    
    // open output file for reading
    FILE *fr;
    fr = fopen(argv[1], "r");
    check_file(fr, argv);

    data *read = create_data(), *calc = create_data();
    Hasher *h = createHasher();
    
    // scan file line by line
    while (fscanf(fr, "%d %s %s %s", &read->lenStr, read->str, read->strHash, read->catHash) != -1) {
        h->hash(read->str, &calc->strHash);
        invalid_hash(char_to_hex(calc->strHash), read->strHash, INVALID);
    }

    cleanup(h);
    free(calc->strHash);
    fclose(fr);
    printf("File has not been modified.\n");
    return 0;
}
