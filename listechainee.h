#ifndef LISTECHAINEE_H
#define LISTECHAINEE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char* key;
    int value;
    struct ListNode* next;
} ListNode;

ListNode* creationChainon(char* K, int V);
void afficherListeRec(ListNode* chainon);
void supDebut(ListNode** pliste);
void suppressionChainon(ListNode** pliste, char* a);

#endif /* LISTECHAINEE_H */
