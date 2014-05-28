#include <cstdio>
#include <cassert>
#include <cstdlib>

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

// A more difficult problem is to write a function InsertNth() which can insert a new node at
// any index within a list. Push() is similar, but can only insert a node at the head end of the
// list (index 0). The caller may specify any index in the range [0..length], and the new node
// should be inserted so as to be at that index.
/*
A more general version of Push().
Given a list, an index 'n' in the range 0..length,
and a data element, add a new node to the list so
that it has the given index.
*/
void InsertNth(struct node** headRef, int index, int data) {
	assert(*headRef != NULL);
	struct node *newNode;
	if (index == 0) {
		newNode = (node*) malloc(sizeof(node));
		newNode->data = data;
		newNode->next = *headRef;
		*headRef = newNode;
	} else {
		struct node *current = *headRef;
		for (int i = 0; i < index - 1; i++) {
			assert(current != NULL);
			current = current->next;
		}
		assert(current != NULL);
		newNode = (node*) malloc(sizeof(node));
		newNode->data = data;
		struct node *temp = current->next;
		current->next = newNode;
		newNode->next = temp;
	}
}

// Write a SortedInsert() function which given a list that is sorted in increasing order, and a
// single node, inserts the node into the correct sorted position in the list. While Push()
// allocates a new node to add to the list, SortedInsert() takes an existing node, and just
// rearranges pointers to insert it into the list. There are many possible solutions to this
// problem.
void SortedInsert(struct node** headRef, struct node* newNode) {
	if (*headRef == NULL || (*headRef)->data >= newNode->data) {
		newNode->next = *headRef;
		*headRef = newNode;
	} else {
		// Locate the node before the point of insertion
		struct node* current = *headRef;
		while (current->next != NULL && current->next->data < newNode->data) {
				current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

// Write an InsertSort() function which given a list, rearranges its nodes so they are sorted in
// increasing order. It should use SortedInsert().
// Given a list, change it to be in sorted order (using SortedInsert()).
void InsertSort(struct node** headRef) {
	assert(*headRef != NULL);
	struct node *current = *headRef;
	struct node *result = NULL;
	struct node *next;

	while (current != NULL) {
		next = current->next;
		SortedInsert(&result, current);
		current = next;
	}
	*headRef = result;
}

// Write an Append() function that takes two lists, 'a' and 'b', appends 'b' onto the end of 'a',
// and then sets 'b' to NULL (since it is now trailing off the end of 'a'). Here is a drawing of
// a sample call to Append(a, b) with the start state in gray and the end state in black. At the
// end of the call, the 'a' list is {1, 2, 3, 4}, and 'b' list is empty.
// Append 'b' onto the end of 'a', and then set 'b' to NULL.
void Append(struct node** aRef, struct node** bRef) {
	if (*aRef == NULL) {
		*aRef = *bRef;
	} else {
		struct node *aCurrent = *aRef;
		while (aCurrent->next != NULL) {
			aCurrent = aCurrent->next;
		}
		aCurrent->next = *bRef;
	}
	*bRef = NULL;
}

/*
Split the nodes of the given list into front and back halves,
and return the two lists using the reference parameters.
If the length is odd, the extra node should go in the front list.
*/
void FrontBackSplit(struct node* source,
struct node** frontRef, struct node** backRef) {
	if (source == NULL || source->next == NULL) {
		*frontRef = source;
		*backRef = NULL;
	} else {
		struct node *slow = source;
		struct node *fast = source->next;
		while (fast != NULL) {
			fast = fast->next;
			if (fast != NULL) {
				fast = fast->next;
				slow = slow->next;
			}
		}
		*backRef = slow->next;
		slow->next = NULL;
		*frontRef = source;
	}
}

// Write a RemoveDuplicates() function which takes a list sorted in increasing order and
// deletes any duplicate nodes from the list. Ideally, the list should only be traversed once.
/*
Remove duplicates from a sorted list.
*/
void RemoveDuplicates(struct node* head) {
	assert(head != NULL);

	struct node *current = head;

	if (current == NULL) return;

	while (current->next != NULL) {
		if (current->data == current->next->data) {
			struct node* nextNext = current->next->next;
			free(current->next);
			current->next = nextNext;
		} else {
			current = current->next;
		}
	}
}

/*
Take the node from the front of the source, and move it to
the front of the dest.
It is an error to call this with the source list empty.
*/
void MoveNode(struct node** destRef, struct node** sourceRef) {
	struct node *newNode = *sourceRef;
	assert(newNode != NULL);
	*sourceRef = newNode->next;
	newNode->next = *destRef;
	*destRef = newNode;
}

/*
Given the source list, split its nodes into two shorter lists.
If we number the elements 0, 1, 2, ... then all the even elements
should go in the first list, and all the odd elements in the second.
The elements in the new lists may be in any order.
*/
void AlternatingSplit(struct node* source,
struct node** aRef, struct node** bRef) {
	if (source == NULL) return;
	struct node *current = source;
	struct node *aCurr = NULL, *bCurr = NULL;
	while (current != NULL) {
		struct node *newNode = current->next;
		if (current->data % 2 == 0) {
			if (aCurr == NULL) {
				aCurr = current;
				*aRef = aCurr;
			} else {
				aCurr->next = current;
			}
			aCurr = current;
			aCurr->next = NULL;
		} else {
			if (bCurr == NULL) {
				bCurr = current;
				*bRef = bCurr;
			} else {
				bCurr->next = current;
			}
			bCurr = current;
			bCurr->next = NULL;
		}
	}
}

/*
Merge the nodes of the two lists into a single list taking a node
alternately from each list, and return the new list.
*/
struct node* ShuffleMerge(struct node* a, struct node* b) {
	struct node* result;
	struct node* recur;
	if (a == NULL || b == NULL) {
		return (a == NULL) ? b : a;
	} else {
		recur = ShuffleMerge(a->next, b->next);
		result = a; // one node from a
		a->next = b; // one from b
		b->next = recur; // then the rest
		return(result);
	}
}

/*
Takes two lists sorted in increasing order, and
splices their nodes together to make one big
sorted list which is returned.
*/
struct node* SortedMerge(struct node* a, struct node* b) {
	if (a == NULL || b == NULL) {
		return (a == NULL) ? b : a;
	} else {
		struct node *result;
		if (a->data <= b->data) {
			result = a;
			result->next = SortedMerge(a->next, b);
		} else {
			result = b;
			result->next = SortedMerge(a, b->next);
		}
		return result;
	}
}

// (This problem requires recursion) Given FrontBackSplit() and SortedMerge(), it's pretty
// easy to write a classic recursive MergeSort(): split the list into two smaller lists,
// recursively sort those lists, and finally merge the two sorted lists together into a single
// sorted list. Ironically, this problem is easier than either FrontBackSplit() or
// SortedMerge().
void MergeSort(struct node** headRef) {
	struct node* head = *headRef;
	struct node* a;
	struct node* b;
	// Base case -- length 0 or 1
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}
	FrontBackSplit(head, &a, &b);
	MergeSort(&a); 
	MergeSort(&b);
	*headRef = SortedMerge(a, b);
}

/*
Compute a new sorted list that represents the intersection
of the two given sorted lists.
*/
struct node* SortedIntersect(struct node* a, struct node* b) {
	if (a == NULL || b == NULL) {
		return NULL;
	} else {
		struct node* result;
		if (a-> data == b->data) {
			result = (node*) malloc(sizeof(node));
			result->data = a->data;
			result->next = SortedIntersect(a->next, b->next);
			return result;
		} else if (a->data > b->data) {
			return SortedIntersect(a, b->next);
		} else {
			return SortedIntersect(a->next, b);
		}
	}
}

/*
Reverse the given linked list by changing its .next pointers and
its head pointer. Takes a pointer (reference) to the head pointer.
*/
void Reverse(struct node** headRef) {
	struct node *current = *headRef;
	struct node *previous = NULL, *next = NULL;

	while (current != NULL) {
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	*headRef = previous;
}

/*
Recursively reverses the given linked list by changing its .next
pointers and its head pointer in one pass of the list.
*/
void RecursiveReverse(struct node** headRef) {
	if (*headRef == NULL) return;

	struct node* first = *headRef;
	struct node* rest  = first->next;

	if (rest == NULL) return;

	RecursiveReverse(&rest);
	first->next->next = first;
	first->next = NULL;
	*headRef = rest;
}

int main() {
	return 0;
}