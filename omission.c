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
    
    Hasher *h = createHasher();
    data *read = create_data(), *calc = create_data(), *prevCalc = create_data();
    unsigned char *calc_cat;

    // scan file line by line
    while (fscanf(fr, "%d %s %s %s", &read->lenStr, read->str, read->strHash, read->catHash) != -1) {
        strcpy(calc->str, read->str);
        h->hash(read->str, &calc->strHash);
        calc_cat = concatenate(calc->str, prevCalc->catHash);
        h->chainHash(calc_cat, &calc->catHash);
        invalid_hash(char_to_hex(calc->catHash), read->catHash, OMISSION);
        prevCalc = calc;
    }
    
    cleanup(h);
    free(calc->strHash);
    free(calc->catHash);
    free(calc_cat);
    fclose(fr);
    printf("No omission from file detected.\n");
    return 0;
}
