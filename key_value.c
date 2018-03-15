#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "key_value.h"

struct set {
    int length;
    int count;
    char **elts;
    char *flags;
};

SET *createSet(int maxElts) {
    SET *sp;
    
    sp = malloc(sizeof (SET));
    assert(sp != NULL);
    
    sp->count = 0;
    sp->length = maxElts;
    
    sp->elts = malloc(sizeof (char*) * maxElts);
    assert(sp->elts != NULL);
    
    sp->flags = malloc(sizeof (char) * maxElts);
    assert(sp->flags != NULL);
    
    for (int i = 0; i < maxElts; i++) {
        sp->flags[i] = EMPTY;
    }
    return sp;
}

void destroySet(SET *sp) {
    assert(sp != NULL);

    for (int i = 0; i < sp->length; i++) {
        if (sp->flags[i] == FILLED) {
            free(sp->elts[i]);
        }
    }
    
    free(sp->elts);
    free(sp->flags);
    free(sp);
}

int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

unsigned int hashString(char *s) {
    unsigned hash = 0;
    
    while (*s != '\0') {
        hash = 31 * hash + *s++;
    }
    
    return hash;
}

int findElement(SET *sp, char *elt, bool *found) {
    assert(sp != NULL && elt != NULL);
    
    int position;
    int first = -1;
    unsigned int hash = hashString(elt);
    
    for (int i = 0; i < sp->length; i++) {
        position = (hash + i) % sp->length;

        if (sp->flags[position] == DELETED && first == -1) {
            first = position;
        }
        
        if (sp->flags[position] == EMPTY) {
            *found = false;
            return first != -1 ? first : position;
        }
        
        if (sp->flags[position] == FILLED && strcmp(elt, sp->elts[position]) == 0) {
            *found = true;
            return position;
        }
    }
    
    *found = false;
    return first;
}

bool hasElement(SET *sp, char *elt) {
    assert(sp != NULL && elt != NULL);
    bool found;
    findElement(sp, elt, &found);
    return found;
}

bool addElement(SET *sp, char *elt) {
    assert(sp != NULL && elt != NULL);
    
    if (sp->count == sp->length) {
        return false;
    }
    
    bool found;
    int position = findElement(sp, elt, &found);
    
    if (found) {
        return false;
    }
    
    elt = strdup(elt);
    assert(elt != NULL);
    
    sp->elts[position] = elt;
    sp->flags[position] = FILLED;
    sp->count++;
    return true;
}

bool removeElement(SET *sp, char *elt) {
    assert(sp != NULL && elt != NULL);
    
    if (sp->count == 0) {
        return false;
    }
    
    bool found;
    int position = findElement(sp, elt, &found);
    
    if (found) {
        free(sp->elts[position]);
        sp->flags[position] = DELETED;
        sp->count--;
        return true;
    }
    return false;
}

void printElements(SET *sp) {
    for (int i = 0; i < sp->length; i++) {
        if (sp->flags[i] == FILLED) {
            printf("%s ", sp->elts[i]);
        }
    }
    printf("\n");
}
