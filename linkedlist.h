#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

LinkedList* createLinkedList();
void addNode(LinkedList* list, char* key, int value);
Node* findNodeByKey(const LinkedList* list, const char* key);
void removeNode(LinkedList* list, const char* key);
void printLinkedList(const LinkedList* list);
int sizeLinkedList(const LinkedList* list);
void freeLinkedList(LinkedList* list);

#endif // LINKEDLIST_H
