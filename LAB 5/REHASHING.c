#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


struct symbol{
	char* name;
	char* type;
};

struct node{
	struct symbol* s;
	struct node* next;
};
typedef struct node* NODE;

struct linkedlist{
	NODE head;
	int count;
};
typedef struct linkedlist* list;

struct Hashtable{
	int entries;
	int size;
	double loadfactor;
	int freeSlots;
	int insertionTime;
	int queryingTime;
	list* table;
};

struct symbol* readSymbols(int* n);
struct symbol* readQueries(int* n);
int hashingFunction(char* key, int size);
void insert(struct Hashtable* hashtable, struct symbol* s);
int isSlotEmpty(struct Hashtable* hashtable, int index);
int insertSymbol(struct Hashtable* hashtable, int index, struct symbol* sym);
struct Hashtable* createHashTable(struct Hashtable* hashtable, int size, double minLoad, double maxLoad, int resizeFactor, struct symbol* s, int n);
struct Hashtable* createEmptyHashTable(int size);
void PrintTabSeparated(int a, int b, double c, int d, int e);
void lookupQueries(struct Hashtable* hashtable, struct symbol* q, int n);
int lookup(struct Hashtable* hashtable, struct symbol* q);



int main(){
	int x;
	struct symbol* symbollist; int s;
	struct symbol* querylist; int q;
	struct Hashtable* hashtable;
	scanf("%d",&x);
	while(1){
		if(x==-1)
			break;
		else if(x==0){
			symbollist = readSymbols(&s);
		}
		else if(x==1){
			querylist = readQueries(&q);
		}
		else if(x==2){
			int size;	double minLoad;	double maxLoad; int resizeFactor;
			scanf("%d%lf%lf%d",&size,&minLoad,&maxLoad,&resizeFactor);
			hashtable = createHashTable(hashtable, size,minLoad,maxLoad,resizeFactor,symbollist,s);		
		}
		else if(x==3){
			lookupQueries(hashtable, querylist, q);
		}
		scanf("%d",&x);	
	}
	return 0;
}


//INPUT SYMBOLS
struct symbol* readSymbols(int* n){
	scanf("%d",n);
	struct symbol* symlist = (struct symbol*)malloc((*n)*sizeof(struct symbol));
	int i;
	for(i = 0;i<(*n);i++){
		symlist[i].name  = (char*)malloc(8*sizeof(char));
		symlist[i].type  = (char*)malloc(10*sizeof(char));
		scanf("%s",symlist[i].name);
		scanf("%s",symlist[i].type);	
	}
	return symlist;
}

//INPUT QUERY LIST
struct symbol* readQueries(int *n){
	scanf("%d",n);
	struct symbol* querlist = (struct symbol*)malloc((*n)*sizeof(struct symbol));
	int i;
	for(i = 0;i<(*n);i++){
		querlist[i].name  = (char*)malloc(8*sizeof(char));
		querlist[i].type  = (char*)malloc(10*sizeof(char));
		scanf("%s",querlist[i].name);
		scanf("%s",querlist[i].type);
	}
	return querlist;
}

//HASHING FUNCTION
int hashingFunction(char* key, int size){
	long x = pow(2,16);
	long total = 0;
	int i;
	for(i=0;i<strlen(key);i++){
		total+=(int)key[i];
	}
	return ((int)(total%x))%size;	
}


//INSERTION INTO THE HASHTABLE FOR ONE SYMBOL
void insert(struct Hashtable* hashtable, struct symbol* s){
	hashtable->entries++;
	int index = hashingFunction(s->name,hashtable->size);
	if(isSlotEmpty(hashtable,index))
		hashtable->freeSlots--;
			
	int t = insertSymbol(hashtable,index,s);	
	hashtable->insertionTime+=t;
	hashtable->loadfactor = (float)hashtable->entries/hashtable->size;
}

