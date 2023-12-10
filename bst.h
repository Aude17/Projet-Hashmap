#ifndef BST_H
#define BST_H

typedef struct TreeNode {
    char* key;
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* root;
} BinarySearchTree;

BinarySearchTree* createBST();
void insertBST(BinarySearchTree* tree, char* key, int value);
TreeNode* findNodeByKeyBST(const BinarySearchTree* tree, const char* key);
void removeNodeBST(BinarySearchTree* tree, const char* key);
void printBST(const BinarySearchTree* tree);
int sizeBST(const BinarySearchTree* tree);
void freeBST(BinarySearchTree* tree);

#endif // BST_H
