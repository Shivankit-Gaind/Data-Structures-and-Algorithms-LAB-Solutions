#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

unsigned int CreateBitVector();
unsigned int set(unsigned int S);
int get(unsigned int S);

int main(){
	
	int x;
	scanf("%d",&x);
	unsigned int S;
	while(1){
		if(x==-1){
			break;
		}
	
		if(x==0){
			S = CreateBitVector();
		}
	
		else if(x==1){
			S = set(S);
		}
	
		else if(x==2){
			int bit = get(S);
			printf("%d\n",bit);			
		}
		
		scanf("%d",&x);
	}
	return 0;
}

unsigned int CreateBitVector(){
	unsigned int S = 0;
	return S;
}

unsigned int set(unsigned int S){
	int j;
	scanf("%d",&j);
	unsigned int B = 1<<(j-1);
	S = S|B;
	return S;	
}

int get(unsigned int S){
	int j;
	scanf("%d",&j);
	unsigned int B = 1<<(j-1);
	B = S&B;
	return (B==0)?0:1;
}

