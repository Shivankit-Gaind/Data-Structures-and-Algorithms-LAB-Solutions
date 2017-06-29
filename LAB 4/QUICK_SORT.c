#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

struct student{
	char name[21];
	unsigned int marks;
};

struct index{
	int l;
	int h;
};

struct node{
	struct index element;
	struct node* next;
};

struct linkedlist{
	struct node* first;
	int count;
};

void partial_quicksort(struct student* records, int low, int high, int t);
void quick_sort_1(struct student* records, int low, int high);
void quick_sort_2(struct student* records, int low, int high);
void quick_sort_3(struct student* records, int low, int high);
void quick_sort_4(struct student* records, int low, int high);
int partition(struct student* records, int low, int high);
void swap(struct student* records, int i, int j);

void push(struct linkedlist* head, struct index ele);
struct index pop(struct linkedlist* head);
struct index top(struct linkedlist* head);
int empty(struct linkedlist* head);

void insertFirst(struct linkedlist* head, struct index ele);
struct node* deleteFirst(struct linkedlist* head);

int main(){
	struct student* a;
	int x,t,n,i;
	scanf("%d",&x);	
	while(1){
		if(x==-1)
			break;
			
		else if(x==0){
			scanf("%d",&n);
			a = (struct student*)malloc(n*sizeof(struct student));			
			for(i=0;i<n;i++){
				scanf("%s",a[i].name);
				scanf("%u",&a[i].marks);
			}					
		}
		
		else if(x==1){
			scanf("%d",&t);
			struct student list_copy[n];			
			for(i=0;i<n;i++){
				strcpy(list_copy[i].name,a[i].name);
				list_copy[i].marks = a[i].marks;
			}
			
			partial_quicksort(list_copy,0,n-1,t);

			for(i=0;i<n;i++){
				printf("%s ",list_copy[i].name);
				printf("%u ",list_copy[i].marks);
				printf("\n");
			}
		}
		
		else if(x==2){
			scanf("%d",&t);
			struct student list_copy[n];
			for(i=0;i<n;i++){
				strcpy(list_copy[i].name,a[i].name);
				list_copy[i].marks = a[i].marks;
			}
			
			switch(t){
				case 1:
					quick_sort_1(list_copy,0,n-1);
					break;
				case 2:
					quick_sort_2(list_copy,0,n-1);
					break;
				case 3:
					quick_sort_3(list_copy,0,n-1);
					break;
				case 4:
					quick_sort_4(list_copy,0,n-1);
					break;				
			}
						
			for(i=0;i<n;i++){
				printf("%s ",list_copy[i].name);
				printf("%u ",list_copy[i].marks);
				printf("\n");
			}
		}
		scanf("%d",&x);	
	}				
	return 0;
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

//NORMAL QUICKSORT
void quick_sort_1(struct student* records, int low, int high){
	if(low<high){
		int p = partition(records,low,high);
		quick_sort_1(records,low,p-1);
		quick_sort_1(records,p+1,high);
	}
}

//CONTROLLING CALL STACK DEPTH
void quick_sort_2(struct student* records, int low, int high){
	if(low<high){
		int p = partition(records,low,high);
		if(p-1-low>0) //CHECK BEFORE PUSHING TO STACK
			quick_sort_2(records,low,p-1);
		if(high-(p+1)>0) //CHECK BEFORE PUSHING TO STACK
			quick_sort_2(records,p+1,high);
	}
}

//ELIMINATING TAIL CALL RECURSION
void quick_sort_3(struct student* records, int low, int high){
	while(low<high){
		int p = partition(records,low,high);
		//MAKE SURE SHORTER LIST IS PUT ON THE STACK
		if(p-1-low<high-(p+1)){
			quick_sort_3(records,low,p-1);
			low = p+1; //tail call recursion removed
		}
		else{
			quick_sort_3(records,p+1,high);
			high = p-1; //tail call recursion removed
		}		
	}
}

//ELIMINATING RECURSION COMPLETELY
void quick_sort_4(struct student* records, int low, int high){	
	struct linkedlist* stack = (struct linkedlist *) malloc (sizeof(struct linkedlist));
	stack->first = NULL;
	stack->count = 0;
	struct index in;
	//ITERATIVE VERSION OF THE QUICK SORT
	while(1){
		while(low<high){
			int p = partition(records,low,high);
			in.l = low;
			in.h = p-1;
			push(stack,in);
			low = p+1;
		}
		if(!empty(stack)){
			low = top(stack).l;
			high = top(stack).h;
			pop(stack);
		}
		else{
			break;
		}
	}	
}

//PARTITIONING-- SAME FOR ALL
int partition(struct student* records, int low, int high){
	double pivot = records[high].marks;
	int i; int j = low;
	for(i=low;i<high;i++){
		if(records[i].marks<=pivot){
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


// STACK FUNCTIONS

void push(struct linkedlist* head, struct index ele){
	insertFirst(head,ele);
}
struct index pop(struct linkedlist* head){
	struct node* temp = deleteFirst(head);
	return temp->element;
}
struct index top(struct linkedlist* head){
	struct node* temp = head->first;
	return temp->element;
}
int empty(struct linkedlist* head){
	if(head->first==NULL)
		return 1;
	else
		return 0;
}

void insertFirst(struct linkedlist* head, struct index ele){
	//create a node
	struct node *link = (struct node*) malloc(sizeof(struct node));	
	/* by this you are creating a node whose address is being stored in the link pointer.*/	
	link->element = ele;
	//point it to old first node
	link -> next = head ->first;
	//point first to new first node	
	head -> first = link;
	head -> count++;
}

struct node* deleteFirst(struct linkedlist* head){
	struct node* temp = head->first;
	head -> first = head->first->next;
	head->count--;
	return temp;
}

