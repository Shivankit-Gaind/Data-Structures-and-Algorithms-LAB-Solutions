#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#define MAX(a,b) (((a)>(b))?(a):(b))

struct student{
	char name[21];
	double marks1;
	double marks2;
};

void quick_sort(struct student* records, int low, int high);
int partition_1(struct student* records, int low, int high);
int partition_2(struct student* records, int low, int high);
int partition_3(struct student* records, int low, int high);
void swap(struct student* records, int i, int j);
void quick_sort_last_element_as_pivot(struct student* records, int low, int high);
int partition_with_last_element_as_pivot(struct student* records, int low, int high);
int last_element_as_pivot(int low, int high);
void quick_sort_random_pivot(struct student* records, int low, int high);
int partition_with_random_element_as_pivot(struct student* records, int low, int high);
int random_pivot(int low, int high);
void quick_sort_with_quick_select(struct student* records, int low, int high);
void quickSelect(struct student* records, int low, int high, int k);
void quick_sort_with_medianOfMedians_as_pivot(struct student* records, int low, int high);
int partition_with_median_of_medians_as_pivot(struct student* records, int low, int high, int medianOfMedians);


int main(){
	struct student* a;
	int x,t,n,i;
	scanf("%d",&x);
	
			scanf("%d",&n);
			a = (struct student*)malloc(n*sizeof(struct student));
			
			for(i=0;i<n;i++){
				scanf("%s",a[i].name);
				scanf("%lf",&a[i].marks1);
				scanf("%lf",&a[i].marks2);
			}					
	
			struct student list_copy[n];
			
			for(i=0;i<n;i++){
				strcpy(list_copy[i].name,a[i].name);
				list_copy[i].marks1 = a[i].marks1;
				list_copy[i].marks2 = a[i].marks2;
			}
			quick_sort_with_quick_select(list_copy,0,n-1);

			for(i=0;i<n;i++){
				printf("%s ",list_copy[i].name);
				printf("%lf ",list_copy[i].marks1);
				printf("%lf ",list_copy[i].marks2);
				printf("\n");
			}		
	return 0;
}


//Quick Sort 
void quick_sort(struct student* records, int low, int high){
	if(low<high){
		int p = partition_1(records,low,high);
		quick_sort(records,low,p-1);
		quick_sort(records,p+1,high);
	}
}

//LOCALITY AWARE PARTITIONING
int partition_1(struct student* records, int low, int high){
	int index = high;
	double pivot = MAX(records[index].marks1 ,records[index].marks2);
	int i; int j = low;
	for(i=low;i<high;i++){
		if(MAX(records[i].marks1,records[i].marks2)<=pivot){
			swap(records,i,j++);		
		}
	}
	swap(records,j,high);
	return j;
}


//HOARE'S PARTITIONING
int partition_2(struct student* records, int low, int high){
	int h = high;
	double pivot = MAX(records[high].marks1 ,records[high].marks2);
	high--;
	while(low<high){
		while(MAX(records[low].marks1,records[low].marks2)<=pivot){
			low++;
		}
		while(MAX(records[high].marks1,records[high].marks2)>pivot){
			high--;
		}
		
		if(low<high){
			swap(records,low,high);
		}			
	}
	if(MAX(records[high].marks1 ,records[high].marks2)>pivot)
		swap(records,h,high);
	else{
		swap(records,h,high+1);
		high++;
	}
	return high;
}

// 3-WAY PARTITIONING
int partition_3(struct student* records, int low, int high){
	double value; int h = high;
	double pivot = MAX(records[high].marks1 ,records[high].marks2);
	high--;
	int mid = low;
	while(mid<high){
		value = MAX(records[mid].marks1,records[mid].marks2);
		if(value<pivot){
			swap(records,low,mid);
			low++;
			mid++;
		}
		else if(value == pivot){
			mid++;
		}
		else{
			swap(records,mid,high);
			high--;
		}
	}
	if(MAX(records[high].marks1 ,records[high].marks2)>pivot)
		swap(records,h,high);
	else{
		swap(records,h,high+1);
		high++;
	}
	return high;
}

