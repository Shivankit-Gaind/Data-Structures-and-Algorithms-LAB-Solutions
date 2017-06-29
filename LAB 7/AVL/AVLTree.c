//AVL Tree is a better option than BST because Rotations take almost negligible time for every insertion

//Insert and Delete Operations are Recursive in Nature

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct node{
	int key;
	int balance_factor;
	struct node* left;
	struct node* right;
};
typedef struct node* Node;

struct balanced_tree{
	Node root;
	int count;
};
typedef struct balanced_tree* Btree;

int* readData(int N);
void add(Btree tree, int element);
Node add_assist(Node temp, int element);
Node leftRotate(Node temp);
Node rightRotate(Node temp);
Node newNode(int element);
Btree construct(int* arr, int N);
int find(Btree tree, int element);
int assist_find(Node temp,int element);
int get_height(Node temp);
int getBalance(Node temp);
Node minValue(Node temp);
int delete_key(Btree tree, int element);
Node delete_assist(Node temp, int element);

float measure_time;

int main(){
	int x,N,key;
	int* arr;
	Btree avlTree;
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
			add(avlTree, key);
		}
		
		else if(x==2){
			measure_time = 0;
			avlTree = construct(arr,N);		
		}
		
		else if(x==3){
			scanf("%d",&key);
			printf("%d\n",find(avlTree, key));
		}
		
		else if(x==4){
			printf("%f\n",measure_time);
		}
		
		else if(x==5){
			scanf("%d",&key);
			printf("%d\n",delete_key(avlTree, key));
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

//Adding an element to the AVL Tree
void add(Btree tree, int element){
	tree->count++;
	tree->root = add_assist(tree->root,element);	
}
Node add_assist(Node temp, int element){
	if(temp==NULL){
		return newNode(element);
	}	
	else if(element<temp->key){
		temp->left = add_assist(temp->left,element);
	}
	else if(element>temp->key){
		temp->right = add_assist(temp->right,element);
	}
	else return temp; //Duplicates are not allowed in the AVL Tree
	
	
	//Rotation
	int balance = temp->balance_factor = getBalance(temp);
	
	//Left Left Case
	if(balance>1 && temp->left->key > element){
		return rightRotate(temp);
	}
	
	//Right Right Case
	else if(balance<-1 && temp->right->key < element){
		return leftRotate(temp);
	}
	
	//Left Right Case
	else if(balance>1 && temp->left->key < element){
		temp->left = leftRotate(temp->left);
		return rightRotate(temp);
	}
	
	//Right Left Case
	else if(balance <-1 && temp->right->key > element){
		temp->right = rightRotate(temp->right);
		return leftRotate(temp);
	}	
	return temp;	
}

//Left Rotate
Node leftRotate(Node temp){
	time_t start,end;
	start = time(NULL);
	
	Node y = temp;
	Node x = y->right;
	Node T2 = x->left;
	
	x->left = y;
	y->right = T2;
	
	x->balance_factor = getBalance(x);
	y->balance_factor = getBalance(y);
	
	end  = time(NULL);
	measure_time+=difftime(end,start);
	
	return x;
}

//Right Rotate
Node rightRotate(Node temp){
	time_t start,end;
	start = time(NULL);
	
	Node y = temp;
	Node x = y->left;
	Node T2 = x->right;
	
	x->right = y;
	y->left = T2;
	
	x->balance_factor = getBalance(x);
	y->balance_factor = getBalance(y);
	
	end  = time(NULL);
	measure_time+=difftime(end,start);
	
	return x;
}

//Creates a new node from the given key
Node newNode(int element){
	Node new_node = (Node)malloc(1*sizeof(struct node));
	new_node->key = element;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->balance_factor = 0;
	return new_node;
}

//Constructing AVL tree
Btree construct(int* arr, int N){
	//Initializing an empty tree
	Btree tree = (Btree)malloc(1*sizeof(struct balanced_tree));
	tree->root = NULL;
	tree->count = 0;
	
	int i;
	
	for(i=0;i<N;i++){
		add(tree, arr[i]);
	} 
	return tree;
}

//Finding an element in an AVL tree
int find(Btree tree, int element){
	return assist_find(tree->root,element);
}
int assist_find(Node temp,int element){
	if(temp == NULL)
		return 0;
	else if(temp->key == element)
		return 1;
	else if(temp->key>element)
		return assist_find(temp->left,element);			
	else return assist_find(temp->right,element);
}


//Height of a Tree rooted at Node temp
int get_height(Node temp){
	if(temp==NULL)
		return -1;
	int l = get_height(temp->left);
	int r = get_height(temp->right);
	return (l>r)?(l+1):(r+1);
}

//Returns the balance factor of a tree rooted at Node temp
int getBalance(Node temp){
	if(temp==NULL){
		return 0;
	}
	int l = get_height(temp->left);
	int r = get_height(temp->right);
	return (l-r);
}

//Deleting the element from the AVL tree
int delete_key(Btree tree, int element){
	if(find(tree,element)==0)
		return 0;
	tree->count--;
	tree->root = delete_assist(tree->root,element);
	return element;
}
Node delete_assist(Node temp, int element){
	if(temp==NULL)
		return NULL;
	else if(temp->key > element){
		temp->left = delete_assist(temp->left,element);
	}
	else if(temp->key < element){
		temp->right = delete_assist(temp->right,element);
	}
	else{
		if(temp->left==NULL){
			Node temp2 = temp->right;
			free(temp);
			return temp2;
		}
		else if(temp->right == NULL){
			Node temp2 = temp->left;
			free(temp);
			return temp2;
		}
		else{
			Node temp2 = minValue(temp->right);
			temp->key = temp2->key;
			delete_assist(temp->right,temp->key);
		}
	}
	
	//Rotation
	int balance = temp->balance_factor = getBalance(temp);
	
	//Left Left Case
	if(balance>1 && temp->left->key > element){
		return rightRotate(temp);
	}
	
	//Right Right Case
	else if(balance<-1 && temp->right->key < element){
		return leftRotate(temp);
	}
	
	//Left Right Case
	else if(balance>1 && temp->left->key < element){
		temp->left = leftRotate(temp->left);
		return rightRotate(temp);
	}
	
	//Right Left Case
	else if(balance <-1 && temp->right->key > element){
		temp->right = rightRotate(temp->right);
		return leftRotate(temp);
	}	
	return temp;	
	
}

//Minimum value of a tree rooted at temp
Node minValue(Node temp){
	if(temp==NULL)
		return NULL;
	while(temp->left!=NULL)
		temp = temp->left;
	return temp;
}





