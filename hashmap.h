#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    int size;
    Node** cell;
} HashMap;

HashMap* createHashMap(int size);
int hash(const char* key);
void addHashMap(HashMap* map, char* key, int value);
Node* findKeyByHash(const HashMap* map, int hashValue);
void removeKeyHashMap(HashMap* map, const char* key);
void printHashMap(const HashMap* map);
int sizeHashMap(const HashMap* map);
void freeHashMap(HashMap* map);

#endif // HASHMAP_H
