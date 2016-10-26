/** Alan Cham
  * HW2 Q4 */

#include <p4b_tree.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Insertion code based on notes/slides
// Deletion based on purdue link from notes

Node* create_node(void) {
    Node* new_node = malloc(sizeof(Node));
    new_node->color = RED;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->key = NULL;
    new_node->data = NULL;
    return new_node;
}

Node* create_tree(void) {
    Node* tree = create_node();
    tree->color = BLACK;
    return tree;
}

int free_tree(Node* node) {
    if (node->right != NULL) {
        free_tree(node->right);
    }
    if (node->left != NULL) {
        free_tree(node->left);
    }
    free(node->data);
    free(node->key);
    free(node);
    return 0;
}

void* find_obj(Node *tree, void* key, int (*cmp)(const void*, const void*)) {
    if (tree == NULL) {
        return NULL; 
    } else if (cmp(tree->key, key) == 0) {
        return tree->data;
    } else if (cmp(key, tree->key) > 0) {
        return find_obj(tree->right, key, cmp);
    } else {
        return find_obj(tree->left, key, cmp);
    }
}

// return 1 if problem, 0 otherwise
int insert_node(Node* tree, void* key, void* object, int (*cmp)(const void*, const void*)) {
    if (tree == NULL) {
        return 1;
    } else if (key == NULL) { // NULL keys not permitted
        return 1;
    } else if (tree->key == NULL) { // empty tree
        tree->key = key;
        tree->data = object;
        return insert_case1(tree);
    }
    if (cmp(key, tree->key) > 0) {
        if (tree->right == NULL) {
            tree->right = create_node();
            tree->right->key = key;
            tree->right->data = object;
            tree->right->parent = tree;
            return insert_case1(tree->right);
        } else {
            return insert_node(tree->right, key, object, cmp);
        }
    } else if (cmp(key, tree->key) == 0) {
        return 1;
    } else {
        if (tree->left == NULL) {
            tree->left = create_node();
            tree->left->key = key;
            tree->left->data = object;
            tree->left->parent = tree;
            return insert_case1(tree->left);
        } else {
            return insert_node(tree->left, key, object, cmp);
        }
    }
}

// return 1 if problem, 0 otherwise
int insert_case1(Node* n) {
    if (n->parent == NULL) {
        n->color = BLACK;
        return 0;
    }
    return insert_case2(n);
}

// return 1 if problem, 0 otherwise
int insert_case2(Node* n) {
    if (n->parent->color == BLACK) {
        return 0;
    }
    return insert_case3(n);
}

// return 1 if problem, 0 otherwise
int insert_case3(Node* n) {
    Node* u, * g;
    u = get_uncle(n);
    if (u != NULL && u->color == RED) {
        n->parent->color = BLACK;
        u->color = BLACK;
        g = get_grandparent(n);
        g->color = RED;
        return insert_case1(g);
    }
    return insert_case4(n);
}

// return 1 if problem, 0 otherwise
int insert_case4(Node* n) {
    Node* g = get_grandparent(n);
    if (n == n->parent->right && n->parent == g->left) {
        rotate_left(n->parent);
        n = n->left;
    } else if (n == n->parent->left && n->parent == g->right) {
        rotate_right(n->parent);
        n = n->right;
    }
    return insert_case5(n);
}

// return 1 if problem, 0 otherwise
int insert_case5(Node* n) {
    Node* g = get_grandparent(n);
    n->parent->color = BLACK;
    g->color = RED;
    if (n == n->parent->left) {
        rotate_right(g);
    } else {
        rotate_left(g);
    }
    return 0;
}

void rotate_left(Node* n) {
    Node* tmp_node = n->left;
    void* tmp_key = n->key;
    void* tmp_data = n->data;

    n->left = n->right;
    n->key = n->right->key;
    n->data = n->right->data;

    n->right = n->left->right;
    n->left->right = n->left->left;
    n->left->left = tmp_node;
    n->left->key = tmp_key;
    n->left->data = tmp_data;

    fix_parent(n, 1);
}

void rotate_right(Node* n) {
    Node* tmp_node = n->right;
    void* tmp_key = n->key;
    void* tmp_data = n->data;

    n->right = n->left;
    n->key = n->left->key;
    n->data = n->left->data;

    n->left = n->right->left;
    n->right->left = n->right->right;
    n->right->right = tmp_node;
    n->right->key = tmp_key;
    n->right->data = tmp_data;

    fix_parent(n, 1);
}

int delete_node(Node* tree, void* delete_key, int (*cmp)(const void*, const void*)) {
    Node* tmp_node, * upper_node, * other_node;

    if (tree->left == NULL) {
        return 1;
    } else if (tree->right == NULL) {
        if (cmp(tree->key, delete_key) == 0) {
            free(tree->left);
            free(tree->key);
            tree->key = NULL;
            tree->left = NULL;
            return 0;
        } else {
            return 1;
        }
    } else {
        tmp_node = tree;
        while (tmp_node->right != NULL) {
            upper_node = tmp_node;
            if (cmp(delete_key, tmp_node->key) < 0) {
                tmp_node = upper_node->left;
                other_node = upper_node->right;
            } else {
                tmp_node = upper_node->right;
                other_node = upper_node->left;
            }
        }
        if (cmp(tmp_node->key, delete_key)) {
            return 1;
        } else {
            upper_node->key = other_node->key;
            upper_node->left = other_node->left;
            upper_node->right = other_node->right;
            upper_node->color = other_node->color;
            free(other_node);
            if (upper_node->color == RED) {
                return insert_case1(upper_node);
            }
            return 0;
        }
    }
}

Node* get_uncle(Node* node) {
    Node* grand = get_grandparent(node);
    if (grand == NULL) {
        return NULL;
    }
    if (grand->left == node->parent) {
        return grand->right;
    } else {
        return grand->left;
    }
    return NULL;
}

Node* get_grandparent(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    node = node->parent;
    if (node == NULL) {
        return NULL;
    }
    return node->parent;
}

void fix_parent(Node* n, int repeat) {
    if (n == NULL || repeat < 0) {
        return;
    }
    if (n->left != NULL) {
        n->left->parent = n;
        fix_parent(n->left, repeat-1);
    }
    if (n->right != NULL) {
        n->right->parent = n;
        fix_parent(n->right, repeat-1);
    }
}