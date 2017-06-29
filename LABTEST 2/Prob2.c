#include"Prob2.h"

int main(){
	char** strings;
	char** strings_copy;
	int x,d,i,n,w;
	scanf("%d",&x);
	while(1){
		if(x==-1)
			break;
		
		else if(x==1){
			scanf("%d",&n);
			scanf("%d",&w);
			strings = readStrings(n,w);
		}
		
		else if(x==2){
			scanf("%d",&d);			
			// Making a copy
			strings_copy = (char**)malloc(n*sizeof(char*));
			for(i=0;i<n;i++){
				strings_copy[i] = (char*)malloc(w*sizeof(char));
				strcpy(strings_copy[i],strings[i]);
			}
			
			part3way3keys(strings_copy,0,n-1,d);
			print_strings(strings,0,n-1);
		}
		
		else if(x==3){
			radixPart3waySort(strings,n);
			print_strings(strings, 0,n-1);
		}		
		
		scanf("%d",&x);
	}
	return 0;
}

//Printing all the strings
void print_strings(char** strings, int low, int high){
	int i;
	for(i=low;i<=high;i++){
		printf("%s\n",strings[i]);
	}
}

// reading strings and returning to the driver function
char** readStrings(int n, int w){
	int i;
 	char** strings;
	strings = (char**)malloc(n*sizeof(char*));
	for(i=0;i<n;i++){
		strings[i] = (char*)malloc(w*sizeof(char));
		scanf("%s",strings[i]);
	}
	return strings;
}


//Radix Partition Sort
void radixPartitionSort(char** strings, int low, int high, int d){
	struct index ind;
	if(low<high){
		ind = part3way3keys(strings,low,high,d);
		int p = ind.i;
		int q = ind.j;
		radixPartitionSort(strings,low,p-1,d);
		radixPartitionSort(strings,q+1,high,d);
	}

}

//Complete radixPart3waySort
void radixPart3waySort(char** strings, int n){
	int w = strlen(strings[0]);
	int i;
	for(i=w-1;i>=0;i--){
		radixPartitionSort(strings,0,n-1,i);
	}	
}

//3-Way Partitioning Algorithm
struct index part3way3keys(char** strings, int low, int high, int d){
	char pivot =  strings[high][d];
	int m;
	int r1 = high-1;
	int l1 = low;
	int l2 = low;
	int r2 = high-1;
	while(l1<l2){
		while(strings[l1][d]<pivot){
			l1++;
		}
		while(strings[r1][d]>pivot){
			r1--;
		}
		if(l1<r1){
			if(strings[l1][d]==pivot){
				swap(strings,l1,l2);
				l1++;
				l2++;
			}
			if(strings[r1][d]==pivot){
				swap(strings,r2,r1);
				r2--;
				r1--;
			}
		}		
	}
	int p = l2-1;
	int q = r2+1;
	if(strings[l1][d]>pivot){
		m = l1-1;
	}
	else{
		m = l1;
	}
	//division done till here (1st part where we get values of p,m and q)
	/*****************************************************************************************/
	
	//Returning struct index pair
	struct index ind;
	ind.i = p;
	ind.j = q;
	return ind;
}

void swap(char** strings, int low, int high){
	int w = strlen(strings[0]);  
	char* temp = (char*)malloc(w*sizeof(char));
	strcpy(temp,strings[low]);
	strcpy(strings[low],strings[high]);
	strcpy(strings[high],temp);
}



