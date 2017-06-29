#include<stdio.h>
#include<conio.h>
#include<stdlib.h>


void push(int* a,int n,int *size,int* back,int element);
int pop(int *a,int n,int *size,int* front);
int peek(int *a,int n,int size,int front);
void print_queue(int *a,int n,int size,int front);


int main(){
	int n;
	scanf("%d",&n);
	int a[n];
	int x;
	int front = 0; int back = 0; int size = 0;
	while(1){
		scanf("%d",&x);
		if(x==-1)
			break;
		else if(x==0){
			scanf("%d",&x);
			push(a,n,&size,&back,x);
		}
		else if(x==1){
			printf("%d\n",pop(a,n,&size,&front));
		}
		else if(x==2){
			printf("%d\n",peek(a,n,size,front));
		}
		else if(x==3){
			print_queue(a,n,size,front);
		}
	}
}

void push(int* a,int n,int* size,int* back,int element){
	if(*size==n){
		printf("Queue Full");
		return;
	}
	a[*(back)%n] = element;
	*back = *back + 1;
	*size = *size+1;	
}

int pop(int *a,int n,int* size,int* front){
	if(*size==0){
		printf("Queue empty");
		return -1;
	}
	int temp = a[*(front)%n];
	*front = *front+1;
	*size = *size-1;
	return temp;
}

int peek(int *a,int n,int size,int front){
	if(size==0){
		printf("Queue empty");
		return -1;
	}
	return a[front%n];
}

void print_queue(int *a,int n,int size,int front){
	int x = front;
	int i;
	for(i=0;i<(size);i++){
		printf("%d ",a[(x++)%n]);
	}
}
