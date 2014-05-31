#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;


struct node {
	int data;
	struct node *next;
};

struct DLL {
    int data;
    struct DLL *next;
    struct DLL *prev;
};

struct list {
    int data;
    struct list *next;
    struct list *child;
};

struct NNode {
    int data;
    struct NNode *right;
    struct NNode *down;
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
	struct node *bCurr = *b;
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
struct node *partition(struct node *head, struct node *end,
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
void skipMdeleteN(struct node  *head, int M, int N) {
	if (head == NULL) return;
	struct node *current = head, *next;
	while (current) {
		for (int i = 1; i < M && current != NULL; i++) {
			current = current->next;
		}
		if (current == NULL) return;
		next = current->next;

		for (int i = 1; i < N && next != NULL; i++) {
			struct node *temp = next;
			next = next->next;
			free(temp);
		}

		current->next = next;
		current = next;
	}
}

// How to implement a stack which will support following operations in O(1) time complexity?
// 1) push() which adds an element to the top of stack.
// 2) pop() which removes an element from top of stack.
// 3) findMiddle() which will return middle element of the stack.
// 4) deleteMiddle() which will delete the middle element.
// Push and pop are standard stack operations.

// The important question is, whether to use a linked list or array for implementation of stack?

// Please note that, we need to find and delete middle element. 
// Deleting an element from middle is not O(1) for array. 
// Also, we may need to move the middle pointer up when we push an element 
// and move down when we pop(). 
// In singly linked list, moving middle pointer in both directions is not possible.

// The idea is to use Doubly Linked List (DLL). 
// We can delete middle element in O(1) time by maintaining mid pointer. 
// We can move mid pointer in both directions using previous and next pointers.

// TODO

// Swap Kth node from beginning with Kth node from end in a Linked List
// Given a singly linked list, swap kth node from beginning with kth node from end. 
// Swapping of data is not allowed, only pointers should be changed. 
// This requirement may be logical in many situations where the linked list data part is huge 
// (For example student details line Name, RollNo, Address, ..etc). 
// The pointers are always fixed (4 bytes for most of the compilers).

int countNodes(struct node *head) {
	int count = 0;
	while (head != NULL) {
		head = head->next;
		count++;
	}
	return count;
}
void swap(struct node **headRef, int k) {
	int n = countNodes(*headRef);

	if (n < k) return;

	// if x (kth node from start) and y (kth node from end)
	// are same
	if (2*k - 1 == n) return;

	node *x = *headRef;
	node *x_prev = NULL;

	for (int i = 1; i < k; i++) {
		x_prev = x;
		x = x->next;
	}

	node *y = *headRef;
	node *y_prev = NULL;

	for (int i = 1; i < n - k + 1; i++) {
		y_prev = y;
		y = y->next;
	}

	// If x_prev exists then new next of it 
	// will be y. Consider the case when y->next
	// is x, in this case, x_prev and y are same
	// So it creates a self loop
	// This self loop will be broken 
	// when we change y->next
	if (x_prev) {
		x_prev->next = y;
	}
	if (y_prev) {
		y_prev->next = x;
	}

	node *temp = x->next;
	x->next = y->next;
	y->next = temp;

	if (k == 1) {
		*headRef = y;
	}
	if (k == n) {
		*headRef = x;
	}
} 

// QuickSort on Doubly Linked List
struct DLL *lastNode(DLL *root) {
    while (root && root->next)
        root = root->next;
    return root;
}

void swap(int* a, int* b) { 
	int t = *a;      
	*a = *b;       
	*b = t;   
}

DLL *partition(DLL *start, DLL *end) {
	int pivot = end->data;
	DLL *i = start->prev;

	for (DLL *j = start; j != end; j = j->next) {
		if (j->data <= pivot) {
			i = (i == NULL) ? start : i->next;
			swap(&(i->data), &(j->data));
		}
	}
	i = (i == NULL) ? start : i->next;
	swap(&(i->data), &(end->data));
	return i;
}

void _quickSort(DLL *start, DLL *end) {
	if (end != NULL && start != end  
		&& start != end->next) {
		struct DLL *p = partition(start, end);
	_quickSort(start, p->prev);
	_quickSort(p->next, end);
	}
}

void quickSort(DLL *head) {
	_quickSort(head, lastNode(head));
}


// Flatten a multilevel linked list
// Given a linked list where in addition to the next pointer, 
// each node has a child pointer, which may or may not point to a separate list. 
// These child lists may have one or more children of their own, and so on, to produce a multilevel data structure, 
// as shown in below figure.You are given the head of the first level of the list. 
// Flatten the list so that all the nodes appear in a single-level linked list. 
// You need to flatten the list in way that all nodes at first level should come first, then nodes of second level, and so on.

// Each node is a C struct with the following definition.

// struct list
// {
//     int data;
//     struct list *next;
//     struct list *child;
// };

void flattenList(struct list *head) {
	if (head == NULL) return;

	struct list *temp,*tail = head;

	while (tail->next != NULL) {
		tail = tail->next;
	}

	struct list *current = head;

	while (current != tail) {
		if (current->child != NULL) {
			tail->next = current->child;
			temp = current->child;

			while (temp->next) {
				temp = temp->next;
			}
			tail = temp;
		}
		current = current->next;
	}
}

// Add two numbers represented by linked lists 

void push(struct node **result, int data) {
	struct node *newNode = (node*) malloc(sizeof(node));
	newNode->data = data;
	newNode->next = *result;
	*result = newNode;
}
struct node *addSameSizeLists(struct node *head1, struct node* head2, int *carry) {
	if (head1 == NULL) return NULL;
	struct node *result = (node*) malloc(sizeof(node));
	result->next = addSameSizeLists(head1->next, head2->next, carry);
	int sum = head1->data + head2->data + *carry;
	*carry = sum / 10;
	sum = sum % 10;
	result->data = sum;
	return result;
}

void addCarryToRemaining(struct node *head1, struct node *current, 
						 int *carry, struct node **result) {
	int sum = 0;
	while (head1 != current) {
		addCarryToRemaining(head1->next, current, carry, result);
		sum = head1->data + *carry;
		*carry = sum / 10;
		sum = sum % 10;
		push(result, sum);
	}
}

void swapPointers(struct node **head1, struct node **head2) {
	struct node *temp = *head1;
	*head1 = *head2;
	*head2 = temp;
}
void addList(struct node *head1, struct node *head2, struct node **result) {
	if (head1 == NULL || head2 == NULL) {
		*result = (head1 == NULL) ? head2 : head1;
	} else {
		int size1 = countNodes(head1);
		int size2 = countNodes(head2);
		int carry = 0;
		if (size1 == size2) {
			*result = addSameSizeLists(head1, head2, &carry);
		} else {
			if (size2 > size1) {
				swapPointers(&head1, &head2);
			}
			int diff = (int) abs(size1 - size2);
			struct node* current;
			for (current  = head1; diff--; current = current->next);
			*result = addSameSizeLists(current, head2, &carry);
			addCarryToRemaining(head1, current, &carry, result);
		}
		if (carry) {
			push(result, carry);
		}
	}
}

// Flattening a Linked List
// Given a linked list where every node represents a linked list and contains two pointers of its type:
// (i) Pointer to next node in the main list (we call it ‘right’ pointer in below code)
// (ii) Pointer to a linked list where this node is head (we call it ‘down’ pointer in below code).
// All linked lists are sorted. See the following example

//        5 -> 10 -> 19 -> 28
//        |    |     |     |
//        V    V     V     V
//        7    20    22    35
//        |          |     |
//        V          V     V
//        8          50    40
//        |                |
//        V                V
//        30               45
// Write a function flatten() to flatten the lists into a single linked list. 
// The flattened linked list should also be sorted. 
// For example, for the above input list, 
// output list should be 5->7->8->10->19->20->22->28->30->35->40->45->50.

NNode *merge(NNode *a, NNode *b) {
	if (a == NULL || b == NULL) {
		return (a == NULL) ? b : a;
	}

	NNode *result;
	if (a->data < b->data) {
		result = a;
		result->down = merge(a->down, b);
	} else {
		result = b;
		result->down = merge(a, b->down);
	}
	return result;
}

NNode *flatten(NNode *root) {
	if (root == NULL || root->right == NULL) return root;
	return merge(root, flatten(root->right));
}

// Implement LRU Cache
// How to implement LRU caching scheme? What data structures should be used?

// We are given total possible page numbers that can be referred. 
// We are also given cache size (Number of page frames that cache can hold at a time). 
// The LRU caching scheme is to remove the least recently used frame when the cache is full 
// and a new page is referenced which is not there in cache. 
// Please see the Galvin book for more details (see the LRU page replacement slide here).

// We use two data structures to implement an LRU Cache.

// 1. A Queue which is implemented using a doubly linked list. The maximum size of the queue will be equal to the total number of frames available (cache size).
// The most recently used pages will be near front end and least recently pages will be near rear end.

// 2. A Hash with page number as key and address of the corresponding queue node as value.

// TODO

// Given a singly linked list, 
// rotate the linked list counter-clockwise by k nodes. 
// Where k is a given positive integer. 
// For example, if the given linked list is 10->20->30->40->50->60 
// and k is 4, the list should be modified to 50->60->10->20->30->40. 
// Assume that k is smaller than the count of nodes in linked list.
void rotateByK(struct node **headRef, int k) {
	if (*headRef == NULL || (*headRef)->next == NULL) return;
	int n = countNodes(*headRef);
	if (k > n) return;
	struct node *current = *headRef;

	for (int i = 0; i < k - 1; i++) {
		current = current->next;
	}

	struct node *newHead = current->next;
	current->next = NULL;
	struct node *end = current;

	while (end->next != NULL) {
		end = end->next;
	}
	end->next = *headRef;
	*headRef = newHead;
}
// Given three linked lists, say a, b and c, 
// find one node from each list such that the sum of the values of the nodes is equal 
// to a given number. 
// For example, if the three linked lists are 12->6->29, 23->5->8 and 90->20->59, 
// and the given number is 101, the output should be tripel “6 5 90″.

// In the following solutions, size of all three linked lists is assumed same 
// for simplicity of analysis. 
// The following solutions work for linked lists of different sizes also.

// A simple method to solve this problem is to run three nested loops. 
// The outermost loop picks an element from list a, 
// the middle loop picks an element from b and the innermost loop picks from c. 
// The innermost loop also checks whether the sum of values of current nodes of a, b and c 
// is equal to given number. The time complexity of this method will be O(n^3).

// Sorting can be used to reduce the time complexity to O(n*n). 
// Following are the detailed steps.
// 1) Sort list b in ascending order, and list c in descending order.
// 2) After the b and c are sorted, one by one pick an element from list a 
// and find the pair by traversing both b and c. 
// See isSumSorted() in the following code. 
// The idea is similar to Quadratic algorithm of 3 sum problem.
bool isSumSorted(struct node *headA, struct node *headB, 
                 struct node *headC, int givenNumber) {
	struct node *a = headA;
	while (a != NULL) {
		struct node *b = headB;
		struct node *c = headC;

		while (b != NULL && c != NULL) {
			int sum = a->data + b->data + c->data;
			if (sum == givenNumber) {
				printf("Triplet found %d %d %d\n", a->data, b->data, c->data);
				return true;
			} else if (sum < givenNumber) {
				b = b->next;
			} else {
				c = c->next;
			}
		}
		a = a->next;
	}
	printf("No Such triplet\n");
	return false;
}

// XOR Linked List – A Memory Efficient Doubly Linked List
struct XORnode {
    int data;
    struct XORnode *npx;  /* XOR of next and previous node */
};

struct XORnode *XOR(struct XORnode *a, struct XORnode *b) {
	return (struct XORnode*) ((unsigned int) (a) ^ (unsigned int) (b));
}

void insert(struct XORnode **headRef, int data) {
	struct XORnode *newNode = (struct XORnode*) malloc(sizeof(XORnode));
	newNode->data = data;
	newNode->npx = XOR(*headRef, NULL);

	if (*headRef != NULL) {
		struct XORnode *next = XOR((*headRef)->npx, NULL);
		(*headRef)->npx = XOR(newNode, next);
	}
	*headRef = newNode;
}

void printXORList(struct XORnode *head) {
	struct XORnode *current = head, *prev = NULL, *next;
	while (current != NULL) {
		cout << current->data << " ";
		next = XOR(prev, current->npx);
		prev = current;
		current = next;
	}
}

int main() {
	return 0;
}