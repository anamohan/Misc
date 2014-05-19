// Boundary Traversal of binary tree
// Given a binary tree, print boundary nodes of the binary tree Anti-Clockwise 
// starting from the root. 
// For example, boundary traversal of the following tree is “20 8 4 10 14 25 22″
// 					20
// 			    8       22
// 		4   12        25
// 		   10 14  
#include <iostream>
#include <cstdio>

using namespace std;

struct node {
	struct node *left;
	struct node *right;
	int data;
};

void print_leaves(struct node *root) {
	if (root == NULL) return;
	print_leaves(root->left);
	if (root->left == NULL && root->right == NULL) {
		printf(" %d ", root->data);
	}
	print_leaves(root->right);
}

void print_left_boundary(struct node *root) {
	if (root == NULL) return;
	if (root->left != NULL) {
		printf(" %d ", root->data);
		print_left_boundary(root->left);
	} else if (root->right != NULL) {
		printf(" %d ", root->data);
		print_left_boundary(root->right);
	}
}

void print_right_boundary(struct node *root) {
	if (root == NULL) return;
	if (root->right != NULL) {
		print_right_boundary(root->right);
		printf(" %d ", root->data);
		
	} else if (root->left != NULL) {
		print_right_boundary(root->left);
		printf(" %d ", root->data);
	}
}

void print_boundary(struct node *root) {
	if (root == NULL) return;
	printf("%d ",root->data);
	print_left_boundary(root->left);
	print_leaves(root->left);
	print_leaves(root->right);
	print_right_boundary(root->right);       
}

struct node *newNode(int data) {
    struct node *temp = new node;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

int main() {
	struct node *root         = newNode(20);
    root->left                = newNode(8);
    root->left->left          = newNode(4);
    root->left->right         = newNode(12);
    root->left->right->left   = newNode(10);
    root->left->right->right  = newNode(14);
    root->right               = newNode(22);
    root->right->right        = newNode(25);

    print_boundary(root);
	return 0;
}