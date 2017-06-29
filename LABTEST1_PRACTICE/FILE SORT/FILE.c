#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


void merge(FILE* f1, FILE* f2,int index);
void insertion_sort(int* arr,int end);
void insert_in_sorted_order(int* a, int element,int length);

void merge_sort(int* a,int low,int high);
void sorted_merge(int* a, int low, int high, int* x,int m, int j, int* y, int n, int k);



int main(){
	
	//Making an input file
	FILE* start = fopen("input.txt","w");
	int size = pow(2,18);
	
	//printing the size of input file
	printf("%d\n",size);
	
	
	int i,z,element;
	for(i=0;i<size;i++){
		fprintf(start, "%d\n", rand());
	}	
	fclose(start);
	
	
	//opening the file for reading
	FILE *f = fopen("input.txt","r");
	
	int j = 1;
	int flag = 0;
		
	while(1){
		
		// allocating an array for sorting pow(2,14) elements		
		int x = pow(2,14);
		int* a = (int*)malloc(x*sizeof(int));		
		
		
		//loading elements into the array from the input file
		for(i=0;i<x;i++){
			if(fscanf(f,"%d",&element)==1){
				a[i] = element;
			}
			else{
				flag = 1; // denoting that the file is finished
				break;
			}
		}		
		if(i==0)
			break;
									
		//sorting the elements in the array
		insertion_sort(a,i-1);
		
		//opening a file for next pow(2,16) elements		
		char file[15];
		sprintf(file,"File%d.txt",j++);	
		FILE* temp = fopen(file,"w");
		
		
		for(z=0;z<i;z++){
			fprintf(temp,"%d\n",a[z]);
		}
		
		//closing the file and freeing the array
		fclose(temp);
		free(a);
		
		if(flag==1)
			break;
	}
	
	//closing the input file after reading	
	fclose(f);
	
	int no_of_files = j-1;
	
	//The files have been created till here
	
	//#####################################################################################################################################
	
	int y = no_of_files+1;
	int x=1;
	while(1){
		if(y-x==1){
			break;
		}
		char file[15];
		sprintf(file,"File%d.txt",x++);
		FILE* f1 = fopen(file,"r");
		
		sprintf(file,"File%d.txt",x++);
		FILE* f2 = fopen(file,"r");
		
		merge(f1,f2,y++);
		
									
	}
	
	//merge operation completed
	
	//#####################################################################################################################################
	
	int last_file = y-1;
	char file[15];	
	sprintf(file,"File%d.txt",last_file);
	FILE* final = fopen(file,"r");
	
	
	//####################################################################################################################################@
	
	//counting the number of elements in the last file and matching it with the size
		
	int count = 0;
	while(fscanf(final,"%d",&element)==1){
		count++;
	}
	printf("%d",count);
	
	fclose(final);
		
}

void merge(FILE* f1, FILE* f2,int index){
	
	//opening the file with an appropriate name
		
	char file[15];
	sprintf(file,"File%d.txt",index);	
	FILE* temp = fopen(file,"w");
	
	//#######################################################################################################################################
	
	//merging operation of 2 files
	
	int x1,x2,check;
	fscanf(f1,"%d",&x1);
	fscanf(f2,"%d",&x2);
	while(x1!=EOF && x2!=EOF){
		if(x1<=x2){
			fprintf(temp,"%d\n",x1);
			if(fscanf(f1,"%d",&check)==1){
				x1 = check;
			}
			else
				x1 = EOF;
		}
		else{
			fprintf(temp,"%d\n",x2);
			if(fscanf(f2,"%d",&check)==1){
				x2 = check;
			}
			else
				x2 = EOF;
		}
	}	
	while(x1!=EOF){
		fprintf(temp,"%d\n",x1);
		if(fscanf(f1,"%d",&check)==1){
			x1 = check;
		}
		else
			x1 = EOF;
	}	
	while(x2!=EOF){
		fprintf(temp,"%d\n",x2);
		if(fscanf(f2,"%d",&check)==1){
			x2 = check;
		}
		else
			x2 = EOF;
	}
	
	//###########################################################################################################################################
	
	fclose(f1); fclose(f2); fclose(temp);
}


// SORTING OPERATIONS ON THE ARRAY
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

// Merge sort is gonna work only till N = pow(2,14) where recursion depth is log2(N) = 14, not beyond depth
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
