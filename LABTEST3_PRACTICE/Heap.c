#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

struct heap{
	int* harr;
	int size;
	int capacity;
};
typedef struct heap* Heap;

//Creates an empty heap
Heap createHeap(int capacity){
	Heap h = (Heap)malloc(1*sizeof(struct heap));
	h->harr = (int *)malloc(capacity*sizeof(int));
	h->capacity = capacity;
	h->size = 0;
	return h;
}

//Returns the left child of an element
int get_left(Heap h, int i){
	return 2*i+1;
}

//Returns the right child of an element
int get_right(Heap h, int i){
	return 2*i+2;
}

//Returns the parent of an element
int get_parent(Heap h, int i){
	return (int)(i-1)/2;
}

//Adds an alement to the heap
void add(Heap h, int element){

	if(h->size==h->capacity){
		printf("Heap is already fully\n");
		return;
	}
	
	h->size++;
	h->harr[h->size-1] = element; //Adds an element at the end
	
	int i = h->size-1;
	
	//Maintaining the heap property
	while(i!=0 && h->harr[i] < h->harr[get_parent(h,i)]){
		int temp = h->harr[i];
		h->harr[i] = h->harr[get_parent(h,i)];
		h->harr[get_parent(h,i)] = temp;
		
		i = get_parent(h,i); 
	}
}

//Returns the minimum value from a heap
int get_min(Heap h){
	if(h->size==0){
		return INT_MIN;
	}
	return h->harr[0];
}


//Top Down Hepify
void min_heapify(Heap h, int i){
	int l = get_left(h,i);
	int r = get_right(h,i);
	int smallest = i;
	
	//Picking the smallest out of the three
	if(l<h->size && h->harr[smallest] > h->harr[l]){
		smallest = l;
	}
	if(r<h->size && h->harr[smallest] > h->harr[r]){
		smallest = r;
	}
	
	if(smallest!=i){
		int temp = h->harr[smallest];
		h->harr[smallest] = h->harr[i];
		h->harr[i] = temp;
		
		min_heapify(h,smallest);
	}	
}

//Returns as well as removes the minimum element from the heap
int extract_min(Heap h){
	int size = h->size;
	if(size==0){
		return INT_MIN;
	}
	
	int min = h->harr[0];
	
	h->harr[0] = h->harr[size-1]; //Size can also be 1
	h->size--;
	
	if(h->size!=0) 
		min_heapify(h,0);
	
	//Now removing the minimum value
	
	return min;
}

//Function to reduce the value of a key and bringing to the top of the heap
void decrease_key(Heap h, int i, int value){
	h->harr[i] = value;
	
	//Bringing the reduced key to the top of the heap
	while(i!=0 && h->harr[i] < h->harr[get_parent(h,i)]){
		int temp = h->harr[i];
		h->harr[i] = h->harr[get_parent(h,i)];
		h->harr[get_parent(h,i)] = temp;
		
		i = get_parent(h,i); 
	}
	
}

//To delete a key, we first reduces to INT_MIN, brings it to the top of the heap and then performs extact_min()
int delete_key(Heap h, int i){
	if(i>=h->size){
		printf("Index Out of Bounds\n");
		return INT_MIN;
	}
	
	int value = h->harr[i];
	
	decrease_key(h,i,INT_MIN);
	extract_min(h);
	
	return value;	
} 

//Returns the index of an element so that we can delete it further
int get_index(Heap h, int i, int key){	
	if(i>=h->size){
		return -1;
	}
	
	if(h->harr[i] == key)
		return i;
	
	int l = get_index(h,get_left(h,i),key);
	if(l!= -1)
		return l;
	
	int r = get_index(h, get_right(h,i),key);
	if(r!=-1)
		return r;
		
	return -1;
}


//Test the heap
int main(){
	Heap h = createHeap(10);
	int i; 
	for(i=0;i<10;i++){
		add(h,10-i);
	}
	
	for(i=0;i<10;i++){
		printf("%d ",extract_min(h));
	}
	return 0;
}


