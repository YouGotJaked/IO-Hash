#ifndef HASHER_H
#define HASHER_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// public portion of Hasher defintion
typedef struct Hasher {
    int (*hash)(char *val, unsigned char **result);
    int (*chainHash)(unsigned char *val, unsigned char **result);
} Hasher;

// the function that preforms the hash algorithm
//      @param result
//          should be passed as the reference to an unallocated pointer
//          is allocated on the heap and must be freed before the program terminates
//          will be filled with the sha512 hash of val upon completion
//      @retval 
//          the length of the hash stored in result
int hash(char *val, unsigned char **result); 

// allocates a hasher object to the heap
Hasher *createHasher();

void cleanup(Hasher *h);

void printHash(unsigned char *hash, int hashLen); 

#endif
