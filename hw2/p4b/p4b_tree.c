/** Alan Cham
  * HW2 Q4 */

#include <p4b_tree.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Insertion code based on notes/slides
// Deletion based on purdue link from Brass Textbook, notes, and https://en.wikipedia.org/wiki/Red%E2%80%93black_tree

Node* create_node(void) {
    Node* new_node = malloc(sizeof(Node));
    new_node->color = RED;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->key = NULL;
    new_node->data = NULL;
    new_node->is_leaf = 0;
    return new_node;
}

Node* create_leaf(Node* parent) {
    Node* leaf = create_node();
    leaf->parent = parent;
    leaf->color = BLACK;
    leaf->is_leaf = 1;
    return leaf;
}

Node* create_tree(void) {
    Node* tree = create_node();
    tree->color = BLACK;
    return tree;
}

// return 1 if problem, 0 otherwise
int free_tree(Node* node) {
    int stat1 = 0;
    int stat2 = 0;
    if (node == NULL) {
        return 0;
    }
    stat1 = free_tree(node->right);
    stat2 = free_tree(node->left);
    free(node->data);
    free(node->key);
    free(node);
    return stat1 || stat2;
}

Node* find_node(Node* tree, void* key, int (*cmp)(const void*, const void*)) {
    if (tree == NULL || tree->key == NULL || tree->is_leaf) {
        return NULL; 
    } else if (cmp(tree->key, key) == 0) {
        return tree;
    } else if (cmp(key, tree->key) > 0) {
        return find_node(tree->right, key, cmp);
    } else {
        return find_node(tree->left, key, cmp);
    }    
}

void* find_obj(Node *tree, void* key, int (*cmp)(const void*, const void*)) {
    if (tree == NULL || tree->key == NULL || tree->is_leaf) {
        return NULL; 
    } else if (cmp(tree->key, key) == 0) {
        return tree->data;
    } else if (cmp(key, tree->key) > 0) {
        return find_obj(tree->right, key, cmp);
    } else {
        return find_obj(tree->left, key, cmp);
    }
}

void print_tree(Node* node) {
    if (node->key != NULL && !node->is_leaf) {
        printf("node: %s %d", (char*) node->key, node->color);
        printf(" | left: %s %d", (char*) node->left->key, node->left->color);
        printf(" | right: %s %d\n", (char*) node->right->key, node->right->color);
        print_tree(node->left);
        print_tree(node->right);
    }
}

