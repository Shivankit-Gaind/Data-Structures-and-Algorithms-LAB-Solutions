#include "linkedlist.h"
#include<stdio.h>
#include<stdlib.h>

void insertFirst(struct linkedlist* head, int ele){
	//create a node
	struct node *link = (struct node*) malloc(sizeof(struct node));
	
	/* by this you are creating a node whose address is being stored in the link pointer.*/
	
	link->element = ele;
	//point it to old first node
	link -> next = head ->first;
	//point first to new first node
	
	head -> first = link;
	head -> count++;
}


struct node* deleteFirst(struct linkedlist* head){
	if(head->first==NULL){
		return NULL;
	}
	
	struct node* temp = head->first;
	head -> first = head->first->next;
	head->count--;
	return temp;
}


void printList(struct linkedlist * head){
	struct node *ptr = head->first;
	printf("\n[ ");
	
	//start from the beginning
	
	while(ptr != NULL){        
		printf("%d ",ptr->element);
		ptr = ptr->next;
	}
	printf(" ]");
}

int search (struct linkedlist * head, int ele){
	struct node *ptr = head->first;
	
	// assume index of the first element is 1
	int index=1;
	
	while(ptr != NULL){        
		if(ptr->element==ele){
			return index;
		}
		index++;
		ptr = ptr->next;
	}
	return -1;	
} 
struct node * delete (struct linkedlist * head, int ele){
	struct node *temp = head->first;
	struct node *pretemp = head->first;
	
	while(temp!=NULL && temp->element!=ele){
		pretemp = temp;
		temp = temp->next;
	}
	
	//ITEM NOT FOUND
	if(temp==NULL)
		return NULL;
	
	// for deleting the first element
	if(pretemp==temp){
		head->first = head->first->next;
		return temp; //or pretremp
	}	
	
	// for deleting element at any other position
	pretemp->next = temp->next;
	return temp;
}





