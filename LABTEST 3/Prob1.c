#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


struct node{
	struct node **children;
	char c;
	int isLeaf;
};
typedef struct node* Node;

struct trie{
	int count;
	Node root;
};
typedef struct trie* Trie;


Node createNode();
Trie create_trie();
Trie createEmptyTrie();
void add(Trie t, char* string);
int find(Trie t, char* string);
int find_assist(Node n, char* string, int index);
void printTrie(Trie t);
void print_assist(Node n);
void findPrefix(Trie t, char* string);


int main(){
	int x;
	Trie t = NULL;
	char str[600];
	
	scanf("%d",&x);
	while(1){
		if(x==-1)
			break;
		else if(x==0){
			t = create_trie();
		}
		else if(x==1){
			printTrie(t);
		}
		else if(x==2){
			scanf("%s",str);
			printf("%d\n",find(t,str));
		}
		else if(x==3){
			scanf("%s",str);
			findPrefix(t,str);
		}
		
		scanf("%d",&x);
	}
	
	return 0;
}

//Reading data and adding them to the trie
Trie create_trie(){
	Trie t = createEmptyTrie();
	char str[600];
	char str2[2] = "X";
	scanf("%s",str);
	while(strcmp(str,str2)!=0){
		add(t,str);
		scanf("%s",str);
	}
	return t;
}

//Creating a new node
Node createNode(){
	Node n = (Node)malloc(1*sizeof(struct node));
	n->isLeaf = 0;
	n->children  = (Node*)malloc(4*sizeof(Node));
	int i;
	for(i=0;i<4;i++){
		n->children[i] = NULL;
	}
	return n;
}

//Creating an empty trie
Trie createEmptyTrie(){
	Trie t = (Trie)malloc(1*sizeof(struct trie));
	t->count = 0;
	t->root = createNode();
	t->root->c = '.';
	return t;
}

//Adding a sequence to the Trie
void add(Trie t, char* string){
	int i = 0,x;
	Node temp = t->root;
	while(i!=strlen(string)){
	
		if(string[i]=='A')
			x = 0;
		else if(string[i]=='C')
			x = 1;
		else if(string[i]=='G')
			x = 2;
		else if(string[i]=='T')
			x = 3;
			
		if(temp->children[x]==NULL){
			temp->children[x]=createNode();
		}
		temp = temp->children[x];
		temp->c = string[i];
		i++;
	}
	temp->isLeaf = 1;
}

//Finding whether a sequence exists in the trie or not
int find(Trie t, char* string){
	if(t==NULL)
		return -1;
		
	return find_assist(t->root,string,0);
}

//Assistant function for find -- recursive implementation
int find_assist(Node n, char* string, int index){
	if(string[index]=='\0'){
		return 1;	
	}
	
	int x;
	if(string[index]=='A')
		x = 0;
	else if(string[index]=='C')
		x = 1;
	else if(string[index]=='G')
		x = 2;
	else if(string[index]=='T')
		x = 3;
	
	if(n->children[x]==NULL)
		return -1;
		
	else 
		return find_assist(n->children[x],string,index+1);
}

//Printing the entire trie by DFS
void printTrie(Trie t){
	if(t==NULL)
		return;
		
	print_assist(t->root);
	printf("\n");	
}

//Assistant function for print -- recursive implementation
void print_assist(Node n){
	if(n==NULL)
		return;
	if(n->c!='.')
		printf("%c ",n->c);
	int i;
	for(i=0;i<4;i++){
		if(n->children[i]!=NULL){
			print_assist(n->children[i]);
		}
	}
}

//Find prefix function
void findPrefix(Trie t, char* string){
	if(t==NULL)
		return;
		
	Node temp = t->root;
	int i=0,x;
	while(i!=strlen(string)){
		if(string[i]=='A')
			x = 0;
		else if(string[i]=='C')
			x = 1;
		else if(string[i]=='G')
			x = 2;
		else if(string[i]=='T')
			x = 3;
			
		if(temp->children[x]!=NULL)	
			temp = temp->children[x];
		else
			break;
			
		i++;
	}
	
	if(i!=strlen(string)){
		printf("-1\n");
		return;
	}
		
		
	print_assist(temp);
	printf("\n");
}

