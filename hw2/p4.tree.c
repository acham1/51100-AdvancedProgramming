/** Alan Cham
  * HW2 Q4 */

#include <p4_tree.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Node* create_node(void) {
    Node* new_node = malloc(sizeof(Node));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->key = NULL;
    new_node->data = NULL;
    return new_node;
}

Node* create_tree(void) {
    Node* tree = create_node();
    tree->left = NULL;
    return tree;
}

int free_tree(Node* tree) {
	return 0;
}

int free_node(Node* node) {
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

	printf("insert 1\n");
	if (tree->left == NULL) {
		tree->left = new_object;
		tree->key = new_key;
		tree->right = NULL;
		printf("insert 2\n");
		return 0;
	} else {
		tmp_node = tree;
		while (tmp_node->right != NULL) {
			printf("insert 4\n");
			if (cmp(new_key, tmp_node->key) < 0) {
				tmp_node = tmp_node->left;
			} else {
				tmp_node = tmp_node->right;
			}
		}
		printf("insert3\n");
	}
	if (!strcmp(tmp_node->key, new_key)) {
		return 1;
	}
	old_leaf = create_node();
	old_leaf->left = tmp_node->left;
	old_leaf->key = tmp_node->key;
	old_leaf->right = NULL;
	new_leaf = create_node();
	new_leaf->left = new_object;
	new_leaf->right = NULL;
	new_leaf->key = new_key;
	if (strcmp(tmp_node->key, new_key) < 0) {
		tmp_node->left = old_leaf;
		tmp_node->right = new_leaf;
		tmp_node->key = new_key;
	} else {
		tmp_node->left = new_leaf;
		tmp_node->right = old_leaf;
	}
	return 0;
}