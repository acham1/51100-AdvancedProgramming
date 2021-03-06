/** Alan Cham
  * HW2 Q4 */

#ifndef P4A_TREE_H
#define P4A_TREE_H

typedef struct node_ {
    void* key;
    void* data;
    struct node_* left;
    struct node_* right;
} Node;

Node* create_tree(void);
Node* create_node(void);
void* find_obj(Node* tree, void* query_key, int (*cmp)(const void*, const void*));
int insert_node(Node* tree, void* new_key, void* new_object, int (*cmp)(const void*, const void*));
int free_tree(Node* tree);
int free_node(Node* node);
int delete_node(Node* tree, void* delete_key, int (*cmp)(const void*, const void*));

#endif