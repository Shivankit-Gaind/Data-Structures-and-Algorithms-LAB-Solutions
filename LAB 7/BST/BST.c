#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

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
Btree construct(int* arr, int N, Btree tree);
Btree randomConstruct(int* arr, int N, Btree tree);
int find(Btree tree, int element);
int assist_find(Node temp,int element);
int delete_key(Btree tree, int element);
Node minValue(Node temp);
Node maxValue(Node temp);
int get_height(Btree tree);
int assist_get_height(Node temp);
void experiment(Btree bst1, Btree bst2);


int main(){
	int x,N,key,bit;
	char tree_name[5];
	int* arr;
	
	Btree bst1 = (Btree)malloc(1*sizeof(struct binary_tree));
	bst1->root = NULL;
	bst1->count = 0;
	
	Btree bst2 = (Btree)malloc(1*sizeof(struct binary_tree));
	bst2->root = NULL;
	bst2->count = 0;
	
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
			scanf("%s",tree_name);
			if(strcmp(tree_name,"bst1")==0){
				add(bst1, key);
			}
			else
				add(bst2, key);
		}
		
		else if(x==2){
			bst1 = construct(arr,N,bst1);
		}
		
		else if(x==3){
			bst2 = randomConstruct(arr,N, bst2);
		}
		
		else if(x==4){
			scanf("%d",&key);
			scanf("%s",tree_name);
			if(strcmp(tree_name,"bst1")==0){
				bit = find(bst1, key);
			}
			else
				bit = find(bst2, key);
			printf("%d\n",bit);
		}
		
		else if(x==5){
			scanf("%d",&key);
			scanf("%s",tree_name);
			if(strcmp(tree_name,"bst1")==0){
				bit = delete_key(bst1, key);
			}
			else
				bit = delete_key(bst2, key);
			printf("%d\n",bit);
		}
		
		else if(x==6){
			int height;
			scanf("%s",tree_name);
			if(strcmp(tree_name,"bst1")==0){
				height = get_height(bst1);
			}
			else
				height = get_height(bst2);
			printf("%d\n",height);
		}
		
		else if(x==7){
			experiment(bst1,bst2);
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
	if(tree == NULL)
		return; //The tree is not initialized even	
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

//Constructing BST1
Btree construct(int* arr, int N, Btree tree){
	int i;	
	for(i=0;i<N;i++){
		add(tree, arr[i]);	
	} 
	return tree;
}

//Constructing BST2
Btree randomConstruct(int* arr, int N, Btree tree){	
	int cnt = 0;
	int random,i;
		
	//To keep a track of which elements have been added
	int added[N];
	for(i=0;i<N;i++)
		added[i] = 0;
	
	//Adding all elements to the BST	
	while(cnt!=N){
		random = rand()%N;
		if(added[random]==0){
			added[random] = 1;
			add(tree,arr[random]);
			cnt++;
		}
	}
	return tree;
}

//Finding an element in a BST
int find(Btree tree, int element){
	if(tree == NULL)
		return 0; //The tree is not initialized even	
		
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

//Deleting an element from BST
int delete_key(Btree tree, int element){
	if(tree == NULL)
		return 0; //The tree is not initialized even	
		
	if(find(tree,element)==0)
		return 0;
	
	//Locating the node to be deleted
	Node temp = tree->root;
	Node pretemp = tree->root;
	while(temp!=NULL){
		if(temp->key==element)
			break;
			
		pretemp = temp;
		
		if(temp->key>element){
			temp = temp->left;
		}
		else
			temp = temp->right;
	}
	
	int value = temp->key;
	/***********************************************************************/
	
	//If atleast one of the children of the node to be deleted is NULL
	
	if(temp->left == NULL){
		if(pretemp==temp){ //Node to be deleted is the root
			tree->root = temp->right;
		}
		else if(pretemp->left==temp){
			pretemp->left = temp->right;
		}
		else{
			pretemp->right = temp->right;
		}
		
	}
	else if(temp->right == NULL){
		if(pretemp==temp){ //Node to be deleted is the root
			tree->root = temp->left;
		}
		else if(pretemp->left==temp){
			pretemp->left = temp->left;
		}
		else{
			pretemp->right = temp->left;
		}
	}
	
	/************************************************************************/
	
	//If none of the children of the node to be deleted is NULL
	
	else{
		Node min = minValue(temp->right);
		int y = temp->key;
		temp->key = min->key;
		min->key = y;
		value = delete_key(tree,min->key);
		tree->count++; //To account for the decrement twice when the function is called twice
	}
	
	tree->count--;
	return value;
}

//Minimum value of a tree rooted at temp
Node minValue(Node temp){
	if(temp==NULL)
		return NULL;
	while(temp->left!=NULL)
		temp = temp->left;
	return temp;
}

//Maximum value of a tree rooted at temp
Node maxValue(Node temp){
	if(temp==NULL)
		return NULL;
	while(temp->right!=NULL)
		temp = temp->right;
	return temp;
}


//Height of a BST
int get_height(Btree tree){
	if(tree == NULL)
		return; //The tree is not initialized even	
		
	return assist_get_height(tree->root);
}
int assist_get_height(Node temp){
	if(temp==NULL)
		return -1;
	int l = assist_get_height(temp->left);
	int r = assist_get_height(temp->right);
	return (l>r)?(l+1):(r+1);
}

//Experiment
void experiment(Btree bst1, Btree bst2){
	if(bst1 == NULL || bst2 == NULL)
		return; //The tree is not initialized even	
	int h1 = get_height(bst1);
	int h2 = get_height(bst2);
	printf("Height of bst1 is %d\nHeight of bst2 is %d\n",h1,h2);
}




