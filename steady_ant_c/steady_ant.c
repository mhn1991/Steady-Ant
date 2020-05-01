#include<stdio.h>
#include<stdlib.h>

#include "linkedlist.h"


typedef struct matrixCell{
  int isBlue;
  // value could be byte for permutation matrix
  int value;
}Cell;


typedef struct permutationMatrix{
  // we will need it for steady ant algorithm
  int isBlue;
  int *matrix;
  int size;
}Matrix;

void makeMatrix(){
  
}


void printArr(int *a,int n) 
{ 
  for (int i=0; i<n; i++){ 
      printf("%d ",a[i]);
  }
    printf("\n"); 
} 
  
// Generating permutation using Heap Algorithm 
void heapPermutation(int *a, int size, int n,list *l) 
{
  if (size == 1) 
    {
      append(l,a); 
      return; 
    } 
    
  for (int i=0; i<size; i++) 
    { 
      heapPermutation(a,size-1,n,l); 
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
  int *a = calloc(3,sizeof(int));
  for(int i=1;i<3;i++){
    a[i] = i;
  }
  list l;
  init(&l);
  heapPermutation(a, 3, 3,&l);
  printArr(l.head->data,3);
  printf("\n%d\n",l.size);
  return 0; 
} 
