#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"



int main(int argc, char *argv[]){

	// Create a file pointer and open the file read as command line argument.
	FILE *fileptr = fopen(argv[1], "r");

	// Declare a pointer to a linked list (head) and allocate memory to it.
	struct linkedlist * stack = (struct linkedlist *) malloc (sizeof(struct linkedlist));

	
	
	// In a loop read the file and insert elements into the linkedList.
	int x;
	while (fscanf(fileptr, "%d", &x)==1){
		// read the next element and store into the temp variable.
		// insert temp into the linked list.
		push(stack,x);
	}


	// close the file pointer
	fclose(fileptr);
	int temp;
	temp = pop(stack);
	while(temp!=-9999){
		printf("%d, ",temp);
		temp = pop(stack);
	}	

}
