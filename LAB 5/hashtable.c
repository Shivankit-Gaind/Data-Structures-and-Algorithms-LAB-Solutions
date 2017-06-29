#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


struct symbol{
	char* name;
	long int id;
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
	int option;
};

struct symbol* readSymbols(int* n);
struct symbol* readQueries(int* n);
int hashingFunction(char* key, long int id, int size, int option);
void insert(struct Hashtable* hashtable, struct symbol* s, int option);
int isSlotEmpty(struct Hashtable* hashtable, int index);
int insertSymbol(struct Hashtable* hashtable, int index, struct symbol* sym);
struct Hashtable* createHashTable(struct Hashtable* hashtable, int size,struct symbol* s, int n,int option);
struct Hashtable* createEmptyHashTable(int size);
void lookupQueries(struct Hashtable* hashtable, struct symbol* q, int n,int option);
int lookup(struct Hashtable* hashtable, struct symbol* q,int option);
void printINScomplex(struct Hashtable** hashtable);
void printQUERcomplex(struct Hashtable** hashtable);

int main(){
	int x;
	struct symbol* symbollist; int s;
	struct symbol* querylist; int q;
	struct Hashtable** hashtable = (struct Hashtable**)malloc(sizeof(struct Hashtable*));
	int i;
	scanf("%d",&x);
	while(1){
		if(x==-1)
			break;
			
		else if(x==1){
			symbollist = readSymbols(&s);
			int size;				
			//different sizes......redundancy is there...will remove later
			for(i=0;i<2;i++){
				hashtable[i] = createHashTable(hashtable[i],20,symbollist,s,i+1);
			}
			for(i=2;i<4;i++){
				hashtable[i] = createHashTable(hashtable[i],200,symbollist,s,i+1);
			}
			for(i=4;i<6;i++){
				hashtable[i] = createHashTable(hashtable[i],20,symbollist,s,i+1);
			}
			for(i=6;i<8;i++){
				hashtable[i] = createHashTable(hashtable[i],200,symbollist,s,i+1);
			}	
		}
		
		else if(x==2){
			querylist = readQueries(&q);
			for(i=0;i<8;i++){
				lookupQueries(hashtable[i], querylist,q,i+1);
			}
		}
		
		else if(x==3){
				printINScomplex(hashtable);	
		}
		
		else if(x==4){
				printQUERcomplex(hashtable);
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
		scanf("%s",symlist[i].name);
		scanf("%ld",&symlist[i].id);	
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
		scanf("%s",querlist[i].name);
		scanf("%ld",&querlist[i].id);
	}
	return querlist;
}

//HASHING FUNCTION
int hashingFunction(char* name, long int id, int size,int option){
	int total = 0;
	int i;
	for(i=0;i<strlen(name);i++){
		total = total+name[i];
	}
	int x = 89;
	int y = 105943;
	switch(option){
		case 1:
			return (((total%x))%size);
			break;
		case 2:
			return (((total%y))%size);
			break;
		case 3:
			return (((total%x))%size);
			break;
		case 4:
			return (((total%y))%size);
			break;
		case 5:
			return (((id%x))%size);
			break;
		case 6:
			return (((id%y))%size);
			break;
		case 7:
			return (((id%x))%size);
			break;
		case 8:
			return (((id%y))%size);	
			break;		
	}
}


//INSERTION INTO THE HASHTABLE FOR ONE SYMBOL
void insert(struct Hashtable* hashtable, struct symbol* s,int option){
	hashtable->entries++;
	int index = hashingFunction(s->name,s->id, hashtable->size,option);
	if(isSlotEmpty(hashtable,index))
		hashtable->freeSlots--;
			
	int t = insertSymbol(hashtable,index,s);	
	hashtable->insertionTime+=t;
	hashtable->loadfactor = (double)hashtable->entries/hashtable->size;
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
struct Hashtable* createHashTable(struct Hashtable* hashtable, int size, struct symbol* s, int n,int option){
	hashtable = createEmptyHashTable(size);
	hashtable->option = option;
	int i;
	for(i=0;i<n;i++){
		insert(hashtable,&s[i],option);
	}	
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

//LOOKUP QUERIES
void lookupQueries(struct Hashtable* hashtable, struct symbol* q, int n,int option){
	int i;
	int time = 0;
	for(i=0;i<n;i++){
		time += lookup(hashtable,&q[i],option);
	}
	hashtable->queryingTime = time;
}

//ASSISTANT FUNCTION FOR LOOKUP QUERIES
int lookup(struct Hashtable* hashtable, struct symbol* q,int option){
	int time = 0;
	int index = hashingFunction(q->name,q->id,hashtable->size,option);
	NODE temp = hashtable->table[index]->head;
	while(temp!=NULL){
		time++;
		if(strcmp(temp->s->name,q->name)==0 && temp->s->id==q->id)
			break;
		temp = temp->next;
	}
	return time;
}

// Print “Option Number,insertionTime” pair of each table in increasing order of insertionTime of the hash table to finish all insertions.
void printINScomplex(struct Hashtable** hashtable){
	struct Hashtable* temp;
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8-1-i;j++){
			if(hashtable[j]->insertionTime > hashtable[j+1]->insertionTime){
				temp = hashtable[j];
				hashtable[j] = hashtable[j+1];
				hashtable[j+1] = temp;
			}
		}
	}
	for(i=0;i<8;i++){
		printf("%d,%d\t",hashtable[i]->option,hashtable[i]->insertionTime);
	}
	printf("\n");
}



//Print “Option Number, queryTime” pair of each table in increasing order of queryingTime to look up all “queries” in each hash table.
void printQUERcomplex(struct Hashtable** hashtable){
	struct Hashtable* temp;
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8-1-i;j++){
			if(hashtable[j]->queryingTime > hashtable[j+1]->queryingTime){
				temp = hashtable[j];
				hashtable[j] = hashtable[j+1];
				hashtable[j+1] = temp;
			}
		}
	}
	for(i=0;i<8;i++){
		printf("%d,%d\t",hashtable[i]->option,hashtable[i]->queryingTime);
	}
	printf("\n");
}

