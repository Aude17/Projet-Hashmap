#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "bst.h"
#include "hashmap.h"

int main() {
    /** LinkedList */
    LinkedList* linkedList = createLinkedList();

    while (1) {
        char key[100];   // Adjust the size as needed
        int value;

        printf("Enter a key (or 'exit' to quit) for LinkedList: ");
        scanf("%s", key);

        if (strcmp(key, "exit") == 0) {
            break; // Exit the loop if the user enters 'exit'
        }

        printf("Enter a value: ");
        scanf("%d", &value);

        addNode(linkedList, key, value);
    }

    printf("Size of the LinkedList: %d\n", sizeLinkedList(linkedList));

    /** Remove a key-value pair from LinkedList*/
    char keyToRemoveLinkedList[100];
    printf("Enter a key to remove from LinkedList: ");
    scanf("%s", keyToRemoveLinkedList);

    removeNode(linkedList, keyToRemoveLinkedList);

    /** Print the updated size of the LinkedList*/
    printf("Size of the LinkedList after removal: %d\n", sizeLinkedList(linkedList));

    /** Print the updated LinkedList*/
    printLinkedList(linkedList);

    freeLinkedList(linkedList);

    /** Binary Search Tree (BST)*/
    BinarySearchTree* bst = createBST();

    while (1) {
        char key[100];   
        int value;

        printf("Enter a key (or 'exit' to quit) for BST: ");
        scanf("%s", key);

        if (strcmp(key, "exit") == 0) {
            break; /** Exit the loop if the user enters 'exit'*/
        }

        printf("Enter a value: ");
        scanf("%d", &value);

        insertBST(bst, key, value);
    }

    printf("Size of the BST: %d\n", sizeBST(bst));

    /** Remove a key-value pair from BST*/
    char keyToRemoveBST[100];
    printf("Enter a key to remove from BST: ");
    scanf("%s", keyToRemoveBST);

    removeNodeBST(bst, keyToRemoveBST);

    /** Print the updated size of the BST*/
    printf("Size of the BST after removal: %d\n", sizeBST(bst));

    /** Print the updated BST*/
    printBST(bst);

    freeBST(bst);

    /** HashMap*/
    HashMap* myMap = createHashMap(26); /** Adjust the size as needed*/

    while (1) {
        char key[100];   /** Adjust the size as needed*/
        int value;

        printf("Enter a key (or 'exit' to quit) for HashMap: ");
        scanf("%s", key);

        if (strcmp(key, "exit") == 0) {
            break; /** Exit the loop if the user enters 'exit'*/
        }

        printf("Enter a value: ");
        scanf("%d", &value);

        addHashMap(myMap, key, value);
    }

    printf("Size of the HashMap: %d\n", sizeHashMap(myMap));

    /** Remove a key-value pair from HashMap*/
    char keyToRemoveHashMap[100];
    printf("Enter a key to remove from HashMap: ");
    scanf("%s", keyToRemoveHashMap);

    removeKeyHashMap(myMap, keyToRemoveHashMap);

    /** Print the updated size of the HashMap*/
    printf("Size of the HashMap after removal: %d\n", sizeHashMap(myMap));

    /** Print the updated HashMap*/
    printHashMap(myMap);

    freeHashMap(myMap);

    return 0;
}
