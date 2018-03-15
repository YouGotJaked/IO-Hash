# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "key_value.c"

# define MAX_SIZE 18000

int main(int argc, char **argv) {
    FILE *fp;
    SET *unique = createSet(MAX_SIZE);
    char buffer[BUFSIZ];
    int words = 0;
    
    if (argc == 1 || argc > 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        exit(-1);
    }
    
    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[1]);
        exit(-1);
    }
    
    while (fscanf(fp, "%s", buffer) == 1) {
        words++;
        addElement(unique, buffer);
    }
    
    printElements(unique);
    printf("%d total words\n", words);
    printf("%d distinct words\n", numElements(unique));
    
    fclose(fp);
    destroySet(unique);
    return 0;
}

