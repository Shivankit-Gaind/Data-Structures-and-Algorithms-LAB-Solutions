#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void merge_sort(int* a,int low,int high);
void sorted_merge(int* a, int low, int high, int* x,int m, int j, int* y, int n, int k);


int main(){
	int n;
	scanf("%d",&n);
	int a[n];
	int i;
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);	
	merge_sort(a,0,n-1);
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}
}

//merge-sort with a recursive merge operation

void merge_sort(int* a,int low,int high){
	if(low<high){
		int mid = (high+low)/2;
		merge_sort(a,low,mid);
		merge_sort(a,mid+1,high);
		int i;
		int z=0;
		int x[mid-low+1];
		int y[high-mid];
		for(i=low;i<=mid;i++){
			x[z++] = a[i];
		}
		z=0;
		for(i = mid+1;i<=high;i++){
			y[z++] = a[i];
		}
		sorted_merge(a,low,high,x,mid-low+1,0,y,high-mid,0);
	}
}

void sorted_merge(int* a, int low, int high, int* x,int m ,int j, int* y,int n, int k){
	if(low>high)
		return;
		
	if(j<m && k<n){
		if(x[j]<=y[k]){
			a[low] = x[j];
			sorted_merge(a,low+1,high,x,m,j+1,y,n,k);
		}
		else{
			a[low] = y[k];
			sorted_merge(a,low+1,high,x,m,j,y,n,k+1);
		}
	}
	else if(j<m){
		a[low] = x[j];
		sorted_merge(a,low+1,high,x,m,j+1,y,n,k);
	}
	else{
		a[low] = y[k];
		sorted_merge(a,low+1,high,x,m,j,y,n,k+1);
	}
}
