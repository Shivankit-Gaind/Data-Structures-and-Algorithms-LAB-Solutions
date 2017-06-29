#include <stdio.h>
int main(int argc, char* argv[])
{
	FILE *fptr = fopen(argv[1],"r");
	FILE *fptr2 = fopen(argv[2],"w");
	
	if(!fptr){
		printf("File: %s doesn't exist",argv[1]);
		return 0;
	}
	
	
	
}
