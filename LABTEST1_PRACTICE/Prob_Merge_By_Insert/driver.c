#include<stdio.h>
#include<stdlib.h>
#include"mergeSort.h"

int main(){
	FILE* f = stdin;
	int n;
	fscanf(f,"%d",&n);
	int arr[n];
	
	int i;
	for(i=0;i<n;i++){
		fscanf(f,"%d",&arr[i]);
	}
	
	mergeSort(arr,0,n-1);
	
	for(i=0;i<n;i++)
		printf("%d\n",arr[i]);
	
}

