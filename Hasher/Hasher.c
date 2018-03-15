#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/evp.h"

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
int hashFun(char *val, unsigned char **result) {
    unsigned int md_len;
    EVP_MD_CTX *mdctx = EVP_MD_CTX_create();
    const EVP_MD *md = EVP_sha512();
    (*result) = (unsigned char *) calloc(EVP_MAX_MD_SIZE, sizeof(unsigned char));

    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, val, strlen(val));
    EVP_DigestFinal_ex(mdctx, (*result), &md_len);

    EVP_MD_CTX_destroy(mdctx);
    return md_len;
}

int chainHashFun(unsigned char *val, unsigned char **result) {
    unsigned int md_len;
    EVP_MD_CTX *mdctx = EVP_MD_CTX_create();
    const EVP_MD *md = EVP_sha512();
    (*result) = (unsigned char *) calloc(EVP_MAX_MD_SIZE, sizeof(unsigned char));
    
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, val, 2 * EVP_MAX_MD_SIZE);
    EVP_DigestFinal_ex(mdctx, (*result), &md_len);
    
    EVP_MD_CTX_destroy(mdctx);
    return md_len;
}

Hasher *createHasher() {
    Hasher *h = (Hasher *) malloc(sizeof(Hasher));
    h->hash = hashFun;
    h->chainHash = chainHashFun;
    OpenSSL_add_all_digests();
    return h;
}

void cleanup(Hasher *h) {
    free(h);
    EVP_cleanup();
}

void printHash(unsigned char *hash, int hashLen) {
    int i;
    for(i = 0; i < hashLen; i++) {
        printf("%02x", hash[i]);
    }
}
