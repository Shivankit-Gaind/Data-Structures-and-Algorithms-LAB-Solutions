#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main(int argc, char *argv[]){

	// Create a file pointer and open the file read as command line argument.
	FILE *fileptr = fopen(argv[1], "r");

	// Declare a pointer to a linked list (head) and allocate memory to it.
	struct linkedlist * head = (struct linkedlist *) malloc (sizeof(struct linkedlist));

	
	
	// In a loop read the file and insert elements into the linkedList.
	int x;
	while (fscanf(fileptr, "%d", &x)==1){
		// read the next element and store into the temp variable.
		// insert temp into the linked list.
		insertFirst(head,x);
	}


	// close the file pointer
	fclose(fileptr);

	// print the linked list.
	printList (head); 
	
	// delete the first element of the linked list.
	deleteFirst (head); 

	// print the linked list again to check if delete was successful.
	printList (head);

	// print the linked list to a new file.
	FILE *fileptr2 = fopen("newLinkedList.txt", "w");
	if(fileptr2==NULL){
		printf("Error!\n");
		exit(1);
	}
	
	struct node* temp = head->first;
	while(temp != NULL){        
		fprintf(fileptr2,"%d --> ",temp->element);
		temp = temp->next;
	}
	fprintf(fileptr,"end\n");
	
	
	// testing the delete function
	delete(head,56);
	temp = head->first;
	while(temp != NULL){        
		fprintf(fileptr2,"%d --> ",temp->element);
		temp = temp->next;
	}
	fprintf(fileptr,"end\n");	
}
