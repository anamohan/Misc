#include <iostream>
#include <cstdio>

using namespace std;


struct node {
	struct node *left;
	struct node *right;
	int data;
};

void mirror(struct node *root) {
	if (root == NULL) return;
	mirror(root->left);
	mirror(root->right);

	struct node *temp = root->left;
	root->left = root->right;
	root->right = temp;
}

int main() {
	return 0;
}