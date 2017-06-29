#include<stdio.h>

struct node{
	int element;
	struct node* next;
};

struct linkedlist{
	struct node* first;
	int count;
};

void create(struct linkedlist * head,int ele);
void delete(struct linkedlist * head);
void traverse (struct linkedlist * head);
void hasCycle(struct linkedlist* head);
void traverseGeneric(struct linkedlist* head);
void destroyGeneric(struct linkedlist* head); 



