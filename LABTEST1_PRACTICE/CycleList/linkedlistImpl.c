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
	head->count = 0;	
}


void make_loop(struct linkedlist* head){
	int index;
	scanf("%d",&index);
	
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

void hasCycle(struct linkedlist* head){
	
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
	
	if(flag==1){
		printf("1\n");
	}
	else
		printf("0\n");
}

void traverseGeneric(struct linkedlist* head){
	struct node *ptr = head->first;	
	int count = head->count;
	while(count>0){        
		printf("%d\t",ptr->element);
		ptr = ptr->next;
		count--;
	}
	printf("-2\n");
}

void destroyGeneric(struct linkedlist* head){
	if(head->first==NULL){
		printf("-3\n");
		return;
	}
	int count = head->count;
	struct node *temp = head->first;
	struct node *pretemp = head->first;
	while(count>0){
		pretemp = temp;
		if(count!=1)
			temp = temp->next;
		free(pretemp);
		count--;
	}	
	head->first = NULL;
	printf("-2\n");
	head->count = 0;
	
}


