#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void insertion_sort(int* arr,int end);
void insert_in_sorted_order(int* a, int element,int length);
void insertion_sort_2(int *a,int n);

int main(){
	int n;
	scanf("%d",&n);
	int a[n];
	int i;
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);	
	insertion_sort_2(a,n);
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}
}
void insertion_sort(int* arr,int end){
	if(end==0){
		return;
	}
	int temp = arr[end];
	insertion_sort(arr,end-1);
	insert_in_sorted_order(arr,arr[end],end-1);
}

void insert_in_sorted_order(int* a, int element,int length){
	int i = length;
	for(;i>=0;i--){
		if(element>a[i])
			break;
		a[i+1] = a[i];
	}
	a[i+1] = element;
}

void insertion_sort_2(int *a,int n){
	int i,j;
	for(i=0;i<n;i++){
		int element = a[i];
		j = i-1;
		while(j>=0 && a[j]>element){
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = element;
	}
}
