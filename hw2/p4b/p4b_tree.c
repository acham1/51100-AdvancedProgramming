/** Alan Cham
  * HW2 Q4 */

#include <p4b_tree.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
    if (node->right == NULL) {
        free_node(node);
    } else {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }
    return 0;
}

int free_node(Node* node) {
    if (node != NULL) {
        if (node->left) {
            free(node->left);
        }
        if (node->right) {
            free(node->right);
        }
        if (node->key) {
            free(node->key);
        }
        if (node->data) {
            free(node->data);
        }
        free(node);
    }
    return 0;
}

void* find_obj(Node *tree, void* query_key, int (*cmp)(const void*, const void*)) {
    Node* tmp_node;

    if (tree->left == NULL) {
        return NULL;
    } else {
        tmp_node = tree;
    } 
    while (tmp_node->right != NULL) {
        if (cmp(query_key, tmp_node->key) < 0) {
            tmp_node = tmp_node->left;
        } else {
            tmp_node = tmp_node->right;
        }
    }
    if (!cmp(tmp_node->key, query_key)) {
        return tmp_node->left;
    } else {
        return NULL;
    }
}

int insert_node(Node* tree, void* new_key, void* new_object, int (*cmp)(const void*, const void*)) {
    Node* tmp_node;
    Node* old_leaf, * new_leaf;

    if (tree->left == NULL) {
        tree->left = new_object;
        tree->key = new_key;
        tree->color = BLACK;
        tree->right = NULL;
        return insert_case1(tree);
    }
    tmp_node = tree;
    while (tmp_node->right != NULL) {
        if (cmp(new_key, tmp_node->key) < 0) {
            tmp_node = tmp_node->left;
        } else {
            tmp_node = tmp_node->right;
        }
    }
    if (!strcmp(tmp_node->key, new_key)) {
        return 1;
    }
    old_leaf = create_node();
    old_leaf->left = tmp_node->left;
    old_leaf->right = NULL;
    old_leaf->parent = tmp_node;
    old_leaf->key = tmp_node->key;
    old_leaf->color = BLACK;
    new_leaf = create_node();
    new_leaf->left = new_object;
    new_leaf->right = NULL;
    new_leaf->parent = tmp_node;
    new_leaf->key = new_key;
    new_leaf->color = BLACK;
    if (strcmp(tmp_node->key, new_key) < 0) {
        tmp_node->left = old_leaf;
        tmp_node->right = new_leaf;
        tmp_node->key = new_key;
    } else {
        tmp_node->left = new_leaf;
        tmp_node->right = old_leaf;
    }
    tmp_node->color = RED;
    return insert_case1(tmp_node);
}

int insert_case1(Node* n) {
    printf("insert_case1\n");
    if (n->parent == NULL) {
        n->color = BLACK;
        return 0;
    }
    return insert_case2(n);
}

int insert_case2(Node* n) {
    printf("insert_case2\n");
    if (n->parent->color == BLACK) {
        return 0;
    }
    return insert_case3(n);
}

int insert_case3(Node* n) {
    printf("insert case3\n");
    Node* u, * g;
    u = get_uncle(n);
    if (u != NULL && !is_leaf(u) && u->color == RED) {
        n->parent->color = BLACK;
        u->color = BLACK;
        g = get_grandparent(n);
        g->color = RED;
        return insert_case1(g);
    }
    return insert_case4(n);
}

int insert_case4(Node* n) {
    printf("insert case4\n");
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

int insert_case5(Node* n) {
    printf("insert case5\n");
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

    n->left = n->right;
    n->key = n->right->key;
    n->right = n->left->right;
    n->left->right = n->left->left;
    n->left->left = tmp_node;
    n->left->key = tmp_key;
    fix_parent(n, 1);
}

void rotate_right(Node* n) {
    Node* tmp_node = n->right;
    void* tmp_key = n->key;

    n->right = n->left;
    n->key = n->left->key;
    n->left = n->right->left;
    n->right->left = n->right->right;
    n->right->right = tmp_node;
    n->right->key = tmp_key;
    fix_parent(n, 1);
}

int delete_node(Node* tree, void* delete_key, int (*cmp)(const void*, const void*)) {
    Node* tmp_node, * upper_node, * other_node;

    if (tree->left == NULL) {
        return 0;
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
            free(other_node);
            free_node(tmp_node);
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
    Node* grand = node;
    if (grand == NULL) {
        return NULL;
    }
    grand = grand->parent;
    if (grand == NULL) {
        return NULL;
    }
    grand = grand->parent;
    return grand;
}

void fix_parent(Node* n, int repeat) {
    if (n == NULL || n->right == NULL) {
        return;
    }
    n->right->parent = n;
    n->left->parent = n;
    if (repeat) {
        fix_parent(n->right, 0);
        fix_parent(n->left, 0);
    }
}

int is_leaf(Node* n) {
    if (n == NULL) {
        return 0;
    } else {
        return n->right == NULL;
    }
}