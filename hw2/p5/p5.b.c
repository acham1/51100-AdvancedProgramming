/** Alan Cham
  * HW 2 #5b */

#include <stdlib.h>
#include <limits.h>

// typedef struct Tree_node {
//     struct Tree_node *left, *right;
//     int data;
// } Tree_node;

int isBST_recurse(Tree_node* tree);
static int BST_recurser(Tree_node* tree, int min, int max);

// int main(void) {
//     return 0;
// }

// returns 1 if valid BST, 0 otherwise
int isBST_recurse(Tree_node* tree) {
    return BST_recurser(tree, INT_MIN, INT_MAX);
}

// returns 1 if valid BST, 0 otherwise
static int BST_recurser(Tree_node* tree, int min, int max) {
    if (tree == NULL) { // treat empty tree as valid
        return 1;
    }
    if (tree->data < min || tree->data > max) {
        return 0;       // violates parent
    }
    if (tree->left != NULL) {
        if (tree->data == INT_MIN) {
            return 0;   // no int less than INT_MIN; left child impossible
        }
        if (!BST_recurser(tree->left, min, tree->data-1)) {
            return 0;   // left subtree should be bound by current min, current data
        }
    }
    if (tree->right != NULL) {
        if (tree->data == INT_MAX) {
            return 0;   // no int more than INT_MAX; right child impossible
        }
        if (!BST_recurser(tree->right, tree->data+1, max)) {
            return 0;   // right subtree should be bound by current max, current data
        }
    }
    return 1;
}