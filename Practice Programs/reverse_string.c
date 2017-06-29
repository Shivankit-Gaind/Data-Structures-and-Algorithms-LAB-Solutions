#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

void reverse_string(char* ch, int length, int init);

int main(){
	char ch[10];
	scanf("%s",&ch);	
	reverse_string(ch,strlen(ch)-1,0);
	printf("%s",ch);
	return 0;
}

//in place reversing of characters of string

void reverse_string(char* ch, int length,int init){
	if(init==strlen(ch)){
		return;
	}
	char temp = ch[init];
	reverse_string(ch,length-1,init+1);
	ch[length] = temp;
}