void swap(struct student* records, int i, int j){
	struct student temp = records[i];
	records[i] = records[j];
	records[j] = temp;
}

/*****************************************************************************************************************************************************************************************/

//DIFFERENT PIVOT SELECTION TECHNIQUES


//Quick Sort with pivot selection as the last element
void quick_sort_last_element_as_pivot(struct student* records, int low, int high){
	if(low<high){
		int p = partition_with_last_element_as_pivot(records,low,high);
		quick_sort_last_element_as_pivot(records,low,p-1);
		quick_sort_last_element_as_pivot(records,p+1,high);
	}
}
//Partition around last element as pivot
int partition_with_last_element_as_pivot(struct student* records, int low, int high){
	int index = last_element_as_pivot(low,high);
	double pivot = MAX(records[index].marks1 ,records[index].marks2);
	int i; int j = low;
	for(i=low;i<high;i++){
		if(MAX(records[i].marks1,records[i].marks2)<=pivot){
			swap(records,i,j++);		
		}
	}
	swap(records,j,high);
	return j;
}
//PIVOT SELECTED AS THE LAST ELEMENT
int last_element_as_pivot(int low, int high){
	return high;
}



//Quick sort with random element selected as pivot
void quick_sort_random_pivot(struct student* records, int low, int high){
	if(low<high){
		int p = partition_with_random_element_as_pivot(records,low,high);
		quick_sort_random_pivot(records,low,p-1);
		quick_sort_random_pivot(records,p+1,high);
	}
}
//Partitioning around random element as pivot
int partition_with_random_element_as_pivot(struct student* records, int low, int high){
	int index = random_pivot(low,high);
	double pivot = MAX(records[index].marks1 ,records[index].marks2);
	swap(records,index,high);
	int i; int j = low;
	for(i=low;i<high;i++){
		if(MAX(records[i].marks1,records[i].marks2)<=pivot){
			swap(records,i,j++);		
		}
	}
	swap(records,j,high);
	return j;
}
//RANDOM PIVOT SELECTION
int random_pivot(int low, int high){
	return low + rand()%(high-low+1);
}



//Quick Sort with Quick Select as Pivot Selection Technique
void quick_sort_with_quick_select(struct student* records, int low, int high){
	if(low<high){
		int k = (high+low)/2; //Balanced Partitioning
		quickSelect(records,low,high,k); 
		quick_sort_with_quick_select(records,low,k-1);
		quick_sort_with_quick_select(records,k+1,high);
	}
}
// QUICK SELECT FOR SELECTING For Partitioning Around MIDDLE Element
void quickSelect(struct student* records, int low, int high, int k){
	if(low<high){
		int p = partition_with_random_element_as_pivot(records,low,high); //Randomised Quick Select
		if(p==k){
			return;
		}
		else if(k<p){
			quickSelect(records,low,p-1,k);
		}
		else{
			quickSelect(records,p+1,high,k);
		}
	}
}


//Quick Sort with Median Of Medians as Pivot
void quick_sort_with_medianOfMedians_as_pivot(struct student* records, int low, int high){
	if(low<high){
		int medianOfMedians = find_medianOfMedians();
		int p = partition_with_median_of_medians_as_pivot(records,low,high,medianOfMedians);
		quick_sort_with_medianOfMedians_as_pivot(records,low,p-1);
		quick_sort_with_medianOfMedians_as_pivot(records,p+1,high);
	}
}
//Partitioning around Median of Medians
int partition_with_median_of_medians_as_pivot(struct student* records, int low, int high, int medianOfMedians){
	int i; int j = low,index;
	for(i=low;i<=high;i++){
		if(MAX(records[i].marks1 ,records[i].marks2) == medianOfMedians){
			index = i;
			break;	
		}			
	}
	double pivot = MAX(records[index].marks1 ,records[index].marks2); //which will be Median of Medians
	swap(records,index,high);
	for(i=low;i<high;i++){
		if(MAX(records[i].marks1,records[i].marks2)<=pivot){
			swap(records,i,j++);		
		}
	}
	swap(records,j,high);
	return j;
}
//Finding Median
int findMedian(int* arr, int n){
	
}
// Finding Median Of Medians
void find_medianOfMedians(){
	
}












