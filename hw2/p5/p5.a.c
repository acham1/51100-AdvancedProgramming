/** Alan Cham
  * HW 2 #5a */

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
int isBST(Tree_node* tree) {
    const int default_stack_len = 100;
    int stack_len; // max space in stack
    int stack_pos; // position of next free index in stack
    Tree_node** stack;
    Tree_node** new_stack;
    Tree_node* tmp;

    stack_pos = 1;
    stack_len = default_stack_len;
    stack = malloc(sizeof(Tree_node*) * default_stack_len);
    stack[0] = tree;

    while (stack_pos > 0) {
        if (stack_pos > stack_len-2) {
            stack_len *= 2;
            new_stack = malloc(sizeof(Tree_node*) * stack_len);
            memcpy(new_stack, stack, stack_pos * sizeof(Tree_node*));
            free(stack);
            stack = new_stack;
        }
        tmp = stack[--stack_pos];
        if (tmp->left != NULL) {
            if (tmp->left->data >= tmp->data) {
                free(stack);
                return 0;
            }
            stack[stack_pos++] = tmp->left;
        }
        if (tmp->right != NULL) {
            if (tmp->right->data <= tmp->data) {
                free(stack);
                return 0;
            }
            stack[stack_pos++] = tmp->right;
        }
    }
    return 1;
}