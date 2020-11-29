#ifndef _BST
#define _BST

struct Node {
	char* hostName;
	struct Node* left;
	struct Node* right;
	unsigned int ip;
};
typedef struct Node Node;

Node* bst_init();

Node* bst_new_node(const char* data, int ip);

Node* bst_insert(Node* node, const char* data, int ip);

Node* bst_find(Node* root, const char* data);

Node* bst_delete(Node* node, const char* data);

Node* bst_destruct(Node* root);

#endif // _BST