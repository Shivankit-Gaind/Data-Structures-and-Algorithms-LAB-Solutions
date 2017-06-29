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
			int y;
			scanf("%d",&y);
			while(y!=-1){
				create(head,y);
				scanf("%d",&y);
			}
			traverse(head);
		}
		else if(x==1){
			traverse(head);
		}
		else if(x==2){
			delete(head);
		}	
		else if(x==3){
			make_loop(head);
		}
		else if(x==4)
			hasCycle(head);
		else if(x==5)
			traverseGeneric(head);
		else if(x==6)
			destroyGeneric(head);
		
		scanf("%d",&x);
	}
}


