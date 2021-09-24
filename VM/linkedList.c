#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *next;
} node;

void insert(node **head, int val) {
	node *current=NULL, *new;
	if(*head==NULL) {
		new=malloc(sizeof(node));
		new->val=val;
		new->next=NULL;
		*head=new;
	} else {
		current=*head;
		while(current->next!=NULL) {
			current=current->next;
		}
		new=malloc(sizeof(node));
		current->next=new;
		new->next=NULL;
		new->val=val;
	}
}

void dump(node *head) {
	while(head!=NULL) {
		printf("%d\n", head->val);
		head=head->next;
	}
}

void destroy(node *head) {
	node *current;
	while(head!=NULL) {
		current=head;
		head=head->next;
		free(current);
	}
}

int main(void) {
	node *head=NULL;
	insert(&head, 10);
	insert(&head, 5);
	insert(&head, 60);
	insert(&head, 40);
	dump(head);
	destroy(head);
	return 0;
}
