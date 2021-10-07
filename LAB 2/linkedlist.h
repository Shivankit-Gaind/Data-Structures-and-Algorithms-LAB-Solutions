#include<stdlib.h>
#include<stdio.h>

struct node{
	int element;
	struct node* next;
};

struct linkedlist{
	struct node* first;
	int count;
};

void insertInFront(struct linkedlist * head);
void insertAtEnd(struct linkedlist * head);
void deleteFromFront(struct linkedlist * head);
void deleteAtEnd (struct linkedlist * head);
void traverse (struct linkedlist * head); 
void insertIndex(struct linkedlist* head, int index,int ele);
void detect_Cycle(struct linkedlist* head);
void make_loop(struct linkedlist* head,int index,int element);



