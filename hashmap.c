#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "linkedlist.h"

HashMap* createHashMap(int size) {
    HashMap* hm = (HashMap*)malloc(sizeof(HashMap));
    if (hm != NULL) {
        hm->size = size;
        hm->cell = (Node**)malloc(size * sizeof(Node*));
        for (int i = 0; i < size; ++i) {
            hm->cell[i] = NULL;
        }
    }
    return hm;
}

int hash(const char* key) {
    char firstLetter = key[0];
    if ((firstLetter >= 'a' && firstLetter <= 'z') || (firstLetter >= 'A' && firstLetter <= 'Z')) {
        /** Return the ASCII value of the first letter as the hash value*/
        return (int)firstLetter - 97;
    } else {
        /** Return a default value if the key does not start with a letter*/
        return 0;
    }
}

void addHashMap(HashMap* map, char* key, int value) {
    int i = hash(key);
    Node* current = map->cell[i];
    Node* prev = NULL;

    /** Search for the key in the chain*/
    while (current != NULL && strcmp(current->key, key) != 0) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        /** Key found, update the value*/
        printf("Key '%s' already exists. Changing its value to %d\n", key, value);
        current->value = value;
    } else {
        /** Key not found, add a new node*/
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = strdup(key);
        newNode->value = value;
        newNode->next = NULL;

        if (prev == NULL) {
            map->cell[i] = newNode;
        } else {
            prev->next = newNode;
        }
    }
}

Node* findKeyByHash(const HashMap* map, int hashValue) {
    int index = hashValue % map->size;
    Node* current = map->cell[index];
    while (current != NULL) {
        if (hash(current->key) == hashValue) {
            return current;
        }
        current = current->next;
    }
    return NULL; /** Key not found for the given hash value*/
}

void removeKeyHashMap(HashMap* map, const char* key) {
    int hashValue = hash(key);
    int index = hashValue % map->size;

    Node* current = map->cell[index];
    Node* prev = NULL;

    /** Search for the key in the chain*/
    while (current != NULL && strcmp(current->key, key) != 0) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        /** Key found, remove the node*/
        if (prev == NULL) {
            /** The node is the first in the chain*/
            map->cell[index] = current->next;
        } else {
            prev->next = current->next;
        }

        free(current->key);
        free(current);
        printf("Key '%s' removed from the HashMap\n", key);
    } else {
        printf("Key '%s' not found in the HashMap\n", key);
    }
}

void printHashMap(const HashMap* map) {
    for (int i = 0; i < map->size; i++) {
        printf("Chain %d: ", i);
        Node* current = map->cell[i];
        while (current != NULL) {
            printf("(%s, %d) ", current->key, current->value);
            current = current->next;
        }
        printf("\n");
    }
}


/** cette fonction recupere le size de la hashmap*/
int sizeHashMap(const HashMap* map) {
    int size = 0;
    for (int i = 0; i < map->size; i++) {
        Node* current = map->cell[i];
        while (current != NULL) {
            size++;
            current = current->next;
        }
    }
    return size;
}

/** cette fonction libere la hashmap*/

void freeHashMap(HashMap* map) {
    for (int i = 0; i < map->size; i++) {
        Node* current = map->cell[i];
        while (current != NULL) {
            Node* next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(map->cell);
    free(map);
}
