#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>




//Binary Tree

struct node{
	int key;
	struct node* left;
	struct node* right;
};
typedef struct node* Node;

struct binary_tree{
	Node root;
	int count;
};
typedef struct binary_tree* Btree;

int* readData(int N);
void add(Btree tree, int element);
Btree construct(int* arr, int N);
void inOrderTravRec(Btree tree);
void inorderTraversal_assist(Node temp);
void inOrderTravIter(Btree tree);
void findkthSmallest(Btree tree, int k);
void findBetweenKeys(Btree tree, int k1, int k2);




//Stack

struct node2{
	Node n;
	struct node2* next;
};

struct linkedlist{
	struct node2* first;
	int count;
};

void insertFirst(struct linkedlist * head,Node n);
struct node2* deleteFirst(struct linkedlist * head);

void push(struct linkedlist* head, Node n);
Node pop(struct linkedlist* head);
int isEmpty(struct linkedlist* head);






int main(){
	int x,N,key,bit,k1,k2;
	int* arr;
	Btree bst;
	scanf("%d",&x);
	while(1){
		
		if(x==-1)
			break;
			
		else if(x==0){
			scanf("%d",&N);
			arr = readData(N);
		}
		
		else if(x==1){
			scanf("%d",&key);
			add(bst, key);
		}
		
		else if(x==2){
			bst = construct(arr,N);
		}
		
		else if(x==3){
			inOrderTravRec(bst);
		}
		
		else if(x==4){
			inOrderTravIter(bst);
		}
		
		else if(x==5){
			scanf("%d",&k1);
			findkthSmallest(bst,k1);
		}
		
		else if(x==6){
			scanf("%d%d",&k1,&k2);
			findBetweenKeys(bst,k1,k2);
		}
		
		scanf("%d",&x);		
	}
	return 0;
}

//Reading Input Data
int* readData(int N){
	int* arr = (int*)malloc(N*sizeof(int));
	int i;
	for(i=0;i<N;i++){
		scanf("%d",&arr[i]);
	}
	return arr;
}

//Adding an element to the BST
void add(Btree tree, int element){
	tree->count++;
	Node temp,pretemp;
	Node new_node = (Node)malloc(1*sizeof(struct node));
	new_node->key = element;
	new_node->left = NULL;
	new_node->right = NULL;
	if(tree->root==NULL){
		tree->root = new_node;
		return;
	}
	else{
		temp = tree->root;
		pretemp = temp;
		while(temp!=NULL){
			pretemp = temp;
			if(element>temp->key)
				temp = temp->right;
			else
				temp = temp->left;				
		}
		if(element>pretemp->key)
			pretemp->right = new_node;
		else
			pretemp->left = new_node;
	}	
}

//Constructing Binary Search Tree
Btree construct(int* arr, int N){
	//Initializing an empty tree
	Btree tree = (Btree)malloc(1*sizeof(struct binary_tree));
	tree->root = NULL;
	tree->count = 0;
	
	int i;
	
	for(i=0;i<N;i++){
		add(tree, arr[i]);	
	} 
	return tree;
}

//Recursive Inorder Traversal
void inOrderTravRec(Btree tree){
	inorderTraversal_assist(tree->root);
	printf("\n");
}
void inorderTraversal_assist(Node temp){
	if(temp==NULL)
		return;
	inorderTraversal_assist(temp->left);
	printf("%d ",temp->key);
	inorderTraversal_assist(temp->right);
}

//Iterative Inorder Traversal
void inOrderTravIter(Btree tree){
	//creating an empty stack
	struct linkedlist * stack = (struct linkedlist *) malloc (sizeof(struct linkedlist));

	Node temp = tree->root;
	while(1){
		while(temp!=NULL){
			push(stack,temp);
			temp = temp->left;
		}
		if(isEmpty(stack))
			break;
		else{
			temp = pop(stack);
			printf("%d ", temp->key);
			temp = temp->right;
		}
	}
	printf("\n");
}

//Finding the Kth Smallest element
void findkthSmallest(Btree tree, int k){
	//creating an empty stack
	struct linkedlist * stack = (struct linkedlist *) malloc (sizeof(struct linkedlist));
	int count = 0;

	Node temp = tree->root;
	while(1){
		while(temp!=NULL){
			push(stack,temp);
			temp = temp->left;
		}
		if(isEmpty(stack))
			break;
		else{
			temp = pop(stack);
			count++;
			if(count==k){
				printf("%d", temp->key);
				break;
			}			
			temp = temp->right;
		}
	}
	printf("\n");
}

//Range queries
void findBetweenKeys(Btree tree, int k1, int k2){
	struct linkedlist * stack = (struct linkedlist *) malloc (sizeof(struct linkedlist));
	int flag = 0;
	Node temp = tree->root;
	while(1){
		while(temp!=NULL){
			push(stack,temp);
			temp = temp->left;
		}
		if(isEmpty(stack))
			break;
		else{
			temp = pop(stack);
			if(temp->key>=k1){
				flag = 1;
			}
			if(temp->key>k2){
				break;
			}
			if(flag == 1){
				printf("%d ",temp->key);
			}
			temp = temp->right;
		}
	}
	printf("\n");
}



//Stack


void insertFirst(struct linkedlist* head, Node n){
	//create a node
	struct node2 *link = (struct node2*) malloc(sizeof(struct node2));
	
	/* by this you are creating a node whose address is being stored in the link pointer.*/
	
	link->n = n;
	//point it to old first node
	link -> next = head ->first;
	//point first to new first node
	
	head -> first = link;
	head -> count++;
}


struct node2* deleteFirst(struct linkedlist* head){
	if(head->first==NULL){
		return NULL;
	}
	
	struct node2* temp = head->first;
	head -> first = head->first->next;
	head->count--;
	return temp;
}



void push(struct linkedlist* head, Node n){
	insertFirst(head,n);
}
Node pop(struct linkedlist* head){
	struct node2* temp = deleteFirst(head);
	if(temp==NULL){
		return NULL;
	}
	return temp->n;
}

int isEmpty(struct linkedlist* head){
	if(head->first==NULL)
		return 1;
	else
		return 0;
}
