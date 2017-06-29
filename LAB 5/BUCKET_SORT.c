#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct node{
	int value;
	struct node* next;
};
typedef struct node* NODE;

struct linkedlist{
	NODE head;
	int count;
};
typedef struct linkedlist* list;

void SortSparseLists(int** arr, int n, int xlow, int xhigh, int ylow, int yhigh);
void InsertInOrder(list ls,int v);
void SortDenseLists(int** arr, int n, int xlow, int xhigh, int ylow, int yhigh);
void print_list(int** arr,int n);

int main(){
	int x,N,xlow,xhigh,ylow,yhigh,i;
	int **arr;
	scanf("%d",&x);
	
		//reading data
		if(x==0){
			scanf("%d%d%d%d%d",&N,&xlow,&xhigh,&ylow,&yhigh);
			arr = (int**)malloc(N*sizeof(int*));
			for(i=0;i<N;i++){
				arr[i] = (int*)malloc(2*sizeof(int));
				scanf("%d%d",&arr[i][0],&arr[i][1]);
			}
		}
		scanf("%d",&x);	
		
		//Sorting sparse lists
		if(x==1){
			SortSparseLists(arr,N,xlow,xhigh,ylow,yhigh);
		}
		
		//Sorting dense lists
		else if(x==2){
			SortDenseLists(arr,N,xlow,xhigh,ylow,yhigh);	
		}		
		
	
	return 0;
}

//FUNCTION TO SORT SPARSE LISTS
void SortSparseLists(int** arr, int n, int xlow, int xhigh, int ylow, int yhigh){
	int size,index,i,x_value,low,flag;
	
	if(xhigh-xlow>=yhigh-ylow){
		size = xhigh-xlow+1;
		low = xlow;
		flag=0;
	}
	else{
		size = yhigh-ylow+1;
		low = ylow;
		flag=1;
	}
	
	list* lists = (list*)malloc(size*sizeof(list));
	for(i=0;i<size;i++){
		lists[i] = (list)malloc(sizeof(struct linkedlist));
		lists[i]->head = NULL;
		lists[i]->count = 0;
	}
	
	//BUCKETING THE VALUES
	for(i=0;i<n;i++){
		if(flag == 0){
			index = arr[i][0]- low;	
			InsertInOrder(lists[index],arr[i][1]);
		}
		else{
			index = arr[i][1]- low;	
			InsertInOrder(lists[index],arr[i][0]);
		}
			
	}
	
	//COPYING BACK THE SORTED LIST INTO ARRAY
	int z = 0;
	for(i=0;i<size;i++){
		NODE temp = lists[i]->head;
		while(temp!=NULL){
			if(flag==0){
				arr[z][0] = i+low;
				arr[z][1] = temp->value;
			}
			else{
				arr[z][1] = i+low;
				arr[z][0] = temp->value;
			}			
			temp = temp->next;
			z++;
		}
	}	
	print_list(arr,n);
}

// ASSISTANT FUNCTION FOR SORTING SPARSE LISTS
void InsertInOrder(list ls,int v){
	NODE node = (NODE)malloc(sizeof(struct node));
	node->value = v;
	node->next = NULL;
	if(ls->head==NULL){
		ls->head = node;
	}
	else{
		NODE temp =ls->head;
		NODE pretemp = temp;
		while(temp!=NULL && temp->value<v){
			pretemp = temp;
			temp = temp->next;
		}
		if(pretemp == temp){
			node->next = temp;
			ls->head = node;
		}
		else{
			node->next = pretemp->next;
			pretemp->next = node;
		}
	}
	ls->count++;
}

//FUNCTION TO SORT DENSE LISTS
void SortDenseLists(int** arr, int n, int xlow, int xhigh, int ylow, int yhigh){
	int size1,size2,low1,low2,index1,index2,flag;
	int i,j;
	if(xhigh-xlow>=yhigh-ylow){
		size1 = xhigh-xlow+1;
		size2 = yhigh-ylow+1;
		low1 = xlow; low2 = ylow;
		flag = 0;
	}
	else{
		size1 = yhigh-ylow+1;
		size1 = xhigh-xlow+1;
		low1 = ylow; low2 = xlow;
		flag = 1;
	}	
	
	int** sort;
	sort = (int**)malloc(size1*sizeof(int*));
	for(i=0;i<size1;i++){
		sort[i] = (int*)malloc(size2*sizeof(int));
	}
	

	//MAKING ALL BUCKETS 0
	for(i=0;i<size1;i++){
		for(j=0;j<size2;j++){
			sort[i][j]=0;
		}
	}
		

	//BUCKETING THE VALUES(MULTIKEY)
	for(i=0;i<n;i++){
		if(flag==0){
			index1 = arr[i][0]- low1;	
			index2 = arr[i][1]-low2;
		}
		else{
			index1 = arr[i][1]- low1;	
			index2 = arr[i][0]-low2;	
		}
		
		sort[index1][index2]++;
	}
		

	//COPYING BACK THE SORTED LIST INTO ARRAY
	int z=0;
	for(i=0;i<size1;i++){
		for(j=0;j<size2;j++){			
			while(sort[i][j]!=0){
				if(flag==0){
					arr[z][0] = low1 + i;
					arr[z][1] = low2 + j;						
				}
				else{
					arr[z][0] = low2 + j;
					arr[z][1] = low1 + i;					
				}
				sort[i][j]--;					
				z++;
			}			
		}
	}		
	print_list(arr,n);
}

//PRINTING THE X-Y VALUES
void print_list(int** arr,int n){
	int i;
	for(i=0;i<n;i++){
		printf("%d %d\n",arr[i][0],arr[i][1]);
	}
}


