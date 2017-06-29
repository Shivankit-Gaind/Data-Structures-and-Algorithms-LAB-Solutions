#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>


struct node{
	struct word_of_chars* word;
	struct node* next;
};

struct linkedlist {
	int count;
	struct node* first;
};



struct word_of_chars{
	int count;
	struct charnode* firstchar;

};

struct charnode{
	char x;
	struct charnode* next;
};


void insert_words(char **arr , struct linkedlist *head,int n);
void insert_word_first(struct linkedlist *head, char* w);
void insert_char_first(struct word_of_chars* head, char character);
void print_word_list(struct linkedlist *head);
void print_word(struct word_of_chars* head);
void print_K_word(struct linkedlist *head, int k);
void sort_K_word(struct linkedlist *head, int k);
void sort_char_list(struct charnode* temp, int count);
void sort_all_words(struct linkedlist *head);
void sort_word_list(struct node* temp, int count);
void lexico_graphical_order(struct linkedlist *head);
int compare(struct word_of_chars* word1, struct word_of_chars* word2);


int main(){
	struct linkedlist* head = (struct linkedlist*)malloc(1*sizeof(struct linkedlist));
	head->count =0;
	head->first = NULL;
	
	int x,k,n;
	scanf("%d",&x);
		
	while(1){
		if(x==-1)
			break;
		else if(x==1){
			scanf("%d",&n);
			char** a = (char**)malloc(n*sizeof(char*));
			int i;
			for(i=0;i<n;i++){
				a[i] = (char*)malloc(21*sizeof(char));
				scanf("%s",a[i]);
			}
			insert_words(a,head,n);			
		}
		
		else if(x==2){
			scanf("%d",&k);
			print_K_word(head,k);
		}
		else if(x==3){
			print_word_list(head);
		}
		
		else if(x==4){
			scanf("%d",&k);
			sort_K_word(head,k);			
		}
		else if(x==5){
			sort_all_words(head);
			print_word_list(head);     
		}
		else if(x==6){
			lexico_graphical_order(head);
		}
		scanf("%d",&x);	
	}

	return 0;
}



// ALL THE FUNCTIONS FOR CREATING THE LIST

void insert_words(char **arr , struct linkedlist *head,int n){
	struct node* ptr = head->first;
	int i;
	for(i=n-1;i>=0;i--){
		insert_word_first(head,arr[i]);		
	}	
}

void insert_word_first(struct linkedlist *head, char* w){
		struct node* temp = (struct node*)malloc(1*sizeof(struct node));
		
		temp->word = (struct word_of_chars*)malloc(1*sizeof(struct word_of_chars));
		temp->word->firstchar = NULL;
		temp->word->count = 0;
		int j;
		for(j = strlen(w)-1; j>=0;j--){			
			insert_char_first(temp->word,w[j]);
		}		
		
		temp->next = head->first;
		head->first = temp;
		head->count++;	
	
}

void insert_char_first(struct word_of_chars* head, char character){
	struct charnode* ch = (struct charnode* )malloc(1*sizeof(struct charnode));	
	ch->x = character;
	ch -> next = head->firstchar;
	head->firstchar  = ch;
	head -> count ++;
}





// printing all words
void print_word_list(struct linkedlist *head){
	struct node *temp = head->first;
   	while(temp!=NULL){
	   	print_word(temp->word);
	   	printf("\n");
	   	temp = temp->next;
	}      

}

//PRINTING ONE WORD
void print_word(struct word_of_chars* head){
	struct charnode* temp = head->firstchar;
	while(temp!=NULL){
		printf("%c\t",temp->x);
		temp = temp->next;
	}
}

//PRINTING KTH WORD
void print_K_word(struct linkedlist *head, int k){
	struct node *temp = head->first;
	int count = 1;
	while(temp!=NULL){
		if(count==k){
			print_word(temp->word);
			printf("\n");
			break;
		}
		count++;
		temp = temp->next;
	}
}


// SORT KTH WORD
void sort_K_word(struct linkedlist *head, int k){
	struct node *temp = head->first;
	int count = 1;
	while(temp!=NULL){
		if(count==k){
			sort_char_list(temp->word->firstchar,temp->word->count);
			print_word(temp->word);
			printf("\n");
			break;
		}
		count++;
		temp = temp->next;
	}
}


//SORT ONE WORD
void sort_char_list(struct charnode* temp, int count){
	if(temp->next==NULL){
		return;
	}	
	sort_char_list(temp->next,count--);	
	
	// insert_in_sorted_order
	char ele = temp->x;
	struct charnode* pretemp = temp;
	temp = temp->next;
	while(temp!=NULL){
		if(temp->x > ele){
			break;
		}		
		pretemp->x = temp->x;
		temp = temp->next;
		pretemp = pretemp->next;
	
	}
	pretemp->x = ele;
}

// SORT ALL WORDS
void sort_all_words(struct linkedlist *head){
	struct node *temp = head->first;
   	while(temp!=NULL){
	   	sort_char_list(temp->word->firstchar,temp->word->count);	   	
	   	temp = temp->next;
	}
}

// SORT ALL WORDS IN LEXICOGRAPHICAL ORDER
void lexico_graphical_order(struct linkedlist *head){
	sort_word_list(head->first,head->count);
	print_word_list(head);  	
}

//ASSISTANT FUNCTION FOR  LEXICOGRAPHICALLY SORTING WORDS
void sort_word_list(struct node* temp, int count){
	if(temp->next==NULL){
		return;
	}	
	
	sort_word_list(temp->next,count--);
	
	struct word_of_chars* wordtemp = temp->word;
	
	struct node* pretemp = temp;
	temp = temp->next;
	
	while(temp!=NULL){
		if(compare(temp->word,wordtemp)==1){
			break;
		}
		pretemp->word = temp->word;
		temp = temp->next;
		pretemp = pretemp->next;
	} 
	pretemp->word = wordtemp;
}



// COMPARING 2 WORDS
int compare(struct word_of_chars* word1, struct word_of_chars* word2){
	struct charnode* temp1 = word1->firstchar;
	struct charnode* temp2 = word2->firstchar;
	
	while(1){
		if(temp1==NULL && temp2 == NULL)
			return 0;
		else if(temp1 == NULL){
			return -1;
		}
		else if(temp2 == NULL){
			return 1;
		}
	
		else if(temp1->x > temp2-> x){
			return 1;
		}
	
		else if(temp1->x < temp2-> x){
			return -1;
		}
		else{
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
	}
}












