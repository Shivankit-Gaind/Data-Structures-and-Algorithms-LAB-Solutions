#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int* CreateBitVector();
void set(int* S);
int get(int* S);

int main(){
	
	int x;
	scanf("%d",&x);
	int* S;
	while(1){
		if(x==-1){
			break;
		}
	
		if(x==0){
			S = CreateBitVector();
		}
	
		else if(x==1){
			set(S);
		}
	
		else if(x==2){
			int bit = get(S);
			printf("%d\n",bit);			
		}
		
		scanf("%d",&x);
	}
	return 0;
}

int* CreateBitVector(){
	int N;
	scanf("%d",&N); 
	int* S = (int*)malloc(N*sizeof(int));
	int i;
	for(i=0;i<N;i++){
		S[i] = 0;
	}
	return S;
}

void set(int* S){
	int j;
	scanf("%d",&j);
	S[j-1] = 1;
}

int get(int* S){
	int j;
	scanf("%d",&j);
	return S[j-1];
}

