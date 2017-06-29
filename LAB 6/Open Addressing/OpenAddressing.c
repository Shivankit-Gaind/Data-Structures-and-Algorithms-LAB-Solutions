#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct node{
	char* str;
	int deleted;
};
typedef struct node* Node;

struct combination{
	Node pointer;
	int probes;
};


struct hashtable{
	int probingscheme; //self added attribute
	int t;
	int size;
	int entries;
	double loadfactor;
	int findcount;
	int findprobes;
	double findratio;
	Node* list;
};
typedef struct hashtable* Hashtable;


char** readData(int* n);
Hashtable createHashtable(int t, int K);
void add(Hashtable table, char** data, int i);
int probe(Hashtable table, int h1 ,int j, char* string);
struct combination find(Hashtable table, char** data, int j);
void delete(Hashtable table, char** data, int j);
void lazyDelete(Hashtable table, char** data, int j);
void clear(Hashtable table);
void experiment(Hashtable table,char** data);
void sweep(Hashtable table);
int hash(char* string, int t);
int hash2(char* string, int t);



int main(){
	int N,x,K,t,i;
	scanf("%d",&x);
	char** data;
	Hashtable table;
	struct combination c;
	
	while(1){
		
		if(x==-1)
			break;
		
		else if(x==1){
			scanf("%d",&N);
			data = readData(&N);
		}
		
		else if(x==2){
			scanf("%d%d",&K,&t);
			table = createHashtable(t,K);
		}
		
		else if(x==3){
			scanf("%d",&i);
			c = find(table,data,i);
			table->findcount++;
			table->findprobes += c.probes;
			table->findratio = (double)table->findprobes/table->findcount;
		}
		
		else if(x==4){
			scanf("%d",&i);
			add(table,data,i);
		}
		
		else if(x==5){
			scanf("%d",&i);
			delete(table,data,i);
		}
		
		else if(x==6){
			scanf("%d",&i);
			lazyDelete(table,data,i);
		}
		
		else if(x==7){
			experiment(table,data);
		}
		
		else if(x==8){
			clear(table);
		}
		
		else if(x==9){
			sweep(table);
		}
		
		scanf("%d",&x);
	}
	return 0;
}

//Reading data 
char** readData(int* n){
	scanf("%d",n);
	char** data = (char**)malloc((*n)*sizeof(char*));
	int i;
	for(i = 0;i<(*n);i++){
		data[i] = (char*)malloc(20*sizeof(char));
		scanf("%s",data[i]);
	}
	return data;
}

//Create Empty Hashtable
Hashtable createHashtable(int t, int K){
	int i;
	Hashtable table = (Hashtable)malloc(sizeof(struct hashtable));
	table->probingscheme = K;
	table->entries = 0;
	table->findcount = 0;
	table->findprobes = 0;
	table->loadfactor = 0;
	table->t = t;
	table->size = pow(2,t);
	table->findratio = 0;
	table->list = (Node*)malloc((table->size)*sizeof(Node));
	for(i=0;i<table->size;i++){
		//Creating a node and assigning its character pointer to NULL
		Node n = (Node)malloc(sizeof(struct node));
		n->str = NULL;
		n->deleted = 0;	
		table->list[i] = n;
	}
	return table;
}

//It uses 3 functions--- find, hash and probe
void add(Hashtable table, char** data, int i){
	
	//If the element is already present -- return
	struct combination c = find(table,data,i);
	if(c.pointer->str!=NULL)
		return;
	
	char* string = data[i];
		
	//Hashing the string
	int h = hash(string,table->t);
		
	//Finding an empty slot
	int j = 1;
	while(table->list[h]->str!=NULL && table->list[i]->deleted!=1){		
		h = probe(table,h,j++,string);
	}
	
	//Adding the node to the found slot
	table->list[h]->str = string;	

	//Updating the variables of the hashtable
	table->entries++;
	table->loadfactor = (double)table->entries/table->size;
	
}

//Probing as per the nature of the probing scheme
int probe(Hashtable table, int h1 ,int j, char* string){
	int h2;
	if(table->probingscheme==0){
		return (h1+j)%table->size;
	}
	else if(table->probingscheme==1){
		return (h1+j*j)%table->size;
	}
	else if(table->probingscheme==2){
		h2 = hash2(string,table->t);
		return (h1+h2*j)%table->size;
	}
}

