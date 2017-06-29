#include "linkedlist.h"

void push(struct linkedlist* head, int ele){
	insertFirst(head,ele);
}
int pop(struct linkedlist* head){
	struct node* temp = deleteFirst(head);
	if(temp==NULL){
		return -9999;
	}
	return temp->element;
}
