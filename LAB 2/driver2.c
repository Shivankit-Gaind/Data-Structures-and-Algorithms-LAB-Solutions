#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main(int argc, char *argv[]){
	struct linkedlist * head = (struct linkedlist *) malloc (sizeof(struct linkedlist));
	head->count = 0;
	head->first = NULL;
	int x,y,z;
		
	scanf("%d",&x);
	while(1){
		if(x==-1)
			break;
		else {
			insertAtEnd(head);
		}	
		z=x;	
		scanf("%d",&x);
		if(x<=z && x!=-1){
			scanf("%d",&y);
			make_loop_(head,x,y);
			scanf("%d",&x); // for next element
		}
	}
	detect_Cycle(head);
	return 0;	
}

