#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char* key;
    int value;
    struct ListNode* next; 
} ListNode;

ListNode* creationChainon(char* K, int V) {
    if (K == NULL) {
        printf("Error: Key is NULL\n");
        exit(1);
    }

    ListNode* n = malloc(sizeof(ListNode));
    if (n == NULL) {
        printf("Memory allocation failed for ListNode\n");
        exit(1);
    }

    n->key = strdup(K);
    if (n->key == NULL) {
        printf("Memory allocation failed for key\n");
        exit(1);
    }

    n->value = V;
    n->next = NULL;

    return n;
}

void afficherListeRec(ListNode* chainon) {
    if (chainon != NULL) {
        printf("%s - %d -> ", chainon->key, chainon->value);
        afficherListeRec(chainon->next);
    } else {
        printf("End of the list\n");
    }
}

void supDebut(ListNode** pliste) {
    if (*pliste == NULL) {
        return;
    }
    ListNode* p = *pliste;
    *pliste = (*pliste)->next;
    free(p->key);
    free(p);
}

void suppressionChainon(ListNode** pliste, char* a) {
    if (*pliste == NULL) {
        printf("List is empty\n");
        return;
    }

    if (strcmp((*pliste)->key, a) == 0) {
        supDebut(pliste);
        return;
    }

    ListNode* p = *pliste;
    ListNode* p2 = NULL;

    while (p->next != NULL && strcmp(p->next->key, a) != 0) {
        p = p->next;
    }

    if (p->next != NULL && strcmp(p->next->key, a) == 0) {
        p2 = p->next;
        p->next = p2->next;
        free(p2->key);
        free(p2);
        return;
    }

    printf("Element not found in the list\n");
}

int main() {
    // Exemple d'utilisation
    ListNode* firstNode = creationChainon("alize", 42);
    ListNode* secondNode = creationChainon("pauline", 73);

    // Liaison des nœuds
    firstNode->next = secondNode;

    // Affichage de la liste
    afficherListeRec(firstNode);

    // Suppression d'un élément
    suppressionChainon(&firstNode, "pauline");

    // Affichage de la liste après suppression
    afficherListeRec(firstNode);

    // Libération de la mémoire
    while (firstNode != NULL) {
        ListNode* temp = firstNode;
        firstNode = firstNode->next;
        free(temp->key);
        free(temp);
    }

    return 0;
}
