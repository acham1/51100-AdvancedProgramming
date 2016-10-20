/** Alan Cham
  * HW2 Q4 */

#ifndef P4B_TREE_H
#define P4B_TREE_H

typedef enum color_ {
    RED, BLACK
} Color;

typedef struct node_ {
    Color color;
    void* key;
    void* data;
    struct node_* left;
    struct node_* right;
    struct node_* parent;
} Node;

Node* create_tree(void);
Node* create_node(void);
void* find_obj(Node* tree, void* query_key, int (*cmp)(const void*, const void*));
int insert_node(Node* tree, void* new_key, void* new_object, int (*cmp)(const void*, const void*));
int free_tree(Node* tree);
int free_node(Node* node);
int delete_node(Node* tree, void* delete_key, int (*cmp)(const void*, const void*));
int get_uncle(Node* node);
int get_grandparent(Node* node);

#endif