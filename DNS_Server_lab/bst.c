
#define _CRT_SECURE_NO_WARNINGS

#include "bst.h"
#include <stdbool.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

/// <summary> 
/// Allocate memory for one node;
/// </summary>
/// <returns>Pointer to allocated memory</returns>
Node* bst_init() {
	Node* newNode = malloc(sizeof(Node));
	memset(newNode, 0, sizeof(Node));
	return newNode;
}

/// <summary>
/// Create new node on heap and return
/// pointer to newly created object
/// </summary>
/// <param name="data">: String host name</param>
/// <param name="ip">: Int corresponding ip</param>
/// <returns></returns>
Node* bst_new_node(const char* hostName, int ip) {
	Node* newNode = bst_init();
	newNode->hostName = calloc(strlen(hostName) + 1, sizeof(char));
	strncpy(newNode->hostName, hostName, strlen(hostName));
	newNode->ip = ip;
	return newNode;
}

/// <summary>
/// Compare strings considering lengths and NULLs
/// </summary>
/// <param name="a">: First string to compare</param>
/// <param name="b">: Second string to compare</param>
/// <returns>Zero if equal
/// <para>Negative if a is smaller</para>
/// <para>Positive if a is greater</para>
/// </returns>
static int strcmpl(const char* a, const char* b) {
	if (a == NULL) {
		return false;
	}
	else if (b == NULL) {
		return true;
	}
	else if (strlen(a) != strlen(b)) {
		return strlen(a) - strlen(b);
	}
	else {
		return strcmp(a, b);
	}
}
/// <summary>
/// Inserts new node into tree or updates specified node
/// </summary>
/// <param name="node">: Current node to insert into</param>
/// <param name="data">: Host name</param>
/// <param name="ip">: Correspoiding ip address</param>
/// <returns>Pointer to newly created node or to current node if it was empty</returns>
Node* bst_insert(Node* node, const char* hostToInsert, int ipToInsert) {
	// if tree is empty then create new node
	if (node == NULL) {
		node = bst_new_node(hostToInsert, ipToInsert);
	}
	// if node exists but empty then update current node
	else if (node->left == NULL && node->right == NULL && node->hostName == NULL && node->ip == 0) {
		node->hostName = calloc(strlen(hostToInsert) + 1, sizeof(char));
		strncpy(node->hostName, hostToInsert, strlen(hostToInsert));
		node->left = NULL;
		node->right = NULL;
	}
	else if (strcmpl(hostToInsert, node->hostName) <= 0) {
		node->left = bst_insert(node->left, hostToInsert, ipToInsert);
	}
	else if (strcmpl(hostToInsert, node->hostName) > 0) {
		node->right = bst_insert(node->right, hostToInsert, ipToInsert);
	}

	return node;
}
/// <summary>
/// Searches for specified host name in tree
/// </summary>
/// <param name="root">: Node to start from</param>
/// <param name="data">: Host name to be found</param>
/// <returns>Pointer to found node or NULL if not found</returns>
Node* bst_find(Node* start, const char* hostName) {
	if (start == NULL) {
		return start;
	}
	else if (strcmpl(hostName, start->hostName) == 0) {
		// found
		return start;
	}
	else if (strcmpl(hostName, start->hostName) < 0) {
		// search in left sub tree
		return bst_find(start->left, hostName);
	}
	else {
		// search in right sub tree
		return bst_find(start->right, hostName);
	}
}

/// <summary>
/// Finds the minimum node in specified tree or subtree.
/// <para>Minimum value is always in leftmost leaf of tree.</para>
/// </summary>
/// <param name="node">: Tree or sub tree to search in</param>
/// <returns>Pointer to found node</returns>
static Node* bst_min(Node* start) {
	while (start->left != NULL) {
		start = start->left;
	}
	return start;
}
/// <summary>
/// Checks if specified node does not contain any data
/// </summary>
/// <param name="node">: Node to check</param>
static inline bool bst_node_empty(Node* node) {
	return node->hostName == NULL && node->left == NULL && node->right == NULL && node->ip == 0;
}
/// <summary>
/// Finds and deletes specified node from tree
/// </summary>
/// <param name="node">: Node to start search from</param>
/// <param name="data">: Host name to find and delete</param>
/// <returns>Pointer to node that replaced deleted node</returns>
Node* bst_delete(Node* start, const char* value) {
	if (start == NULL) {
		return start;
	}
	else if (bst_node_empty(start)) {
		// no heap memory for Node::hostName
		free(start);
		start = NULL;
		return start;
	}
	// search value in lef subtree
	else if (strcmpl(value, start->hostName) < 0) {
		start->left = bst_delete(start->left, value);
	}
	// search in right subtree
	else if (strcmpl(value, start->hostName) > 0) {
		start->right = bst_delete(start->right, value);
	}
	// Found
	else {
		// no children
		if (start->left == NULL && start->right == NULL) {
			// first free memory of hostName
			free(start->hostName);
			free(start);
			start = NULL;
			return start;
		}
		// 1 child, right
		else if (start->left == NULL) {
			// Swap node and its right child
			Node* temp = start;
			start = start->right;
			// delete node
			free(temp->hostName);
			free(temp);
			return start;
		}
		//1 child, left
		else if (start->right == NULL) {
			// Swap node and its left child
			Node* temp = start;
			start = start->left;
			free(temp->hostName);
			free(temp);
			return start;
		}
		// 2 children
		else {
			// find min value in right subtree 
			Node* min = bst_min(start->right);
			char* tmpPtr = realloc(start->hostName, sizeof(char) * (strlen(min->hostName) + 1));
			if (tmpPtr == NULL) {
				printf("**************\n");
				printf("*realloc ERROR*\n");
				printf("***************\n");
			}
			start->hostName = tmpPtr;
			// replace data of current node with data if min node
			strncpy(start->hostName, min->hostName, strlen(min->hostName));
			start->ip = min->ip;
			// delete min node
			start->right = bst_delete(start->right, min->hostName);
		}
	}
	return start;
}
/// <summary>
/// Destructrs the tree and frees allocated memory
/// </summary>
/// <param name="root">: Node to start from</param>
/// <returns>NULL if successfuly deleted</returns>
Node* bst_destruct(Node* start) {
	while (start != NULL) {
		start = bst_delete(start, start->hostName);
	}
	return start;
}
