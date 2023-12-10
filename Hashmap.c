#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct List {
    char* key;
    int value;
    struct List* next;
} List;

typedef struct Tree {
    char* key;
    int h;
    struct List* values;
    struct Tree* fg;
    struct Tree* fd;
} Tree;

typedef struct HashMap {
    Tree* proot;
    int size;
    // Vous avez déclaré une variable 'cell' ici, mais vous ne l'utilisez pas
} HashMap;

HashMap* createHashmap() {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    if (map == NULL) {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }
    map->size = 0;
    map->proot = NULL;
    return map;
}

int hash(char* chaine) {
    int i = 0, nbhash = 0;
    for (i = 0; chaine[i] != '\0'; i++) {
        nbhash += chaine[i];
    }
    nbhash %= 100;
    return nbhash;
}

List* addListNode(List* values, char* key, int value) {
    List* newNode = (List*)malloc(sizeof(List));
    if (newNode == NULL) {
        fprintf(stderr, "Allocation failed for List\n");
        exit(EXIT_FAILURE);
    }

    newNode->key = strdup(key);
    if (newNode->key == NULL) {
        fprintf(stderr, "Allocation failed for key\n");
        exit(EXIT_FAILURE);
    }

    newNode->value = value;
    newNode->next = values;

    return newNode;
}

void freeList(List* values) {
    while (values != NULL) {
        List* temp = values;
        values = values->next;
        free(temp->key);
        free(temp);
    }
}

Tree* addTreeNode(Tree* root, char* key, int h, int value) {
    if (root == NULL) {
        Tree* newNode = (Tree*)malloc(sizeof(Tree));
        if (newNode == NULL) {
            fprintf(stderr, "Allocation failed for Tree\n");
            exit(EXIT_FAILURE);
        }

        newNode->key = strdup(key);
        if (newNode->key == NULL) {
            fprintf(stderr, "Allocation failed for key\n");
            exit(EXIT_FAILURE);
        }

        newNode->h = h;
        newNode->fg = NULL;
        newNode->fd = NULL;
        newNode->values = addListNode(NULL, key, value);

        return newNode;
    }

    int compareResult = strcmp(key, root->key);

    if (compareResult < 0) {
        root->fg = addTreeNode(root->fg, key, h, value);
    } else if (compareResult > 0) {
        root->fd = addTreeNode(root->fd, key, h, value);
    } else {
        root->values = addListNode(root->values, key, value);
    }

    return root;
}

void freeTree(Tree* root) {
    if (root != NULL) {
        freeTree(root->fg);
        freeTree(root->fd);
        freeList(root->values);
        free(root->key);
        free(root);
    }
}

void displayNode(Tree* node) {
    if (node != NULL) {
        printf("(%s, %d) -> ", node->key, node->h);
        List* values = node->values;
        while (values != NULL) {
            printf("(%s, %d) ", values->key, values->value);
            values = values->next;
        }
        printf("\n");

        displayNode(node->fg);
        displayNode(node->fd);
    }
}

void display(HashMap* map) {
    displayNode(map->proot);
}

int sizeHM(HashMap* map) {
    if (map == NULL) {
        return 0;
    }
    return map->size;
}

int addHM(HashMap* map, char* key, int value) {
    if (map == NULL || key == NULL) {
        return 0;
    }
    
    int h = hash(key); // Calcul de la valeur de hachage pour la clé donnée

    // Ajout de la clé et de la valeur à l'arbre de la HashMap
    map->proot = addTreeNode(map->proot, key, h, value);
    map->size++;

    return 1;
}

int* getHM(HashMap* map, char* key) {
    if (map == NULL || key == NULL) {
        return NULL;
    }

    /*int h = nbhash(key);*/

    // Recherche de l'arbre correspondant à la clé
    Tree* current = map->proot;
    while (current != NULL) {
        int compareResult = strcmp(key, current->key);

        if (compareResult < 0) {
            current = current->fg;
        } else if (compareResult > 0) {
            current = current->fd;
        } else {
            // Clé trouvée, rechercher la valeur associée
            List* values = current->values;
            while (values != NULL) {
                if (strcmp(values->key, key) == 0) {
                    int* result = (int*)malloc(sizeof(int));
                    if (result == NULL) {
                        fprintf(stderr, "Allocation failed\n");
                        exit(EXIT_FAILURE);
                    }
                    *result = values->value;
                    return result;
                }
                values = values->next;
            }
            // La clé n'a pas été trouvée dans les valeurs existantes
            return NULL;
        }
    }

    // La clé n'a pas été trouvée dans l'arbre
    return NULL;
}

bool updateHM(HashMap* map, char* key, int value) {
    if (map == NULL || key == NULL) {
        return false;
    }

    int h = hash(key); // Calcul de la valeur de hachage pour la clé donnée

    // Recherche de l'arbre correspondant à la clé
    Tree* current = map->proot;
    while (current != NULL) {
        int compareResult = strcmp(key, current->key);

        if (compareResult < 0) {
            current = current->fg;
        } else if (compareResult > 0) {
            current = current->fd;
        } else {
            // Clé trouvée, mettre à jour la valeur associée
            List* values = current->values;
            while (values != NULL) {
                if (strcmp(values->key, key) == 0) {
                    values->value = value;
                    return true;
                }
                values = values->next;
            }
            // Si la clé n'est pas trouvée dans les valeurs existantes, ajoutez-la
            current->values = addListNode(current->values, key, value);
            return true;
        }
    }

    // Si la clé n'est pas trouvée dans l'arbre, créez un nouvel arbre avec la clé et la valeur
    map->proot = addTreeNode(map->proot, key, h, value);
    map->size++;
    return true;
}

void displayList(List* list) {
    if (list == NULL) {
        printf("Empty\n");
        return;
    }

    List* current = list;
    while (current != NULL) {
        printf("(%s, %d) ", current->key, current->value);
        current = current->next;
    }
    printf("\n");
}

/*void displayTree(Tree* node) {
    if (node != NULL) {
        printf("(%s, %d) -> ", node->key, node->h);
        displayList(node->cell);
        printf("\n");

        displayTree(node->fg);
        displayTree(node->fd);
    }
}
*/
void display(HashMap* map) {
    if (map == NULL || map->proot == NULL) {
        printf("HashMap is empty.\n");
        return;
    }

    printf("HashMap Elements:\n");
    displayTree(map->proot);
}


int main() {
    HashMap* map = createHashmap();

    addHM(map, "antoine", 12); // Ajout manquant
    addHM(map, "aude", 14);
    addHM(map, "maman", 57);
    addHM(map, "mathou", 89);
    addHM(map, "guillaume", 102);
    display(map);
    printf("Size of the HashMap: %d\n", sizeHM(map)); // Affichage de la taille pour montrer l'utilisation de la map

    // Vous pouvez également afficher le contenu de la HashMap en utilisant la fonction display(map);

    return 0;
}
