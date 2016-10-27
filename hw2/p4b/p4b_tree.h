/** Alan Cham
  * HW2 Q4 */

#ifndef P4B_TREE_H
#define P4B_TREE_H

typedef enum color_ {
    RED, BLACK, DOUBLE_BLACK
} Color;

typedef struct node_ {
    Color color;
    void* key;
    void* data;
    int is_leaf;
    struct node_* left;
    struct node_* right;
    struct node_* parent;
} Node;

Node* create_tree(void);
Node* create_node(void);
void print_tree(Node* node);
Node* create_leaf(Node* parent);
void* find_obj(Node* tree, void* key, int (*cmp)(const void*, const void*));
Node* find_node(Node* tree, void* key, int (*cmp)(const void*, const void*));
int insert_node(Node* tree, void* key, void* object, int (*cmp)(const void*, const void*));
int free_tree(Node* tree);
int delete_node(Node* tree, void* key, int (*cmp)(const void*, const void*));
int removeAboveExternal(Node* node);
int delete_case1(Node* n);
int delete_case2(Node* n);
int delete_case3(Node* n);
int delete_case4(Node* n);
Node* get_uncle(Node* node);
Node* get_grandparent(Node* node);
int insert_case1(Node* n);
int insert_case2(Node* n);
int insert_case3(Node* n);
int insert_case4(Node* n);
int insert_case5(Node* n);
void rotate_right(Node* n);
void rotate_left(Node* n);
void fix_parent(Node* n, int repeat);
Node* get_successor(Node* n);
Node* get_sibling(Node* n);
#endif