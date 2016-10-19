/** Alan Cham
  * HW2 Q4 */

#include <p4.tree.h>

typedef struct node {
    void* key;
    void* data;
    struct node* left;
    struct node* right;
} Node;

Node* create_node(void) {
    return malloc(sizeof(Node));
}

Node* create_tree(void) {
    Node* tree = create_node();
    tree->left = NULL
    return tree;
}

