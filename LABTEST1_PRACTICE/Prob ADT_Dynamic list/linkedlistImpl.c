#include "linkedlist.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


void create(struct linkedlist* head,int ele){

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
	printf("-2\n");
}

void delete(struct linkedlist* head){
	if(head->first==NULL){
		printf("-3\n");
		return;
	}
	struct node *temp = head->first;
	struct node *pretemp = head->first;
	while(temp!=NULL){
		pretemp = temp;
		temp = temp->next;
		free(pretemp);
	}
	head->first = NULL;
	printf("-2\n");	
}


