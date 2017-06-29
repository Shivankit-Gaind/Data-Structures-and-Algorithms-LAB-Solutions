#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void print_characters(char** strings, int low, int high, int d);
void print_strings(char** strings, int low, int high);
char** readStrings(int n, int w);
void lsdRadixSort(char** strings, int low, int high);
void keyindex(char** strings, int low, int high, int d);

