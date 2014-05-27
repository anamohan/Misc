#include <cstdio>
#include <cassert>

using namespace std;


struct node {
	int data;
	struct node *next;
};

// Write a Count() function that counts the number of times a given int occurs in a list. The
// code for this has the classic list traversal structure as demonstrated in Length().

int Count(struct node* head, int searchFor) {
	if (head == NULL) return 0;
	int count = 0;
	struct node *current = head;

	while (current != NULL) {
		if (current->data == searchFor) {
			count++;
		}
		current = current->next;
	}
	return 0;
}

// Write a GetNth() function that takes a linked list and an integer index and returns the data
// value stored in the node at that index position. GetNth() uses the C numbering convention
// that the first node is index 0, the second is index 1, ... and so on. So for the list {42, 13,
// 666} GetNth() with index 1 should return 13. The index should be in the range [0..length-
// 1]. If it is not, GetNth() should assert() fail (or you could implement some other error
// case strategy).

// Given a list and an index, return the data
// in the nth node of the list. The nodes are numbered from 0.
// Assert fails if the index is invalid (outside 0..lengh-1).
int GetNth(struct node* head, int index) {
	int pos = 0;
	struct node *current = head;
	while (current != NULL) {
		if (pos == index) {
			return current->data;
		}
		current = current->next;
		pos++;
	}
	assert("index is greater than length of list");
	return -1;
}

// Write a function DeleteList() that takes a list, deallocates all of its memory and sets its
// head pointer to NULL (the empty list).
void DeleteList(struct node **headRef) {
	struct node *current = *headRef;
	while (current != NULL) {
		struct node* next = current->next;
		free(current);
		current = current->next;
	}
	*headRef = NULL;
}

/*
The opposite of Push(). Takes a non-empty list
and removes the front node, and returns the data
which was in that node.
*/
int Pop(struct node** headRef) {
	struct node *current = *headRef;

	assert(current != NULL);

	*headRef = current->next;
	int data = current->data;
	free(current);
	return data;
}

int main() {
	return 0;
}