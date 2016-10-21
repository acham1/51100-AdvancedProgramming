/** Alan Cham
  * HW 2 #5b */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
typedef struct Tree_node {
    struct Tree_node *left, *right;
    int data;
} Tree_node;

int main(void) {
    return 0;
}
*/


// returns 1 if valid BST, 0 otherwise
int isBST_recurse(Tree_node* tree) {
    if (tree == NULL) {
        return 1;
    }
    if (tree->left != NULL && tree->left->data >= tree->data) {
        return 0;
    }
    if (tree->right != NULL && tree->right->data <= tree->data) {
        return 0;
    }
    return isBST_recurse(tree->left) && isBST_recurse(tree->right);
}