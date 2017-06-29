#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int binary_search(int *a, int low, int high,int key);

int main(){
	int n;
	scanf("%d",&n);
	int a[n];
	int i;
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	int key = 9;
	printf("%d",binary_search(a,0,n-1,key));
}

int binary_search(int *a, int low, int high,int key){
	if(low<high){
		int mid = (high+low)/2;
		if(a[mid]==key)
			return mid;
		else if(a[mid]>key){
			int index = binary_search(a,low,mid-1,key);
			if(index!=-1)
				return index;
		}			
		else{
			int index = binary_search(a,mid+1,high,key);
			if(index!=-1)
				return index;
		}			
	}
		return -1;		
}
