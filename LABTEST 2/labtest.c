#include"labtest.h"

int main(){
	char** strings;
	char** strings_copy;
	int x,d,i,n,w;
	scanf("%d",&x);
	while(1){
		if(x==-1)
			break;
		
		else if(x==1){
			scanf("%d",&n);
			scanf("%d",&w);
			strings = readStrings(n,w);			
		}
		
		else if(x==2){
			scanf("%d",&d); 
			
			// Making a copy
			strings_copy = (char**)malloc(n*sizeof(char*));
			for(i=0;i<n;i++){
				strings_copy[i] = (char*)malloc(w*sizeof(char));
				strcpy(strings_copy[i],strings[i]);
			}
			keyindex(strings_copy,0,n-1,d);
			print_characters(strings_copy,0,n-1,d);
		}
		
		else if(x==3){
			lsdRadixSort(strings,0,n-1);
			print_strings(strings, 0,n-1);
		}
		
		scanf("%d",&x);
	}
	return 0;
}

//Prining the Dth characters of the strings
void print_characters(char** strings, int low, int high, int d){
	int i;
	for(i=low;i<=high;i++){
		printf("%c\n",strings[i][d]);
	}
}

//Printing all the strings
void print_strings(char** strings, int low, int high){
	int i;
	for(i=low;i<=high;i++){
		printf("%s\n",strings[i]);
	}
}

// reading strings and returning to the driver function
char** readStrings(int n, int w){
	int i;
 	char** strings;
	strings = (char**)malloc(n*sizeof(char*));
	for(i=0;i<n;i++){
		strings[i] = (char*)malloc(w*sizeof(char));
		scanf("%s",strings[i]);
	}
	
	return strings;
}

// Radix sort on all the strings
void lsdRadixSort(char** strings, int low, int high){
	int n = high-low+1;
	int w = strlen(strings[0]);
	int i;
	for(i=w-1;i>=0;i--){
		keyindex(strings,0,n-1,i);
	}	
}

// Key Index
void keyindex(char** strings, int low, int high, int d){
	int i;
	int count[26];
	int n = high-low+1;
	int w = strlen(strings[0]);
	char** output;
	output = (char**)malloc(n*sizeof(char*));
	for(i=0;i<n;i++){
		output[i] = (char*)malloc(w*sizeof(char));
	}
	
	//Initializing Character Frequencies to 0
	for(i=0;i<26;i++){
		count[i]=0;
	}
	//Character Frequencies
	for(i=low;i<=high;i++){
		count[strings[i][d]-97]++;	
	}
	//Cumulative Character Frequencies
	for(i=1;i<26;i++){
		count[i] += count[i-1];
	}
	// Temporary array 
	for(i=high;i>=low;i--){
		strcpy(output[count[strings[i][d]-97]-1],strings[i]);
		count[strings[i][d]-97]--;
	}
	//Store sorted strings on the basis of dth character as a key
	int z=0;
	for(i=low;i<=high;i++){
		strcpy(strings[i],output[z++]);
	}
}






