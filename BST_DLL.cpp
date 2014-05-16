// Convert Binary Search Tree (BST) to Sorted Doubly-Linked List
// Use Left Pointer for prev node
// Use Right Pointer for next node
#include <iostream>

struct Node {
	int data;
	Node *left;
	Node *right;
};


void treeToDoublyList(Node *p, Node *& prev, Node *& head) {
	if (!p) return;
	treeToDoublyList(p->left, prev, head);

	// Now after calling treeToDoublyList on left subtree
	// prev is last node of linked list formed by converting
	// left subtree to doubly link list

	// head-------> prev 
	// <--------------| 
	p->left = prev;
	if (prev) {
		prev->right = p;
	} else {
		head = p;
	}

	Node *right = p->right;
	head->left = p;
	p->right = head;
	prev = p;
	treeToDoublyList(right, prev, head);
}