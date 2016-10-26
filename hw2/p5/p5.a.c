/** Alan Cham
  * HW 2 #5a 
  * Non-recursive BST verification */

#include <stdlib.h>
#include <limits.h>

// typedef struct Tree_node {
//     struct Tree_node *left, *right;
//     int data;
// } Tree_node;// 

// int main(void) {
//     return 0;
// }

// returns 1 if valid BST, 0 otherwise
int isBST(Tree_node* tree) {
    const int default_stack_len = 100;
    int stack_len = default_stack_len; // max space in stack
    Tree_node** stack;
    Tree_node* tmp;
    int min, max;
    int stack_pos;                    // position of next free index in stack
    int* mins;
    int* maxs;

    if (tree == NULL) {               // treat empty tree as valid
        return 1;
    }

    stack = malloc(sizeof(Tree_node*) * default_stack_len);
    mins = malloc(sizeof(int) * default_stack_len);
    maxs = malloc(sizeof(int) * default_stack_len);
    stack_pos = 1;
    stack[0] = tree;
    mins[0] = INT_MIN;
    maxs[0] = INT_MAX;

    while (stack_pos > 0) {
        if (stack_pos >= stack_len-2) {
            stack_len *= 2;
            stack = realloc(stack, sizeof(Tree_node*) * stack_len);
            mins = realloc(mins, sizeof(int) * stack_len);
            maxs = realloc(maxs, sizeof(int) * stack_len);
        }
        --stack_pos;
        tmp = stack[stack_pos];
        min = mins[stack_pos];
        max = maxs[stack_pos];
        if (tmp->data > max || tmp->data < min) {
            free(stack);
            free(mins);
            free(maxs);
            return 0;
        }
        if (tmp->left != NULL) {
            if (tmp->data == INT_MIN) {    // no int less than INT_MIN; left child impossible
                free(stack);
                free(mins);
                free(maxs);
                return 0;
            }
            stack[stack_pos] = tmp->left;  
            mins[stack_pos] = min;         // cannot violate parent trees
            maxs[stack_pos] = tmp->data-1; // must be less than current
            ++stack_pos;
        }
        if (tmp->right != NULL) {
            if (tmp->data == INT_MAX) {    // no int more than INT_MAX; right child impossible
                free(stack);
                free(mins);
                free(maxs);
                return 0;
            }
            stack[stack_pos] = tmp->right;
            mins[stack_pos] = tmp->data+1; // must be greater than current
            maxs[stack_pos] = max;         // cannot violate parent trees
            ++stack_pos;
        }
    }
    free(stack);
    free(mins);
    free(maxs);
    return 1;
}