#include<stdio.h>
#include<stdlib.h>

void radix_sort(int* arr, int n);
void counting_sort(int* arr, int n, int m);
int max_digit_size(int *arr, int n);

int main(){
	int n,i;
	scanf("%d",&n);
	int a[n];
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);	
	radix_sort(a,n);
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}
}

//RADIX SORT
void radix_sort(int* arr, int n){
	int i;
	int m = max_digit_size(arr,n);
	int z =1;	
	for(i=0;i<m;i++){
		counting_sort(arr,n,z);
		z*=10;
	}
}

//Sorting digit by digit m indicates the place(one's, tenth, hundredth etc)
void counting_sort(int* arr, int n, int m){
	int count[10];
	int i;
	int output[n];
	for(i=0;i<=9;i++){
		count[i]=0;
	}
	for(i=0;i<n;i++){
		count[(arr[i]/m)%10]++; //extracting digit at one's place
	}	
	for(i=1;i<=9;i++){
		count[i] += count[i-1];
	}	
	//IMPORTANT: LOOP IS MADE TO RUN IN OPPOSITE DIRECTION FOR THE STABILITY OF THE ALGORITHM -- STABLE COUNTING SORT
	for(i=n-1;i>=0;i--){
		output[count[(arr[i]/m)%10]-1] = arr[i];
		count[(arr[i]/m)%10]--;
	}		
	for(i=0;i<n;i++){
		arr[i] = output[i];
	}
}

//FUNCTION TO RETURN THE NUMBER WITH MAXIMUM DIGITS
int max_digit_size(int *arr, int n){
	int i;
	int max = arr[0];
	for(i=1;i<n;i++){
		if(arr[i]>max)
			max = arr[i];
	}
		
	int digits = 0;
	for(i=max;i>0;i/=10)
		digits++;
	return digits;
}


