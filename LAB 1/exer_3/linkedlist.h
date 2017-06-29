#include<stdio.h>

struct node{
	int element;
	struct node* next;
};

struct linkedlist{
	struct node* first;
	int count;
};

void insertFirst(struct linkedlist * head,int ele);
struct node* deleteFirst(struct linkedlist * head);
void printList (struct linkedlist * head); 
int search (struct linkedlist * head, int ele); 
struct node * delete (struct linkedlist * head, int ele);

