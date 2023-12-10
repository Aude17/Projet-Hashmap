#ifndef ABR_H
#define ABR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listechainee.h"

typedef struct Tree {
    char* key;
    int h;
    struct List* values;
    struct Tree* fg;
    struct Tree* fd;
} Tree;

Tree* createTree(int h, List* list);
void displayValuesList(List* values);
void displayNode(Tree* node);
void freeTree(Tree* root);
Tree* addTreeNode(Tree* proot, char* key, int h, int value);
int hash(char* key);

#endif /* ABR_H */
