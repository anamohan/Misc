// Given a linked list, find out if the list is circular, also find the point from where the cycle start.

#include <iostream>
#include <cstdio>

using namespace std;




struct node {
    int data;
    node* next;
};

void add_node_to_head(struct node ** head, int data) {
    struct node *new_node = (struct node*) malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

void remove_loop(struct node *loop_node, struct node *head) {
    struct node *ptr1 = loop_node;
    struct node *ptr2 = loop_node;

    unsigned int k = 1;
    while (ptr1->next != ptr2) {
        ptr1 = ptr1->next;
        k++;
    }

    ptr1 = head;
    ptr2 = head;
    for (int i = 0; i < k; i++) {
        ptr2 = ptr2->next;
    }

    while (ptr2 != ptr1) {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    ptr2 = ptr2->next;
    while (ptr2->next != ptr1) {
        ptr2 = ptr2->next;
    }
    ptr2->next = NULL;
}

int detect_and_remove_loop(struct node *list) {
    struct node* slow = list;
    struct node* fast = list;

    while (slow && fast && fast->next) {
        if (slow == fast) {
            remove_loop(slow, list);
            return 1;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return 0;
}



void print_list(struct node *head) {
    while (!head) {
        printf("%d ", head->data);
        head = head->next;
    }
}

int main() {
    return 0;
}