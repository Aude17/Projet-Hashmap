#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List {
    char* key;
    int value;
    struct List* next;
}List ;

typedef struct Tree {
    char* key;
    int h;
    struct List* values;
    struct Tree* fg;
    struct Tree* fd;
} Tree;

// Fonctions pour l'arbre
Tree* createTree(int h, List* list) {
    if (list == NULL) {
        return NULL;
    }

    Tree* root = (Tree*)malloc(sizeof(Tree));
    if (root == NULL) {
        fprintf(stderr, "Memory allocation failed for Tree\n");
        exit(EXIT_FAILURE);
    }

    root->h = h;
    root->values = list;
    root->fg = NULL;
    root->fd = NULL;

    return root;
}

void displayValuesList(List* values) {
    List* current = values;
    while (current != NULL) {
        if (current->key != NULL) {
            printf("(%s, %d) ", current->key, current->value);
        }
        current = current->next;
    }
}


void displayNode(Tree* node) {
    if (node != NULL) {
        printf("(%s, %d) -> ", node->key, node->h);
        displayValuesList(node->values);
        printf("\n");

        displayNode(node->fg);
        displayNode(node->fd);
    }
}

void freeTree(Tree* root) {
    if (root != NULL) {
        freeTree(root->fg);
        freeTree(root->fd);

        List* currentList = root->values;
        while (currentList != NULL) {
            List* temp = currentList;
            currentList = currentList->next;
            free(temp->key);
            free(temp);
        }

        free(root->key);
        free(root);
    }
}


Tree* addTreeNode(Tree* root, char* key, int h, int value) {
    if (root == NULL) {
        Tree* newNode = (Tree*)malloc(sizeof(Tree));
        if (newNode == NULL) {
            fprintf(stderr, "Allocation failed\n");
            exit(EXIT_FAILURE);
        }
        newNode->key = strdup(key);
        newNode->h = h;
        newNode->fg = NULL;
        newNode->fd = NULL;
        newNode->values = (List*)malloc(sizeof(List));
        if (newNode->values == NULL) {
            fprintf(stderr, "Allocation failed for List\n");
            exit(EXIT_FAILURE);
        }
        newNode->values->key = strdup(key);
        newNode->values->value = value;
        newNode->values->next = NULL;
        return newNode;
    }

    int compareResult = strcmp(key, root->key);

    if (compareResult < 0) {
        root->fg = addTreeNode(root->fg, key, h, value);
    } else if (compareResult > 0) {
        root->fd = addTreeNode(root->fd, key, h, value);
    } else {
        List* newValue = (List*)malloc(sizeof(List));
        if (newValue == NULL) {
            fprintf(stderr, "Allocation failed for List\n");
            exit(EXIT_FAILURE);
        }
        newValue->key = strdup(key);
        newValue->value = value;
        newValue->next = root->values;
        root->values = newValue;
    }

    return root;
}

Tree* insertion_update_Tree(char* key, int value, Tree* root) {
    if (root == NULL) {
        return addTreeNode(proot, key, value);
    } else if (strcmp(key, root->key) == 0) {
        // La clé existe déjà, mettez à jour la valeur associée
        List* values = root->values;
        while (values != NULL) {
            if (strcmp(values->key, key) == 0) {
                values->value = value;
                return root;
            }
            values = values->next;
        }
        // Si la clé n'est pas trouvée dans les valeurs existantes, ajoutez-la
        root->values = addListNode(root->values, key, value);
        return root;
    } else {
        // Recherche récursive pour insérer ou mettre à jour la valeur
        if (strcmp(key, root->key) < 0) {
            root->fg = insertion_update_Tree(key, value, root->fg);
        } else {
            root->fd = insertion_update_Tree(key, value, root->fd);
        }
        return root;
    }
}

int hash(char* key) {
    char firstLetter = key[0];
    if ((firstLetter >= 'a' && firstLetter <= 'z') || (firstLetter >= 'A' && firstLetter <= 'Z')) {
        return (int)(firstLetter < 'a' ? firstLetter - 'A' + 1 : firstLetter - 'a' + 1);
    } else {
        // Return a default value if the key doesn't start with a letter
        return 0;
    }
}

int main() {
    // Création du premier élément de la première liste
    List* myList1 = (List*)malloc(sizeof(List));
    if (myList1 == NULL) {
        fprintf(stderr, "Allocation failed for List\n");
        exit(EXIT_FAILURE);
    }

    myList1->key = strdup("ella");
    myList1->value = 42;
    myList1->next = NULL;

    // Création du deuxième élément de la première liste
    myList1->next = (List*)malloc(sizeof(List));
    if (myList1->next == NULL) {
        fprintf(stderr, "Allocation failed for List\n");
        exit(EXIT_FAILURE);
    }
    myList1->next->key = strdup("aude");
    myList1->next->value = 73;
    myList1->next->next = NULL;

    // Parcours de la première liste pour créer et afficher les arbres
    List* current1 = myList1;
    while (current1 != NULL) {
        int h = hash(current1->key); // Calcul de la valeur de hachage pour l'élément actuel
        printf("La valeur de hachage pour %s est : %d\n", current1->key, h);

        // Création d'un arbre pour chaque élément de la première liste
        Tree* myTree1 = createTree(h, current1);
        printf("Arbre pour %s:\n", current1->key);
        displayNode(myTree1);
        freeTree(myTree1);

        current1 = current1->next;
    }

    // Libération de la mémoire de la première liste
    current1 = myList1;
    while (current1 != NULL) {
        List* temp = current1;
        current1 = current1->next;
        free(temp->key);
        free(temp);
    }

    return 0;
}


