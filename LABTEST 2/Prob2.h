#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct index{
	int i;
	int j;
};

void print_strings(char** strings, int low, int high);
char** readStrings(int n, int w);
struct index part3way3keys(char** strings, int low, int high, int d);
void radixPart3waySort(char** strings, int n);
void radixPartitionSort(char** strings, int low, int high, int d);
void swap(char** strings, int low, int high);

