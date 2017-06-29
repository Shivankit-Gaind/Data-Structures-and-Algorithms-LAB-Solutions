#include "linkedlist.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


void insertInFront(struct linkedlist* head){
	int ele;
	scanf("%d",&ele);
	
	struct node *link = (struct node*) malloc(sizeof(struct node));	
	link->element = ele;
	link -> next = head ->first;
	
	head -> first = link;
	head -> count++;
	
	traverse(head);
}

void insertAtEnd(struct linkedlist* head){

	int ele;
	scanf("%d",&ele);	
	struct node *link = (struct node*) malloc(sizeof(struct node));
	link->element = ele;	
	link -> next = NULL;
	struct node *ptr = head->first;
	if(ptr==NULL){
		head->first = link;
	}
	else{		
		while(ptr->next != NULL){ 
			ptr = ptr->next;
		}
	ptr->next = link;
	}	
	head -> count++;
}

void traverse(struct linkedlist * head){
	struct node *ptr = head->first;	
	
	while(ptr != NULL){        
		printf("%d\t",ptr->element);
		ptr = ptr->next;
	}
	printf("\n");
}

void deleteFromFront(struct linkedlist* head){
	int ele;
	if(head->first==NULL){
		ele = -2;
		printf("%d\n",ele);
		return;
	}
	ele = head->first->element;
	head -> first = head->first->next;
	head->count--;
	
	printf("%d\n",ele);
}

void deleteAtEnd(struct linkedlist* head){
	int ele;
	if(head->first==NULL){
		ele = -2;
		printf("%d\n",ele);
		return;
	}
	
	struct node *temp = head->first;
	struct node *pretemp = head->first;			
	while(temp->next!= NULL){        
		pretemp = temp;
		temp = temp->next;
	}
	if(pretemp==temp){
		ele = head->first->element;
		head->first = NULL;
	}
	else{
		ele = temp->element;
		pretemp -> next = NULL;
	}
	printf("%d\n",ele);
	head->count--;
}

void insertIndex(struct linkedlist* head, int index,int ele){
	struct node *link = (struct node*) malloc(sizeof(struct node));
	link->element = ele;	
	link -> next = NULL;

	if(index==1){
		link -> next = head ->first;	
		head -> first = link;
		head -> count++;
		return;	
	}

	else{
		int count = 1;
		struct node *ptr = head->first;	
		struct node *pretemp = head->first;	
		while(ptr != NULL && count!=index){  
			pretemp = ptr;      
			ptr = ptr->next;
			count++;
		}
		
		link->next = pretemp->next;
		pretemp->next = link;
		head->count++;
		return;	
	}
}

void make_loop(struct linkedlist* head,int index,int element){
	
	if(head->first==NULL){
		return;
	}
	
	struct node *temp = head->first;
	struct node *pretemp = head->first;
	struct node *ptr;
	int count = 1;
	while(temp!=NULL){
		if(count==index){
			ptr = temp;
		}
		pretemp = temp;
		temp = temp->next;
		count++;	
	}	
	pretemp->next = ptr;
}



//Hare and Tortoise algorithm for detecting a cycle in a linked list

void detect_Cycle(struct linkedlist* head){	
	struct node *temp1 = head->first;
	struct node *temp2 = head->first;	
	int flag = 0;
	while(temp1!=NULL && temp2!=NULL && temp2->next!=NULL){
		temp1 = temp1->next;
		temp2 = temp2->next->next;
		if(temp1==temp2){
			flag=1;
			break;
		}
	}
	int count = 0;
	if(flag==1){
		struct node *ptr = temp1->next;
		count++;	
		while(ptr!=temp1){
			ptr = ptr->next;
			count++;
		}	
	}	
	printf("%d\n",count);
}


