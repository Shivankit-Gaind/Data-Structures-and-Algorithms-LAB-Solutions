#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>


struct student{
	char name[21];
	double marks1;
	double marks2;
};

void quick_sort(struct student* records, int low, int high);
int partition(struct student* records, int low, int high);
void swap(struct student* records, int i, int j);
void partial_quicksort(struct student* records, int low, int high, int t);
void insert_sort(struct student* records,int low,int high);
void insert_in_sorted_order(struct student* a, struct student element,int length,int low);
void quick_insert_sort(struct student* records, int low, int high, int t);

int main(){
	struct student* a;
	int x,t,n,i;


	scanf("%d",&x);
	while(1){
		if(x==-1)
			break;

		// Taking records as input
		else if(x==0){
			scanf("%d",&n);
			a = (struct student*)malloc(n*sizeof(struct student));
			for(i=0;i<n;i++){
				scanf("%s",a[i].name);
				scanf("%lf",&a[i].marks1);
				scanf("%lf",&a[i].marks2);
			}					
		}
		
		// PARTIAL QUICKSORT
		else if(x==1){
			struct student list_copy[n];
			for(i=0;i<n;i++){
				list_copy[i]= a[i];				
			}
			scanf("%d",&t);
			partial_quicksort(list_copy,0,n-1,t);

			for(i=0;i<n;i++){
				printf("%s ",list_copy[i].name);
				printf("%lf ",list_copy[i].marks1);
				printf("%lf ",list_copy[i].marks2);
				printf("\n");
			}
		}

		//COMPLETE QUICKSORT
		else if(x==2){
			struct student list_copy[n];
			for(i=0;i<n;i++){
				strcpy(list_copy[i].name,a[i].name);
				list_copy[i].marks1 = a[i].marks1;
				list_copy[i].marks2 = a[i].marks2;
			}
			quick_sort(list_copy,0,n-1);

			for(i=0;i<n;i++){
				printf("%s ",list_copy[i].name);
				printf("%lf ",list_copy[i].marks1);
				printf("%lf ",list_copy[i].marks2);
				printf("\n");
			}
		}				
		scanf("%d",&x);	
	}
	return 0;
}


void quick_sort(struct student* records, int low, int high){
	if(low<high){
		int p = partition(records,low,high);
		quick_sort(records,low,p-1);
		quick_sort(records,p+1,high);
	}
}

int partition(struct student* records, int low, int high){
	double pivot = records[high].marks1 + records[high].marks2;
	int i; int j = low;
	for(i=low;i<high;i++){
		if(records[i].marks1+records[i].marks2<=pivot){
			swap(records,i,j++);		
		}
	}
	swap(records,j,high);
	return j;
}

void swap(struct student* records, int i, int j){
	struct student temp = records[i];
	records[i] = records[j];
	records[j] = temp;
}


//PARTIAL QUICKSORT
void partial_quicksort(struct student* records, int low, int high, int t){
	if(low<high){
		if(high-low+1<t){
			return;
		}
		int p = partition(records,low,high);
		partial_quicksort(records,low,p-1,t);
		partial_quicksort(records,p+1,high,t);
	}
}




//QUICK INSERT SORT
void quick_insert_sort(struct student* records, int low, int high, int t){
	if(low<high){
		if(high-low+1<t){
			insert_sort(records,low,high);
			return;
		}
		int p = partition(records,low,high);
		quick_insert_sort(records,low,p-1,t);
		quick_insert_sort(records,p+1,high,t);
	}
}

void insert_sort(struct student* records,int low,int high){
	if(high==low){
		return;
	}
	struct student temp = records[high];
	insert_sort(records,low,high-1);
	insert_in_sorted_order(records,temp,high-1,low);
}

void insert_in_sorted_order(struct student* a, struct student element,int length,int low){
	int i = length;
	for(;i>=low;i--){
		if(element.marks1 + element.marks2 > a[i].marks1 + a[i].marks2)
			break;
		a[i+1] = a[i];
	}
	a[i+1] = element;
}
