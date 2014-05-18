// QuickSort on Singly Linked List
#include <iostream>
#include <cstdio>

using namespace std;

struct node {
	int data;
	struct node *next;
};

void push(struct node **head_ref, int data) {
	struct node *new_node = new node;
	new_node->data = data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

void print_list(struct node *node) {
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
}

struct node *get_tail(struct node *cur) {
	while (cur != NULL && cur->next != NULL) {
		cur = cur->next;
	}
	return cur;
}

struct node *partition(struct node *head, 
	struct node *end, struct node **new_head, 
	struct node **new_end) {
	struct node *pivot = end;
	struct node *prev = NULL, *cur = head, 
	*tail = pivot;

	while (cur != pivot) {
		if (cur->data < pivot->data) {
			if ((*new_head) == NULL) {
				(*new_head) = cur;
			}
			prev = cur;
			cur = cur->next;
		} else {
			if (prev != NULL) {
				prev->next = cur->next;
			}
			struct node *temp = cur->next;
			cur->next = NULL;
			tail->next = cur;
			tail = cur;
			cur = temp;
		}
	}
	if ((*new_head) == NULL) {
		(*new_head) = pivot;
	}
	(*new_end) = tail;
	return pivot;
}

struct node *quicksort_recur(struct node *head, 
	struct node *end) {
	if (head == NULL || head == end) {
		return head;
	}
	struct node *new_head = NULL, *new_end = NULL;
	struct node *pivot = partition(head, end, &new_head, &new_end);

	if (new_head != pivot) {
		struct node *temp = new_head;
		while (temp->next != pivot) {
			temp = temp->next;
		}
		temp->next = NULL;
		new_head = quicksort_recur(new_head, temp);
		temp = get_tail(new_head);
		temp->next = pivot;
	}
	pivot->next = quicksort_recur(pivot->next, new_end);
    return new_head;
}

void QuickSort(struct node **head_ref) {
	(*head_ref) = quicksort_recur(*head_ref, 
		get_tail(*head_ref));
	return;
}
int main() {

	struct node *a = NULL;
    push(&a, 5);
    push(&a, 20);
    push(&a, 4);
    push(&a, 3);
    push(&a, 30);
 
    cout << "Linked List before sorting \n";
    print_list(a);
 
    QuickSort(&a);
 
    cout << "Linked List after sorting \n";
    print_list(a);
	return 0;
}