//Finding the element in the hashtable -- it uses hash, and probe functions
struct combination find(Hashtable table, char** data, int j){
	struct combination c; 	c.pointer = NULL;	c.probes = 0;
	int i;
	char* string = data[j];
	int h = hash(string,table->t);
	int visited[table->size];
	for(i=0;i<table->size;i++){
		visited[i] = 0;
	}
	int count=0, z=1;
	while(1){
		if(table->list[h]->str==NULL){
			break;
		}
		else{
			//If the string is found, return 
			if(strcmp(string,table->list[h]->str)==0){
				c.pointer = table->list[h];
				break;
			}
			else{
				if(visited[h]!=0){
					count++; // To keep a track of how many elements have been visited so far
					visited[h]=1;
					if(count==table->size)
						break;
				}

				//Probing the next slot and increasing the probe count
				h = probe(table,h,z++,string);
				c.probes++;
			}
		}
	}
	return c;
}

//Deleting a value by setting its character pointer to NULL
void delete(Hashtable table, char** data, int j){
	struct combination c = find(table,data,j);
	if(c.pointer!=NULL){
		c.pointer->str = NULL;
	}
}

void lazyDelete(Hashtable table, char** data, int j){
	struct combination c = find(table,data,j);
	if(c.pointer!=NULL){
		c.pointer->deleted = 1;
	}
}

//Clearing all the values present in the hashtable
void clear(Hashtable table){
	int i;
	table->entries = 0;
	table->findcount = 0;
	table->findprobes = 0;
	table->loadfactor = 0;
	table->findratio = 0;
	Node n;
	for(i=0;i<table->size;i++){
		table->list[i]->str = NULL;
		table->list[i]->deleted = 0;
	}
}

//Actual Experimenting with the functions
void experiment(Hashtable table,char** data){
	int clusterCount = 0;
	float clusterAvgSize = 0;
	int clustermaxSize = 0;

	int clusterSize = 0;

	int K,z,x,i,sum=0;
	scanf("%d",&K);
	for(z=0;z<K;z++){
		scanf("%d",&x);
		if(x==3){
			scanf("%d",&i);
			struct combination c = find(table,data,i);
			table->findcount++;
			table->findprobes += c.probes;
			table->findratio = (double)table->findprobes/table->findcount;
		}
		
		else if(x==4){
			scanf("%d",&i);
			add(table,data,i);
		}
		
		else if(x==5){
			scanf("%d",&i);
			delete(table,data,i);
		}
		
		else if(x==6){
			scanf("%d",&i);
			lazyDelete(table,data,i);
		}
		printf("%lf\t%lf\n",table->loadfactor,table->findratio);
	}

	//Procedure starts for finding clusters
	for(z=0;z<table->size;){
		while(z<table->size && table->list[z]->str==NULL){
			z++;
		}
		while(z<table->size && table->list[z]->str!=NULL){
			clusterSize++;
		}
		if(clusterSize>0){
			sum+=clusterSize;
			if(clusterSize>clustermaxSize)
				clustermaxSize = clusterSize;
			clusterCount++;
		}
		clusterSize = 0;
	}
	clusterAvgSize = (float)sum/clusterCount;
	printf("%d%f%d\n",clusterCount,clusterAvgSize,clustermaxSize);
}

void sweep(Hashtable table){
	int i;
	for(i=0;i<table->size;i++){
		int j = 1;
		int h = i;
		if(table->list[i]->deleted==1){
			while(table->list[h]->str!=NULL && table->list[h]->deleted!=0){
				table->list[h]-> deleted = 0;
				table->list[h]-> str = NULL;
				h = probe(table,h,j++,table->list[i]->str);
				if(h>=table->size)
					break;
			}
			
			//Pulling up the value
			if(h<table->size){
				table->list[i]->str = table->list[h]->str; //This can even be an empty string
				table->list[h]->str = NULL;
				table->list[h]->deleted = 0;
			}
		}
	}
}
/**
int hash(char* string, int t){
	unsigned long x = pow(2,32);
	unsigned int A = 65791;
	unsigned int mpre = 0;
	unsigned int m = 0;
	int i;
	int l = strlen(string);
	for(i=0;i<l;i++){
		m = (unsigned int)(mpre*A + (unsigned int)string[i])%x;
		mpre = m;
	}
	m = (m*7)%x;
	unsigned  B = pow(2,32);
	B = B&m;

}

int hash2(char* string, int t){
	unsigned int x = pow(2,32);
	unsigned int A = 65791;
	unsigned int mpre = 0;
	unsigned int m = 0;
	int i;
	int l = strlen(string);
	for(i=0;i<l;i++){
		m = (mpre*A + (unsigned int)string[i])%x;
		mpre = m;
	}
	m = (m*7)%x;
}
**/




