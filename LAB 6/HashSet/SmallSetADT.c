#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

unsigned int readData(int K);
unsigned int set(unsigned int S, int j);
unsigned int union_sets(unsigned int S1, unsigned int S2);
unsigned int intersection_sets(unsigned int S1, unsigned int S2);
unsigned int difference_sets(unsigned int S1, unsigned int S2);
void print(unsigned int S);
int get(unsigned int S, int j);


int main(){
	int x,N,X,Y;
	unsigned int S1, S2;
	scanf("%d",&x);
	while(1){
		if(x == -1){
			break;
		}
	
		else if(x==0){
			scanf("%d%d%d",&N,&X,&Y); //just skipping N
			S1 = readData(X);
			S2 = readData(Y);
		}
		
		// UNION
		else if(x==1){
			union_sets(S1,S2);
		}
		
		// INTERSECTION
		else if(x==2){
			intersection_sets(S1,S2);	
		}
		
		// DIFFERENCE
		else if(x==3){
			difference_sets(S1,S2);
		}		
		scanf("%d",&x);
	}
	return 0;
}

//Reading the data
unsigned int readData(int K){
	int i;
	int V;
	unsigned int S = 0;
	for(i=0;i<K;i++){
		scanf("%d",&V);
		S = set(S,V+1);
	}
	return S;
}
unsigned int set(unsigned int S, int j){
	unsigned int B = 1<<(j-1);
	S = S|B;
	return S;	
}

//Union
unsigned int union_sets(unsigned int S1, unsigned int S2){
	unsigned int S3 = S1|S2;
	print(S3);
	return S3;
}

//Intersection
unsigned int intersection_sets(unsigned int S1, unsigned int S2){
	unsigned int S3 = S1&S2;
	print(S3);
	return S3;
}

//Difference
unsigned int difference_sets(unsigned int S1, unsigned int S2){
	unsigned int S3 = S1&S2;
	unsigned int S4 = ~S3;
	unsigned int S5 = S1&S4;
	print(S5);
	return S5;
}


//Printing the resulting set
void print(unsigned int S){
	int i,bit, flag = 0;
	for(i=1;i<=32;i++){
		bit = get(S,i);
		if(bit==1){
			printf("%d ",i-1);
			flag = 1;
		}
	}
	if(flag==1)
		printf("\n");
	else
		printf("NULL\n");
}
int get(unsigned int S, int j){
	unsigned int B = 1<<(j-1);
	B = S&B;
	return (B==0)?0:1;
}
