// Write a program to print all path whose sum is equal 
// to a given number path must start from the root node 
// and it may or may not end at the leaf.

#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

struct node {
	struct node *left;
	struct node *right;
	int data;
};
void print_queue(queue<struct node*> q) {
	if (!q.empty()) {
		while (!q.empty()) {
			struct node *temp = q.front();
			q.pop();
			printf(" %d ", temp->data);
		}
	}
}
void print_paths(struct node *root, int sum, queue <struct node*> q) {
	if (sum == 0) {
		print_queue(q);
		printf("\n");
		return;
	} else if (root == NULL || root->data > sum) {
		return;
	} else if (root->data == sum) {
		print_queue(q);
		printf(" %d ", root->data);
		printf("\n");
		return;
	}
	q.push(root);
	if (root->left != NULL) {
		print_paths(root->left, sum - root->data, q);	
	} 
	if (root->right != NULL) {
		print_paths(root->right, sum - root->data, q);	
	}
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
    root->right               = newNode(20);
    root->right->right        = newNode(25);
    queue<struct node*> q;
    print_paths(root, 28, q);
	return 0;
}