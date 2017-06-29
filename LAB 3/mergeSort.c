#include"mergeSort.h"

void mergeSort(int *a, int low , int high){
	if(low<high){
		int mid = (low+high)/2;
		mergeSort(a,low,mid);
		mergeSort(a,mid+1,high);
		mergebyInsert(a,low,mid,high);
	}
}

void merge(int *a,int low,int mid, int high){
	int b[mid-low+1];
	int c[high-mid];
	int i;
	int j=0;
	int z=low;	
	for(i=low;i<=mid;i++){
		b[j++] = a[i];
	}
	j=0;
	for(i=mid+1;i<=high;i++){
		c[j++] = a[i];
	}
	j=0; i=0;
	while(i<mid-low+1 && j<high-mid){
		
		//Merging
		if(b[i]<=c[j]){
			a[z++] = b[i++];
		}
		else
			a[z++] = c[j++];		
	}	
	
		//Extra elements left	
		while(i<mid-low+1)
			a[z++] = b[i++];
			
		while(j<high-mid)
			a[z++] = c[j++];
}

void mergebyInsert(int *a,int low,int mid,int high){
	
	int i;
	//no extra space used
	for(i=low;i<=mid;i++){
		int j=mid+1;
		while(a[j]<=a[low] && j<=high){
			j++;
		}
		int temp = a[low];
		int x;
		for(x=low;x<j-1;x++){
			a[x] = a[x+1];			
		}
		a[x] =temp;		
	}
}
