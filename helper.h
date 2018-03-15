#ifndef HELPER_H
#define HELPER_H

#define SIZE 255
#define HASH_LEN (2 * EVP_MAX_MD_SIZE)
#define INVALID 0
#define OMISSION 1

/*
 * INDEX KEY
 * 0: invalid
 * 1: omission
 */

const char *msg[] = {
    "File has been modified.\n",
    "Omission from file detected.\n",
};

typedef struct data {
    int lenStr;
    int lenHash;
    int lenCatHash;
    char *str;
    unsigned char *strHash;
    unsigned char *catHash;
} data;

data *create_data();
int check_argc(int argc, int n, char **argv);
void check_file(FILE *fp, char **argv);
unsigned char *concatenate(char *str, unsigned char *catHash);
void invalid_hash(char *calc, unsigned char *read, int flag);
char *char_to_hex(unsigned char *hash);

#endif
