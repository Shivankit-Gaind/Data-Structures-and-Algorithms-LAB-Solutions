#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<ctype.h>

struct node{
	struct node** children;
	int isLeaf;
};
typedef struct node* Node;

struct trie{
	int count;
	Node root;
};
typedef struct trie* Trie;


//Creates a new Node
Node createNode(){
	Node n = (Node)malloc(1*sizeof(struct node));
	n->isLeaf = 0;
	n->children = (Node*)malloc(26*sizeof(Node));
	int i;
	for(i=0;i<26;i++){
		n->children[i] = NULL;
	}
	return n;
}

//Creates a new Trie
Trie createTrie(){
	Trie t = (Trie)malloc(1*sizeof(struct trie));
	t->count = 0;
	t->root = createNode();
	return t;
}


//Adds a word into the trie
void add(Trie t, char* string){
	
	int i;
	for(i = 0; string[i]!='\0'; i++){
  		string[i] = tolower(string[i]);
	}
	
	Node temp = t->root;
	i=0;
	while(i!=strlen(string)){
		int x = string[i++]-97;
		if(temp->children[x]==NULL){
			temp->children[x] = createNode();			
		}
		temp = temp->children[x];		
	}
	temp->isLeaf = 1;
}

//Searches for a string in the Trie -- Recursive
int find(Trie t, char* string){	
	int i;
	for(i = 0; string[i]!='\0'; i++){
		string[i] = tolower(string[i]);
	}	
	return find_assist(t->root,string,0);
}

int find_assist(Node n, char* string, int index){
	if(string[index]=='\0'){
		if(n->isLeaf==1)
			return 1;
		else
			return 0;
	}	
	if(n->children[string[index]-97]==NULL)
		return 0;
	else
		return find_assist(n->children[string[index]-97], string, index+1);	
}

//Testing the trie
int main(){
	int i;
	Trie t = createTrie();
	char str[10];
	
	for(i=0;i<5;i++){
		scanf("%s",str);
		add(t,str);
	}
	
	for(i=0;i<5;i++){
		scanf("%s",str);
		printf("%d\n",find(t,str));
	}	
	return 0;
}


