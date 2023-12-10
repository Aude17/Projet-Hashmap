#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"
#include "listechainee.h"
typedef struct {
    int h;
    struct List* cell;
    struct Tree* fg;
    struct Tree* fd;
} List;

typedef struct {
    char* key;
    int h;
    struct List* cell;
    struct Tree* fg;
    struct Tree* fd;
} Tree;



typedef struct HashMap {
    Tree* proot;
    int size;
    List** cell;
} HashMap;

HashMap* createHashmap();
int sizeHM(HashMap* map);
Tree* removeTree(Tree* root, char* key);
int removeHashmap(HashMap* map, char* key);
int hash(char* chaine);
int addHashmap(HashMap* map, char* key, int value);
void display(HashMap* map);
int addHM(HashMap* map, char* key, int value);

#endif /* HASHMAP_H */
