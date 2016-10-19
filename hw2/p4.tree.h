/** Alan Cham
  * HW2 Q4 */

typedef struct node {
    void* key;
    void* data;
    struct node* left;
    struct node* right;
} Node;

Node* create_tree(void);
Node* create_node(void);