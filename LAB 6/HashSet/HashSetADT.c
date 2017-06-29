// I am assuming the universe is till from 0 to 99 otherwise dehashing can't be done


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

unsigned int* readData(int K, int M);
unsigned int set(unsigned int S, int j);
unsigned int* union_sets(unsigned int* S1, unsigned int* S2, int M);
unsigned int* intersection_sets(unsigned int* S1, unsigned int* S2, int M);
unsigned int* difference_sets(unsigned int* S1, unsigned int* S2, int M);
void print(unsigned int* S, int M);
int get(unsigned int S, int j);
int hash(int j,int M);


int main(){
	int x,M,N,X,Y;
	unsigned int* S1;
	unsigned int* S2;
	scanf("%d",&x);
	while(1){
		if(x == -1){
			break;
		}
	
		else if(x==0){
			scanf("%d%d%d%d",&M,&N,&X,&Y); //just skipping N
			S1 = readData(X,M);
			S2 = readData(Y,M);			
		}
		
		// UNION
		else if(x==1){
			union_sets(S1,S2,M);
		}
		
		// INTERSECTION
		else if(x==2){
			intersection_sets(S1,S2,M);	
		}
		
		// DIFFERENCE
		else if(x==3){
			difference_sets(S1,S2,M);
		}		
		scanf("%d",&x);
	}
	return 0;
}

//Reading the data
unsigned int* readData(int K, int M){	
	int i,N=32,h;
	int V;
	unsigned int* S = (unsigned int*)malloc(M*(sizeof(unsigned int)));
	for(i=0;i<M;i++){
		S[i] = 0;
	}
	for(i=0;i<K;i++){
		scanf("%d",&V);
		h = hash(V,M);
		S[h] = set(S[h],V%N+1); //V%M leads to hashing
	}
	return S;
}
unsigned int set(unsigned int S, int j){
	unsigned int B = 1<<(j-1);
	S = S|B;
	return S;	
}

//Union
unsigned int* union_sets(unsigned int* S1, unsigned int* S2, int M){
	int i;
	unsigned int* S3 = (unsigned int*)malloc(M*(sizeof(unsigned int)));
	for(i=0;i<M;i++){
		S3[i] = S1[i]|S2[i];
	}
	print(S3,M);
	return S3;
}

//Intersection
unsigned int* intersection_sets(unsigned int* S1, unsigned int* S2, int M){
	int i;
	unsigned int* S3 = (unsigned int*)malloc(M*(sizeof(unsigned int)));
	for(i=0;i<M;i++){
		S3[i] = S1[i]&S2[i];
	}
	print(S3,M);
	return S3;
}

//Difference
unsigned int* difference_sets(unsigned int* S1, unsigned int* S2, int M){
	unsigned int* S3 = (unsigned int*)malloc(M*(sizeof(unsigned int)));
	int i;
	for(i=0;i<M;i++){
		S3[i] = S1[i]&S2[i];
		S3[i] = ~S3[i];
		S3[i] = S1[i]&S3[i];
	}
	print(S3,M);
	return S3;
}


//Printing the resulting set
void print(unsigned int* S, int M){
	int i,bit, flag = 0, N=32,h;
	for(i=0;i<100;i++){
		h = hash(i,M);
		bit = get(S[h],i%N+1); //i%M leads to hashing
		if(bit==1){
			printf("%d ",i);
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

int hash(int j,int M){
	int x = abs(19*j+23);
	return x%M;
}