//ASSISTANT FUNCTION FOR INSERT
int isSlotEmpty(struct Hashtable* hashtable, int index){
	if(hashtable->table[index]->head==NULL)
		return 1;
	else
		return 0;
}

//ASSISTANT FUNCTION FOR INSERT
int insertSymbol(struct Hashtable* hashtable, int index, struct symbol* sym){
	int time = 0;
	NODE n = (NODE)malloc(1*sizeof(struct node));
	n->next = NULL; 
	n->s = sym;
	
	//INSERTION INTO LINKED LIST FUNCTION
	NODE temp = hashtable->table[index]->head;
	if(temp == NULL){
		hashtable->table[index]->head = n;
	}
	else{
		time = 1;
		while(temp->next!=NULL){
			temp = temp->next;			
			time++;			
		}
		temp->next = n;
	}
		
	//INCREMENTING COUNT FOR THIS PARTICULAR LINKED LIST
	hashtable->table[index]->count++;
	return time;
}


//CREATE HASHTABLE
struct Hashtable* createHashTable(struct Hashtable* hashtable, int size, double minLoad, double maxLoad, int resizeFactor, struct symbol* s, int n){
	hashtable = createEmptyHashTable(size);
	struct Hashtable* hnew;
	int i,j;
	int newSize;
	for(i=0;i<n;i++){
		insert(hashtable,&s[i]);
		if(hashtable->loadfactor > maxLoad){
			newSize = hashtable->size*resizeFactor;
			hnew = createEmptyHashTable(newSize);
			hnew-> insertionTime = hashtable->insertionTime;
			for(j=0;j<=i;j++){
				insert(hnew,&s[j]);
			}
			//delete(hashtable);
			hashtable = hnew;
		}
	}
		
	if(hashtable->loadfactor < minLoad){
		newSize = hashtable->size/resizeFactor;
		hnew = createEmptyHashTable(newSize);
		hnew-> insertionTime = hashtable->insertionTime;
		for(i=0;i<n;i++){
			insert(hnew,&s[i]);
		}
		//delete(hashtable);
		hashtable = hnew;
	}
	PrintTabSeparated(hashtable->entries,hashtable->size,hashtable->loadfactor,hashtable->freeSlots,hashtable->insertionTime);
	return hashtable;
}


//CREATING AN EMPTY HASHTABLE
struct Hashtable* createEmptyHashTable(int size){
	struct Hashtable* hashtable = (struct Hashtable*)malloc(1*sizeof(struct Hashtable));
	hashtable->entries=0;
	hashtable->size = hashtable->freeSlots = size;
	hashtable->insertionTime = 0;
	hashtable->queryingTime = 0;
	hashtable->table = (list*)malloc(size*sizeof(list));
	int i;
	for(i=0;i<size;i++){
			hashtable->table[i] = (list)malloc(1*sizeof(struct linkedlist));
			hashtable->table[i]->head=NULL;
			hashtable->table[i]->count=0;
	}
	return hashtable;
}

//PRINTING OUTPUT TAB SEPARATED
void PrintTabSeparated(int a, int b, double c, int d, int e){
	printf("%d\t%d\t%lf\t%d\t%d\n",a,b,c,d,e);
}


//LOOKUP QUERIES
void lookupQueries(struct Hashtable* hashtable, struct symbol* q, int n){
	int i;
	int time = 0;
	for(i=0;i<n;i++){
		hashtable->queryingTime += lookup(hashtable,&q[i]);
	}
	printf("%d\t%d\n",n,hashtable->queryingTime);
}

//ASSISTANT FUNCTION FOR LOOKUP QUERIES
int lookup(struct Hashtable* hashtable, struct symbol* q){
	int time = 0;
	int index = hashingFunction(q->name,hashtable->size);
	NODE temp = hashtable->table[index]->head;
	while(temp!=NULL){	
		time++;	
		if(strcmp(temp->s->name,q->name)==0&&strcmp(temp->s->type,q->type)==0){
			break;
		}
			
		temp = temp->next;				
	}
	return time;
}


