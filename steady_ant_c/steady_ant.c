#include<stdio.h>
#include<stdlib.h>


typedef struct matrixCell{
  int isBlue;
  // value could be byte for permutation matrix
  int value;
}Cell;


// i row
// j column
// n size of the matrix
int getIndex(int i,int j,int n){
  return i*n+j;
}

// print our matrix
void printMatrix(Cell *array,int n){
  Cell *tmp = array;
  for(int i=0;i < n; i++){
    for(int j=0;j < n;j++){
      printf("%d",tmp[getIndex(i,j,n)].value);
    }
    printf("\n");
  }
}

// get permutation matrix and return the dominance matrix
// O(n^4)

Cell * dominanceSum(Cell *array,int n){
  Cell * tmp = array;
  Cell * new = calloc((n+1)*(n+1),sizeof(Cell));
  for(int i=0;i < n;i++){
    for(int j =n-1;j>=0;j--){
      int sum = 0;
      for(int k= i;k < n;k++){
	for(int l= j;l>=0;l--){
	  sum += tmp[getIndex(k,l,n)].value;
	}
      }
      Cell x = {0,sum};
      new[getIndex(i,j+1,n+1)] = x; 
      //printf("%d\n",sum);
    }
  }
  printMatrix(new,n+1);
  return new;
}



void crossDifference(Cell * array,int n){
  Cell * tmp = array;
  Cell * new = calloc((n-1)*(n-1),sizeof(Cell));
  int isBlue = tmp[0].isBlue;
  //int elem = 0;
  for(int i=1;i<n;i++){
    for(int j=1;j<n;j++){
      int value = tmp[getIndex(i-1,j,n)].value - tmp[getIndex(i-1,j-1,n)].value - tmp[getIndex(i,j,n)].value + tmp[getIndex(i,j-1,n)].value;
      Cell cell = {isBlue,value};
      new[getIndex(i-1,j-1,n-1)] = cell;
    }
    //printf("%d\n",elem);
  }
  printMatrix(new,3);
}

int main() 
{
  Cell *red = calloc(3*3, sizeof(Cell));
  Cell redCell = {0,1};
  Cell blueCell = {1,1};
  red[1] = red[3] = red[8] = redCell;
  printMatrix(red,3);
  Cell * tmp = dominanceSum(red,3);
  crossDifference(tmp,4);  
  return 0; 
} 
