#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main(int argc, char *argv[]){
	struct linkedlist * head = (struct linkedlist *) malloc (sizeof(struct linkedlist));
	head->count = 0;
	head->first = NULL;
	int x;	
	scanf("%d",&x);
	while(1){
		if(x==-1)
			break;
		else if(x==0){
			insertInFront(head);
		}
		else if(x==1){
			insertAtEnd(head);
		}
		else if(x==2){
			deleteFromFront(head);
		}
		else if(x==3){
			deleteAtEnd(head);
		}
		else{
			traverse(head);	
		}
		scanf("%d",&x);
	}
	return 0;
}


