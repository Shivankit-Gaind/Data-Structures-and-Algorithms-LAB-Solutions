#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void counting_sort(int* arr, int n, int range_max);

int main(){
	int n;
	scanf("%d",&n);
	int a[n];
	int i;
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);	
	counting_sort(a,n,100);
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}
}

void counting_sort(int* arr, int n, int range_max){
	int count[range_max+1];
	int i;
	int output[n];
	for(i=0;i<=range_max;i++){
		count[i]=0;
	}
	for(i=0;i<n;i++){
		count[arr[i]]++;
	}	
	for(i=1;i<=range_max;i++){
		count[i] += count[i-1];
	}	
	for(i=0;i<n;i++){
		output[count[arr[i]]-1] = arr[i];
		count[arr[i]]--;
	}		
	for(i=0;i<n;i++){
		arr[i] = output[i];
	}
}
