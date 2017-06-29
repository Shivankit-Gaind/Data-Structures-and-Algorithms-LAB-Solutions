#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

void print_permutations(char* ch,int init);
void swap(char* ch,int a,int b);

int main(){
	char ch[10];
	scanf("%s",&ch);
	print_permutations(ch,0);
	return 0;
}

void print_permutations(char* ch,int init){
	if(init==strlen(ch)-1){
		printf("%s ",ch);
		return;
	}
	int i;
	for(i = init;i<strlen(ch);i++){
		swap(ch,init,i);
		print_permutations(ch,init+1);
		swap(ch,init,i);		
	}
}

void swap(char* ch,int a,int b){
	char temp = ch[a];
	ch[a] = ch[b];
	ch[b] = temp;
}
