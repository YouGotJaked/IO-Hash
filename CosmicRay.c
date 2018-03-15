#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>

uint64_t uint64Rand() {
    int i;
    uint64_t randNum = 0;
    uint64_t bitsGenerated = (int)ceil(log2(RAND_MAX));
    int numIter = 64%bitsGenerated;
    for(i = 0; i < numIter; i++) {
        randNum |= rand();
        randNum <<= bitsGenerated;
    }
    return randNum;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Incorrect arguments. Usage:\n\t./CosmicRay file\n\nWhere file is the path to a file to corrupt with a cosmic ray\n");
        return -1;
    }
    size_t fileSize;
    uint64_t randNum;
    FILE *f = fopen(argv[1], "r+");
    if(f == NULL) {
        fprintf(stderr, "%s could not be found\n", argv[1]);
        return -1;
    }
    fseek(f, 0L, SEEK_END);
    fileSize = ftell(f);
    if(fileSize < 1) {
        fprintf(stderr, "%s is a file with no bytes in it\n", argv[1]);
        return -1;
    }
    fseek(f, 0L, SEEK_SET);
    srand(time(0));
    
    randNum = uint64Rand()%fileSize;
    fseek(f, randNum, SEEK_SET);
    // insert random ascii character
    fputc(rand()%128, f);
    fclose(f);
}
