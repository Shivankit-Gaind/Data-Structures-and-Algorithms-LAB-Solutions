//Implementation Of N-Ary Trees with each node having Dynamic Number of Children

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


//Every Node has a linked list of children since the no. of children is dynamic
struct node{
	struct node* next;
	char str[100];
	struct linkedlist* list;	
};
typedef struct node* Node;

struct linkedlist{
	Node head;
	int no_children;
};

//Every Tree has a root whose str is NULL and a count of the total path names
struct tree{
	Node root;		
};
typedef struct tree* FILETree;


void readData(int N, FILETree Tree);
FILETree createEmptyTree();
Node createNode();
struct linkedlist* createEmptyList();
void add(FILETree Tree, char* path);
Node add_assist(Node received_node, char* string);
void insert(struct linkedlist* list, Node n);
Node find(struct linkedlist* list, char* string);
void lookUp(FILETree Tree, char* path);
Node lookUp_assist(Node received_node, char* string);


int main(){
	int x,N;
	char name[500];
	scanf("%d",&x);
	FILETree Tree = createEmptyTree();
	
	while(1){	
		
		if(x==-1)
			break;
			
		else if(x==1){
			scanf("%d",&N);		
			readData(N,Tree);			
		}
		
		else if(x==2){			
			scanf("%s",name);		
			lookUp(Tree, name);
		}		
		scanf("%d",&x);
	}	
	return 0;
}

//Reading the paths 
void readData(int N, FILETree Tree){
	int i;
	char path[500];
	for(i=0;i<N;i++){
		scanf("%s",path);
	
		add(Tree,path);
	}
}

//Creating an empty uninitialized FILETree
FILETree createEmptyTree(){
	FILETree Tree = (FILETree)malloc(1*(sizeof(struct tree)));
	Tree->root = createNode();
	return Tree;
}

//Creating a single Node of the  FILE Tree
Node createNode(){
	Node n = (Node)malloc(1*sizeof(struct node));		
	n->list = createEmptyList(); //Initializes an empty list of children
	n->next = NULL;	
	return n;
}

//Creating an empty linked list
struct linkedlist* createEmptyList(){
	struct linkedlist* list = (struct linkedlist*)malloc(1*sizeof(struct linkedlist)); 
	list->no_children = 0;
	list->head = NULL;
	return list;
}

//Constructing the FILE Tree
void add(FILETree Tree, char path[]){
	int l,count,z,j,y;
	char string[100];
	Node n = Tree->root;
	
		l = strlen(path)-1;
		z=1;
		//Start traversing the path name
		while(z<=l){
			count = 0;
			j = z;
			while(path[z]!='/' && path[z]!='\0'){
				count++;
				z++;
			}				
			
			for(y = j;y<j+count;y++){
				string[y-j] = path[y];			
			}			
			string[y-j] = '\0';	
			
			if(strlen(string)>0)
				n = add_assist(n,string);
				
			z++;			
		}
	
}
//Adding the extracted string to the FILE Tree
Node add_assist(Node received_node, char* string){  //This is an assistant function for 'add'
	struct linkedlist* ls = received_node->list;
	Node n = find(ls,string);
	if(n==NULL){
		n = createNode();
		strcpy(n->str,string);
		insert(ls,n);
	}
	return n;
}

//Finding whether the path exists or not
void lookUp(FILETree Tree, char* path){
	int y,l,count,z=1,j;
	char string[100];
	Node n = Tree->root;
	l = strlen(path)-1;
	
	while(z<=l){
			count = 0;
			j = z;
			while(path[z]!='/' && path[z]!='\0'){
				count++;
				z++;
			}				
			
			for(y = j;y<j+count;y++){
				string[y-j] = path[y];			
			}			
			string[y-j] = '\0';	
			
			if(strlen(string)>0)
				n = lookUp_assist(n,string);
				
			if(n==NULL){
				printf("NO\n");
				return;
			}			
			z++;			
		}
		
		printf("YES\n");	
}

//Assistant function for find
Node lookUp_assist(Node received_node, char* string){
	struct linkedlist* ls = received_node->list;
	return find(ls, string);
}


//Inserting a node at the front of a linked list
void insert(struct linkedlist* list, Node n){
	if(list->head == NULL){
		list->head = n;
		list->no_children++;
		return;
	}		
	n->next = list->head;
	list->head = n;
	list->no_children++;	
}

//Finding a node with a given str value in the linked list
Node find(struct linkedlist* list, char* string){
	if(list->head==NULL)
		return NULL;	
	Node temp = list->head;
	while(temp!=NULL){
		if(strcmp(temp->str,string)==0)
			return temp;		
		temp = temp->next;
	}
	return NULL;
}









