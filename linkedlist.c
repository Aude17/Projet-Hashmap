#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list != NULL) {
        list->head = NULL;
    }
    return list;
}

/**Cette fonction ajoute un nouveau nœud (Node) à une liste chaînée (LinkedList) en utilisant une clé (key) et une valeur (value) */

void addNode(LinkedList* list, char* key, int value) {  
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = list->head;
    list->head = newNode;
}

Node* findNodeByKey(const LinkedList* list, const char* key) {
    Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; /** Key not found*/
}

void removeNode(LinkedList* list, const char* key) {
    Node* current = list->head;
    Node* prev = NULL;

    /** Search for the key in the list*/
    while (current != NULL && strcmp(current->key, key) != 0) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        /** Key found, remove the node*/
        if (prev == NULL) {
            /** The node is the first in the list*/
            list->head = current->next;
        } else {
            prev->next = current->next;
        }

        free(current->key);
        free(current);
        printf("Key '%s' removed from the LinkedList\n", key);
    } else {
        printf("Key '%s' not found in the LinkedList\n", key);
    }
}

void printLinkedList(const LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("(%s, %d) ", current->key, current->value);
        current = current->next;
    }
    printf("\n");
}

int sizeLinkedList(const LinkedList* list) {
    int size = 0;
    Node* current = list->head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

void freeLinkedList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->key);
        free(current);
        current = next;
    }
    free(list);
}
