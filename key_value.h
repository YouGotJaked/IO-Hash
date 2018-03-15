# ifndef KEY_VALUE_H
# define KEY_VALUE_H

#define EMPTY 0
#define FILLED 1
#define DELETED 2

typedef struct set SET;

SET *createSet(int maxElts);

void destroySet(SET *sp);

int numElements(SET *sp);

int findElement(SET *sp, char *str, bool *found);

bool hasElement(SET *sp, char *str);

bool addElement(SET *sp, char *str);

bool removeElement(SET *sp, char *str);

void printElements(SET *sp);

# endif /* KEY_VALUE */


