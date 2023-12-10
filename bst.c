#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

BinarySearchTree* createBST() {
    BinarySearchTree* tree = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    if (tree != NULL) {
        tree->root = NULL;
    }
    return tree;
}

/** Cette fonction createTreeNode est destinée à créer un nouveau nœud de type TreeNode pour une structure d'arbre binaire*/
TreeNode* createTreeNode(char* key, int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode != NULL) {
        newNode->key = strdup(key);
        newNode->value = value;
        newNode->left = newNode->right = NULL;
    }
    return newNode;
}

/** cette fonction insert un node dans l'arbre binaire de recherche*/

void insertBSTRecursive(TreeNode** root, char* key, int value) {
    if (*root == NULL) {
        *root = createTreeNode(key, value);
    } else {
        if (strcmp(key, (*root)->key) < 0) {
            insertBSTRecursive(&((*root)->left), key, value);
        } else if (strcmp(key, (*root)->key) > 0) {
            insertBSTRecursive(&((*root)->right), key, value);
        } else {
            /** Key already exists, update the value*/
            (*root)->value = value;
        }
    }
}

void insertBST(BinarySearchTree* tree, char* key, int value) {
    insertBSTRecursive(&(tree->root), key, value);
}

TreeNode* findNodeByKeyBSTRecursive(const TreeNode* root, const char* key) {
    if (root == NULL || strcmp(key, root->key) == 0) {
        return (TreeNode*)root;
    }

    if (strcmp(key, root->key) < 0) {
        return findNodeByKeyBSTRecursive(root->left, key);
    } else {
        return findNodeByKeyBSTRecursive(root->right, key);
    }
}

TreeNode* findNodeByKeyBST(const BinarySearchTree* tree, const char* key) {
    return findNodeByKeyBSTRecursive(tree->root, key);
}


TreeNode* findMin(TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}
void removeNodeBSTRecursive(TreeNode** root, const char* key) {
    if (*root == NULL) {
        return;
    }

    if (strcmp(key, (*root)->key) < 0) {
        removeNodeBSTRecursive(&((*root)->left), key);
    } else if (strcmp(key, (*root)->key) > 0) {
        removeNodeBSTRecursive(&((*root)->right), key);
    } else {
        /** Node with only one child or no child*/
        if ((*root)->left == NULL) {
            TreeNode* temp = (*root)->right;
            free((*root)->key);
            free(*root);
            *root = temp;
        } else if ((*root)->right == NULL) {
            TreeNode* temp = (*root)->left;
            free((*root)->key);
            free(*root);
            *root = temp;
        } else {
            /** Node with two children*/
            TreeNode* temp = findMin((*root)->right);
            (*root)->key = strdup(temp->key);
            (*root)->value = temp->value;
            removeNodeBSTRecursive(&((*root)->right), temp->key);
        }
    }
}

void removeNodeBST(BinarySearchTree* tree, const char* key) {
    removeNodeBSTRecursive(&(tree->root), key);
}



void printBSTInOrder(const TreeNode* root) {
    if (root != NULL) {
        printBSTInOrder(root->left);
        printf("(%s, %d) ", root->key, root->value);
        printBSTInOrder(root->right);
    }
}

void printBST(const BinarySearchTree* tree) {
    printBSTInOrder(tree->root);
    printf("\n");
}

int sizeBSTRecursive(const TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + sizeBSTRecursive(root->left) + sizeBSTRecursive(root->right);
}

int sizeBST(const BinarySearchTree* tree) {
    return sizeBSTRecursive(tree->root);
}

void freeBSTRecursive(TreeNode* root) {
    if (root != NULL) {
        freeBSTRecursive(root->left);
        freeBSTRecursive(root->right);
        free(root->key);
        free(root);
    }
}

void freeBST(BinarySearchTree* tree) {
    freeBSTRecursive(tree->root);
    free(tree);
}
