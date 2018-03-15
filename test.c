# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "key_value.c"

# define MAX_SIZE 18000

int main(int argc, char **argv) {
    FILE *fp;
    SET *unique = createSet(MAX_SIZE);
    char buffer[BUFSIZ];
    int words = 0;
    bool found;
    
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


    while (1) {
        printf("Enter a word to find or type 'q' to quit:\n");
        scanf("%s", buffer);
        if (strcmp(buffer, "q") == 0) {
            break;
        } else if ((found = hasElement(unique, buffer))) {
            printf("%s is found at %d\n", buffer, findElement(unique, buffer, &found));
        } else {
            printf("%s is not found.\n", buffer);
        }
    }
    
    printf("Unique elements in set:\n");
    printElements(unique);
    printf("%d total words\n", words);
    printf("%d distinct words\n", numElements(unique));
    
    fclose(fp);
    destroySet(unique);
    return 0;
}

