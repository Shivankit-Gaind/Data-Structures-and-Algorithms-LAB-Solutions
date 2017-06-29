#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

unsigned int CreateBitVector1();
int* CreateBitVector2(int N);
unsigned int insert1(unsigned int S, int L);
void insert2(int* S, int N, int L);
unsigned int set1(unsigned int S,int j);
void set2(int* S, int j);
int find1(unsigned int S, int L);
int find2(int* S,int N, int L);
int get1(unsigned int S, int j);
int get2(int* S, int j);
int Hash(int V, int A, int B, int N);
void experiment1(unsigned int S);
void experiment2(int* S, int N);
double FPrate(int m, int n, int d);

//Global Variables
int m1 = 0;
int m2 = 0;

int main(){	
	int x,N,i;
	scanf("%d",&x);
	unsigned int S1; //for word implementation
	int* S2; //for array implementation
	int X;
	while(1){
		if(x==-1){
			break;
		}
	
		if(x==0){
			scanf("%d",&X);
			switch(X){
				case 1:
					S1 = CreateBitVector1();
					break;
				case 2:
					scanf("%d",&N);
					S2 = CreateBitVector2(N);
					break;
			}			
		}
		
		// INSERT
		else if(x==1){
			switch(X){
				case 1:
					S1 = insert1(S1,5);
					break;
				case 2:
					insert2(S2,N,5);
					break;
			}	
		}
		
		// FIND
		else if(x==2){
			int bit;
			switch(X){
				case 1:
					bit = find1(S1,5);
					break;
				case 2:
					bit = find2(S2,N,5);
					break;
			}
			printf("%d\n",bit);			
		}
		
		// CLEAR
		else if(x==3){
			switch(X){
				case 1: 
					S1 = 0; m1=0;
					break;
				case 2:
					for(i=0;i<N;i++){
						S2[i] = 0;
					}
					m2 = 0;
			}
		}
		
		//EXPERIMENT
		else if(x==4){
			switch(X){
				case 1:
					experiment1(S1);
					break;
				case 2:
					experiment2(S2,N);
					break;
			}
		}
		
		scanf("%d",&x);
	}
	return 0;
}

int Hash(int V, int A, int B, int N){
	int h = abs(A*V + B);
	return h%N;

}

unsigned int CreateBitVector1(){
	int N;
	scanf("%d",&N); //just for skipping N
	unsigned int S = 0;
	m1=0;
	return S;
}

int* CreateBitVector2(int N){
	int* S = (int*)malloc(N*sizeof(int));
	int i;
	for(i=0;i<N;i++){
		S[i] = 0;
	}
	m2=0;
	return S;
}

unsigned int insert1(unsigned int S, int L){
	int V,i,h,bit;
	scanf("%d",&V);
	int flag = 0;
	for(i=1;i<=L;i++){
		switch(i){
			case 1: 
				h = Hash(V,7,11,32);
				break;
			case 2: 
				h = Hash(V,11,13,32);
				break;
			case 3: 
				h = Hash(V,13,17,32);
				break;
			case 4: 
				h = Hash(V,17,19,32);
				break;
			case 5: 
				h = Hash(V,19,23,32);
				break;
		}
		bit = get1(S,h+1);
		if(bit == 0){
			S = set1(S,h+1);
			flag = 1;
		}			
	}
	if(flag==1) // so that it doesn't get incremented if we insert the same element again
		m1++;
	return S;
}

void insert2(int* S, int N, int L){
	int V,i,h,bit;
	scanf("%d",&V);
	int flag = 0;
	for(i=1;i<=L;i++){
		switch(i){
			case 1: 
				h = Hash(V,7,11,N);
				break;
			case 2: 
				h = Hash(V,11,13,N);
				break;
			case 3: 
				h = Hash(V,13,17,N);
				break;
			case 4: 
				h = Hash(V,17,19,N);
				break;
			case 5: 
				h = Hash(V,19,23,N);
				break;
		}
		
		bit = get2(S,h+1);
		if(bit == 0){
			set2(S,h+1);
			flag = 1;
		}
	}
	if(flag==1) // so that it doesn't get incremented if we insert the same element again
		m2++;
}

unsigned int set1(unsigned int S,int j){
	unsigned int B = ((unsigned int)1)<<(j-(unsigned int)1);
	S = S|B;
	return S;	
}

void set2(int* S, int j){
	S[j-1] = 1;
}


int find1(unsigned int S, int L){
	int V,i,h,bit;
	scanf("%d",&V);
	for(i=1;i<=L;i++){
		switch(i){
			case 1: 
				h = Hash(V,7,11,32);
				break;
			case 2: 
				h = Hash(V,11,13,32);
				break;
			case 3: 
				h = Hash(V,13,17,32);
				break;
			case 4: 
				h = Hash(V,17,19,32);
				break;
			case 5: 
				h = Hash(V,19,23,32);
				break;
		}
		bit = get1(S,h+1);
		if(bit==0)
			return 0;
	}
	return 1;
}

int find2(int* S, int N, int L){
	int V,i,h,bit;
	scanf("%d",&V);
	for(i=1;i<=L;i++){
		switch(i){
			case 1: 
				h = Hash(V,7,11,N);
				break;
			case 2: 
				h = Hash(V,11,13,N);
				break;
			case 3: 
				h = Hash(V,13,17,N);
				break;
			case 4: 
				h = Hash(V,17,19,N);
				break;
			case 5: 
				h = Hash(V,19,23,N);
				break;
		}
		bit = get2(S,h+1);
		if(bit==0)
			return 0;
	}
	return 1;
}

int get1(unsigned int S, int j){
	unsigned int B = ((unsigned int)1)<<(j-(unsigned int)1);
	B = S&B;
	return (B==0)?0:1;
}

int get2(int* S, int j){
	return S[j-1];
}


void experiment1(unsigned int S){
	int K,L,i;
	int V,x,bit;
	scanf("%d%d",&K,&L);
	for(i=1;i<=K;i++){
		scanf("%d",&x);
		if(x==1){
			insert1(S,L);
		}
		else{
			bit = find1(S,L);
			printf("%d\t",bit);
		}
		printf("%f\n",FPrate(m1,32,L));
	}
}


void experiment2(int* S, int N){
	int K,L,i;
	int V,x,bit;
	scanf("%d%d",&K,&L);
	for(i=1;i<=K;i++){
		scanf("%d",&x);
		if(x==1){
			insert2(S,N,L);
		}
		else{
			bit = find2(S,N,L);
			printf("%d\t",bit);
		}
		printf("%lf\n",FPrate(m2,N,L));
	}
}

double FPrate(int m, int n, int d){
	double FP;
	FP = pow(1.0- exp((-1.0)*((double)m*(double)d/(double)n)),d);
	return FP;
}




