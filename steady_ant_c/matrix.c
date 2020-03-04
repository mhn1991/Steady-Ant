#include<stdio.h>
#include<stdlib.h>

//#include "linkedlist.h"

void printArr(int a[],int n) 
{ 
    for (int i=0; i<n; i++) 
      printf("%d ",a[i]); 
    printf("\n"); 
} 
  
// Generating permutation using Heap Algorithm 
void heapPermutation(int a[], int size, int n) 
{
    if (size == 1) 
    {
      
      //printf("%d",j);
        printArr(a, n); 
        return; 
    } 
  
    for (int i=0; i<size; i++) 
    { 
      heapPermutation(a,size-1,n); 
        if (size%2==1){
	  int tmp = a[0];
	  a[0] = a[size-1];
	  a[size-1] = tmp;
	} 
        else{
	  int tmp = a[i];
	  a[i] = a[size-1];
	  a[size-1] = tmp;
	}
    } 
} 
   
int main() 
{
    int a[] = {1, 2, 3}; 
    int n = sizeof a/sizeof a[0];
    //list l;
    //init(&l);
    heapPermutation(a, n, n);
    //printf("\n%d\n",list->size);
    return 0; 
} 
