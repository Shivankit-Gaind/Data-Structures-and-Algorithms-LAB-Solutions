//Implementation Of N-Ary Trees with each node having Dynamic Number of Children

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int global;

//Every Node has a linked list of children since the no. of children is dynamic
struct node{
	struct node* next;
	char str[100];
	struct linkedlist* list;
	int isLeaf; //The concept of isLeaf also avoids the partial addresses lookup to be true
	
};
typedef struct node* Node;

struct linkedlist{
	Node head;
	int no_children;
};

//Every Tree has a root whose str is NULL and a count of the total domain names
struct tree{
	Node root;
	int count;		
};
typedef struct tree* DNSTree;

//Every tuple consists of a domain name and a corresponding IP address
struct data{
	char domain[100];
	char IP[20];
};

void readData(int N,DNSTree Tree);
DNSTree createEmptyTree();
Node createNode();
struct linkedlist* createEmptyList();
void add(DNSTree Tree, char* dom, char* ip, int N);
Node add_assist(Node received_node, char* string);
void insert(struct linkedlist* list, Node n);
Node find(struct linkedlist* list, char* string);
void lookUp(DNSTree Tree, char* dom);
Node lookUp_assist(Node received_node, char* string);


int main(){
	int x,N;
	char name[100];
	scanf("%d",&x);
	struct data* DATA;
	DNSTree Tree = createEmptyTree();
	
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

//Reading the domains and their corresponding IP's
void readData(int N, DNSTree Tree){
	int i;
	struct data DATA;
	for(i=0;i<N;i++){
		scanf("%s",DATA.domain);				
		scanf("%s",DATA.IP);
		add(Tree,DATA.domain,DATA.IP,N);	
	}	
}

//Creating an empty uninitialized DNSTree
DNSTree createEmptyTree(){
	DNSTree Tree = (DNSTree)malloc(1*(sizeof(struct tree)));
	Tree->root = createNode();
	Tree->count = 0;	
	return Tree;
}

//Creating a single Node of the DNS Tree
Node createNode(){
	Node n = (Node)malloc(1*sizeof(struct node));		
	n->list = createEmptyList(); //Initializes an empty list of children
	n->next = NULL;
	n->isLeaf = 0;
	return n;
}

//Creating an empty linked list
struct linkedlist* createEmptyList(){
	struct linkedlist* list = (struct linkedlist*)malloc(1*sizeof(struct linkedlist)); 
	list->no_children = 0;
	list->head = NULL;
	return list;
}

//Constructing the DNS Tree
void add(DNSTree Tree, char* dom, char* ip, int N){
	int l = strlen(dom)-1,count,z,flag=0,j;
	char string[20];
	Node n = Tree->root;
		
		//Start traversing the domain name
		while(1){
			count = 0;
			z=0;

			while(l!=-1 && dom[l]!='.'){
				l--;
				count++;
			}
			
			if(l==-1){
				flag=1;				 
			}
			
			l++; //To skip the dot
								
			for(j=l;j<l+count;j++){
				string[z++] = dom[j];
			}
			string[z] ='\0'; //Marking the end of the string
	
			if(strlen(string)>0)
				n = add_assist(n,string);
						
			//If the string is over
			if(flag==1)
				break;
				
			l = l-2; //To skip dots
		}
		
		n = add_assist(n,ip); //Adding the IP address as the leaf node
		n->isLeaf = 1;
	
}
//Adding the extracted string to the DNS Tree
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

//Finding the IP address of a domain name if it exists
void lookUp(DNSTree Tree, char* dom){
	int* trace = (int*)malloc(10*sizeof(int)); //To be printed if the element to be looked up is not found
	int i = 0,y=0,l,count,z,flag,j;
	char string[20];
	Node n = Tree->root;
	l = strlen(dom)-1;
	flag=0;	
	while(1){
		count = 0;
		z=0;
		while(l!=-1 && dom[l]!='.'){
			l--;
			count++;
		}
		if(l==-1){
			flag=1;				 
		}
		
		l++; //To skip the dot
							
		for(j=l;j<l+count;j++){
			string[z++] = dom[j];
		}
		string[z] ='\0'; //Marking the end of the string
	
		if(strlen(string)>0)
			n = lookUp_assist(n,string);
		
		if(n==NULL)
			break;				
		else
			trace[y++] = global;

		//If the string is over
		if(flag==1)
			break;
			
		l = l-2; //To skip dots
	}
	if(n!=NULL && n->list->head->isLeaf == 1){
		printf("%s\n",n->list->head->str); //Its gonna be a leaf node
	}
	else{
		for(i=0;i<y;i++){
			printf("%d ",trace[i]);
		}
		printf("\n");
	}
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
	Node temp = list->head;
	while(temp->next!=NULL)
		temp = temp->next;	
	
	temp->next = n;
	
	list->no_children++;	
}

//Finding a node with a given str value in the linked list
Node find(struct linkedlist* list, char* string){
	global = 0;
	if(list->head==NULL)
		return NULL;	
	Node temp = list->head;
	while(temp!=NULL){
		if(strcmp(temp->str,string)==0)
			return temp;		
		temp = temp->next;
		global++;
	}
	return NULL;
}