// return 1 if problem, 0 otherwise
int insert_node(Node* tree, void* key, void* object, int (*cmp)(const void*, const void*)) {
            print_tree(tree);
    if (tree == NULL) {
        return 1;
    } else if (key == NULL || object == NULL) { // NULL keys not permitted
        return 1;
    } else if (tree->is_leaf) {
        return 1;
    } else if (tree->key == NULL && tree->parent == NULL) { // empty tree
        tree->key = key;
        tree->data = object;
        tree->color = RED;
        tree->is_leaf = 0;
        tree->left = create_leaf(tree);
        tree->right = create_leaf(tree);
        return insert_case1(tree);
    }
    if (cmp(key, tree->key) > 0) {
        if (tree->right->is_leaf) {
            tree->right->right = create_leaf(tree->right);
            tree->right->left = create_leaf(tree->right);
            tree->right->key = key;
            tree->right->data = object;
            tree->right->parent = tree;
            tree->right->color = RED;
            tree->right->is_leaf = 0;
            return insert_case1(tree->right);
        } else {
            return insert_node(tree->right, key, object, cmp);
        }
    } else if (cmp(key, tree->key) == 0) {
        return 1;
    } else {
        if (tree->left->is_leaf) {
            tree->left->left = create_leaf(tree->left);
            tree->left->right = create_leaf(tree->left);
            tree->left->key = key;
            tree->left->data = object;
            tree->left->parent = tree;
            tree->left->color = RED;
            tree->left->is_leaf = 0;
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
    Node* u, *g;
    u = get_uncle(n);
    if (u != NULL && u->color == RED) {
        n->parent->color = BLACK;
        u->color = BLACK;
        g = get_grandparent(n);
        g->color = RED;
        return insert_case1(g);
    } else {
        return insert_case4(n);
    }
    return 1;
}

// return 1 if problem, 0 otherwise
int insert_case4(Node* n) {
    Node* g = get_grandparent(n);
    if (n == n->parent->right && n->parent == g->left) {
        rotate_left(n->parent);
//        n = n->left;
    } else if (n == n->parent->left && n->parent == g->right) {
        rotate_right(n->parent);
//        n = n->right;
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
    Color tmp_color = n->color;

    n->left = n->right;
    n->key = n->right->key;
    n->data = n->right->data;
    n->color= n->right->color;

    n->right = n->left->right;
    n->left->right = n->left->left;
    n->left->left = tmp_node;
    n->left->key = tmp_key;
    n->left->data = tmp_data;
    n->left->color = tmp_color;
    fix_parent(n, 1);
}

void rotate_right(Node* n) {
    Node* tmp_node = n->right;
    void* tmp_key = n->key;
    void* tmp_data = n->data;
    Color tmp_color = n->color;

    n->right = n->left;
    n->key = n->left->key;
    n->data = n->left->data;
    n->color = n->left->color;

    n->left = n->right->left;
    n->right->left = n->right->right;
    n->right->right = tmp_node;

    n->right->key = tmp_key;
    n->right->data = tmp_data;
    n->right->color = tmp_color;

    fix_parent(n, 1);
}

// return 1 if problem, 0 otherwise
int delete_node(Node* tree, void* key, int (*cmp)(const void*, const void*)) {
    print_tree(tree);
    Node* to_delete, *tmp;

    to_delete = find_node(tree, key, cmp);
    if (to_delete == NULL) {
        return 1;
    }
    // now to_delete is a valid non-leaf node
    if (!to_delete->left->is_leaf && !to_delete->right->is_leaf) {
        tmp = get_successor(to_delete);
        free(to_delete->key);
        free(to_delete->data);
        to_delete->key = tmp->key;
        to_delete->data = tmp->data;
        return removeAboveExternal(tmp);
    } else {    
        free(to_delete->data);
        free(to_delete->key);
        return removeAboveExternal(to_delete);
    }
    return 1;
}

int removeAboveExternal(Node* node) {
    Node* child;

    if (!node->left->is_leaf) {
        child = node->left;
    } else {
        child = node->right;
    }
    free(child == node->left ? node->right : node->left);
    child->parent = node->parent;
    if (node->parent != NULL && node == node->parent->left) {
        node->parent->left = child;
    } else if (node->parent != NULL && node == node->parent->right) {
        node->parent->right = child;
    } else { // Brass case 2: u is new root
        node->key = child->key;
        node->data = child->data;
        node->color = BLACK; 
        node->is_leaf = 0;
        node->left = child->left;
        if (child->left != NULL) {
            node->left->parent = node;
        }
        node->right = child->right;
        if (child->right != NULL) {
            node->right->parent = node;
        }
        free(child);
        return 0;
    }
    if (node->color == BLACK) {
        if (child->color == RED) {
            child->color = BLACK;
            free(node);
            return 0;
        } else {
            free(node);
            return delete_case1(child);
        }
    } else {
        free(node);
        return 0;
    }
    return 1;
}

int delete_case1(Node* node) {
    if (node->parent == NULL) {
        node->is_leaf = 0;
        node->color = BLACK;
        return 0;
    } else {
        return delete_case2(node);
    }
}

int delete_case2(Node* node) {
    if (node->color == RED) {
        node->color = BLACK;  
        return 0;
    } else {
        return delete_case3(node);
    }
}

int delete_case3(Node* node) {
    Node* upper = node->parent;
    Node* other = get_sibling(node);


    if (node == upper->left) {
        if (upper->color == BLACK && other->color == BLACK && other->left->color == BLACK) {
            rotate_left(upper);
            upper->left->color = RED;
            upper->color = BLACK;
            return delete_case1(upper);
        } else if (upper->color == BLACK && other->color == BLACK && other->left->color == RED) {
            rotate_right(other);
            rotate_left(upper);
            upper->left->color = upper->right->color = upper->color = BLACK;
            return 0;
        } else if (upper->color == BLACK && other->color == RED && other->left->left->color == BLACK) {
            rotate_left(upper);
            rotate_left(upper->left);
            upper->left->left->color = RED;
            upper->left->color = upper->color = BLACK;
            return 0;
        } else if (upper->color == BLACK && other->color == RED && other->left->left == RED) {
            rotate_left(upper);
            rotate_right(upper->left->right);
            rotate_left(upper->left);
            upper->left->left->color = upper->left->right->color = BLACK;
            upper->left->color = RED;
            upper->color = BLACK;
            return 0;
        } else if (upper->color == RED && other->color == BLACK && other->left->color == BLACK) {
            rotate_left(upper);
            upper->left->color = RED;
            upper->color = BLACK;
            return 0;
        } else if (upper->color == RED && other->color == BLACK && other->left->color == RED) {
            rotate_right(other);
            rotate_left(upper);
            upper->left->color = upper->right->color = BLACK;
            upper->color = RED;
            return 0;
        }
    } else {
        return delete_case4(node);
    }
    return 1;
}

int delete_case4(Node* node) {
    Node* upper = node->parent;
    Node* other = get_sibling(node);

    if (node == upper->right) {
        if (upper->color == BLACK && other->color == BLACK && other->right->color == BLACK) {
            rotate_right(upper);
            upper->right->color = RED;
            upper->color = BLACK;
            return delete_case1(upper);
        } else if (upper->color == BLACK && other->color == BLACK && other->right->color == RED) {
            rotate_left(other);
            rotate_right(upper);
            upper->left->color = upper->right->color = upper->color = BLACK;
            return 0;
        } else if (upper->color == BLACK && other->color == RED && other->right->right->color == BLACK) {
            rotate_right(upper);
            rotate_right(upper->right);
            upper->right->right->color = RED;
            upper->right->color = upper->color = BLACK;
            return 0;
        } else if (upper->color == BLACK && other->color == RED && other->right->right->color == RED) {
            rotate_right(upper);
            rotate_left(upper->right->left);
            rotate_right(upper->right);
            upper->right->right->color = upper->right->left->color = BLACK;
            upper->right->color = RED;
            upper->color = BLACK;
            return 0;
        } else if (upper->color == RED && other->color == BLACK && other->right->color == BLACK) {
            rotate_right(upper);
            upper->right->color = RED;
            upper->color = BLACK;
            return 0;
        } else if (upper->color == RED && other->color == BLACK && other->right->color == RED) {
            rotate_left(other);
            rotate_right(upper);
            upper->left->color = upper->right->color = BLACK;
            upper->color = RED;
            return 0;
        }
    }
    return 1;
}

Node* get_successor(Node* n) {
    n = n->right;
    while (n->left != NULL && !n->left->is_leaf) {
        n = n->left;
    }
    return n;
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

Node* get_sibling(Node* n) {
    if (n->parent == NULL) {
        return NULL;
    } else {
        return (n == n->parent->left) ? n->parent->right : n->parent->left;
    }
}