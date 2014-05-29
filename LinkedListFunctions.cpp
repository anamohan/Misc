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

// Given a linked list, reverse alternate nodes and append them to end of list. 
// Extra allowed space is O(1) 
// Examples

// Input List:  1->2->3->4->5->6
// Output List: 1->3->5->6->4->2

// Input List:  12->14->16->18->20
// Output List: 12->16->20->18->14

// The idea is to maintain two linked lists, 
//  one list of all odd positioned nodes (1, 3, 5 in above example) 
//   and other list of all even positioned nodes (6, 4 and 2 in above example). Following are detailed steps.
// 1) Traverse the given linked list which is considered as odd list. 
//     Do following for every visited node.
// a) If the node is even node, remove it from odd list 
//     and add it to the front of even node list. 
//     Nodes are added at front to keep the reverse order.
// 2) Append the even node list at the end of odd node list.

void rearrange(struct node **odd) {
	if (*odd == NULL || (*odd)->next == NULL || (*odd)->next->next == NULL) return;
	node *evenNode, *next, *current;
	evenNode = (*odd)->next;
	(*odd)->next = (*odd)->next->next;
	evenNode->next = NULL;
	

	current = *odd;
	int pos = 2;
	while (current != NULL) {
		if (pos % 2 != 0) {
			current = current->next;
		} else {
			next = current->next;
			current->next = evenNode;
			evenNode = current;
			current = next;
		}
		pos++;
	}
	current->next = evenNode;
}

// Given a singly linked list, write a function to swap elements pairwise. 
// For example, if the linked list is 1->2->3->4->5->6->7 
// then the function should change it to 2->1->4->3->6->5->7, 
// and if the linked list is 1->2->3->4->5->6 
// then the function should change it to 2->1->4->3->6->5

struct node *pairWiseSwap(struct node* head) {
    // Base Case: The list is empty or has only one node
    if (head == NULL || head->next == NULL)
        return head;
 
    // Store head of list after two nodes
    struct node* rest = head->next->next;
 
    // Change head
    struct node* newhead = head->next;
 
    // Change next of second node
    head->next->next = head;
 
    // Recur for remaining list and change next of head
    head->next = pairWiseSwap(rest);
 
    // Return new head of modified list
    return newhead;
}

// Given two linked lists, insert nodes of second list into first list at alternate positions 
// of first list.
// For example, if first list is 5->7->17->13->11 
// and second is 12->10->2->4->6, 
// the first list should become 5->12->7->10->17->2->13->4->11->6 
// and second list should become empty.
void merge(struct node *a, struct node **b) {
	if (*b == NULL) return;
	struct node *aCurr = a;
	struct node *bCurr = b;
	while (aCurr != NULL && bCurr != NULL) {
		struct node *aNext = aCurr->next;
		struct node *bNext = bCurr->next;
		
		bCurr->next = aNext;
		aCurr->next = bCurr;

		bCurr = bNext;
		aCurr = aNext;
	}
	*b = bCurr;
}

// Returns the last node of the list
struct node *getTail(struct node *cur) {
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

// QuickSort on a singly link list
void partition(struct node *head, struct node *end,
			struct node **newHead, struct node **newEnd) {
	struct node *pivot = end;
	struct node *prev = NULL, *curr = head, *tail = pivot;
	// During partition, both the head and end of the list might change
    // which is updated in the newHead and newEnd variables
    while (curr != pivot) {
    	
        if (curr->data < pivot->data) {
        	if (*newHead == NULL) {
        		// First node that has a value less than the pivot - becomes
        		// the new head
        		*newHead = curr;
        	} 
        	prev = curr;
        	curr = curr->next;
        } else {
        	// if curr node is greater than pivot
        	// Move curr node to next to tail and 
        	// change tail
        	if (prev) {
        		prev->next = curr->next;
        	}
        	struct node *temp = curr->next;
        	curr->next = NULL;
        	tail->next = curr;
        	tail = curr;
        	curr = temp;
        }
    }
    if (*newHead == NULL) {
    	*newHead = pivot;
    }
    *newEnd = tail;
    return pivot;
}

struct node *quickSortRecur(struct node *head, struct node *end) {
	if (head == NULL || head == end) {
		return head;
	}
	node *newHead = NULL, *newEnd = NULL;
	// Partition the list, newHead and newEnd will be updated
    // by the partition function
    struct node *pivot = partition(head, end, &newHead, &newEnd);
    // If pivot is the smallest element - no need to recur for
    // the left part.
    if (newHead != pivot) {
    	// Set the node before the pivot node as NULL
    	struct node *temp = newHead;
    	while (temp->next != pivot) {
    		temp = temp->next;
    	}
    	temp->next = NULL;
    	newHead = quickSortRecur(newHead, temp);
    	temp = getTail(newHead);
    	temp->next = pivot;
    }
    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

// The main function for quick sort. This is a wrapper over recursive
// function quickSortRecur()
void quickSort(struct node **headRef) {
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    return;
}

// Given a linked list and two integers M and N. 
// Traverse the linked list such that you retain M nodes then delete next N nodes, 
// continue the same till end of the linked list.


 
int main() {
	return 0;
}