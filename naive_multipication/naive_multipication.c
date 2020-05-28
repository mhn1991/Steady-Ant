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

int min(int a,int b){
  return (a < b) ? a : b;
}


// print our matrix
void printMatrix(Cell *array,int n){
  Cell *tmp = array;
  for(int i=0;i < n; i++){
    for(int j=0;j < n;j++){
      printf("%d\t",tmp[getIndex(i,j,n)].value);
    }
    printf("\n");
  }
  printf("##############################################\n"); 
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

// get dominance matrix and return permutation matrix
// O(n^2)

Cell * crossDifference(Cell * array,int n){
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
 printMatrix(new,n-1);
  return new;
}

// min plus multiplication
// O(n^3)

Cell * minPlusMultiplication(Cell * array1,Cell * array2,int n){
  Cell * new = calloc(n*n , sizeof(Cell));
  Cell * tmp1 = array1;
  Cell * tmp2 = array2;
  for(int i=0;i < n; i++){
    for(int j=0;j<n;j++){
      int m = n*n;
      for(int k=0; k< n;k++){
	m = min(tmp1[getIndex(i,k,n)].value + tmp2[getIndex(k,j,n)].value , m);
      }
      Cell tmp = {0,m};
      new[getIndex(i,j,n)] =  tmp;
    }
  }
  printMatrix(new,n);
  return new;
}


int main() 
{
  //Cell *red= calloc(9,sizeof(Cell));
  Cell *red  = calloc(5*5, sizeof(Cell));
  Cell *blue = calloc(5*5, sizeof(Cell));
  Cell redCell = {0,1};
  Cell blueCell = {1,1};
  // this is the slide 20 example semi_talk.pdf
  //red[getIndex(0,1,6)] = red[getIndex(1,2,6)] = red[getIndex(2,4,6)] = red[getIndex(3,0,6)]= red[getIndex(4,5,6)]=red[getIndex(5,3,6)] = redCell;
  //red[getIndex(0,3,4)] = red[getIndex(1,0,4)] = red[getIndex(2,2,4)] = red[getIndex(3,1,4)] = redCell;
  red[getIndex(0,0,5)] = red[getIndex(1,2,5)] = red[getIndex(2,4,5)] = red[getIndex(3,1,5)] = red[getIndex(4,3,5)] = redCell;
  printMatrix(red,5);
  //printf("##############################################\n");
  //blue[getIndex(0,3,6)] = blue[getIndex(1,0,6)] = blue[getIndex(2,1,6)] = blue[getIndex(3,4,6)] = blue[getIndex(4,5,6)] = blue[getIndex(5,2,6)] = blueCell;
  //blue[getIndex(0,1,4)] = blue[getIndex(1,2,4)] = blue[getIndex(2,0,4)] = blue[getIndex(3,3,4)] = blueCell;
  blue[getIndex(0,1,5)] = blue[getIndex(1,2,5)] = blue[getIndex(2,0,5)] = blue[getIndex(3,4,5)] = blue[getIndex(4,3,5)] = blueCell; 
  printMatrix(blue,5);
  //printf("##############################################\n");
  Cell * dRed = dominanceSum(red,5);
  Cell * dBlue = dominanceSum(blue,5);
  Cell * multi = minPlusMultiplication(dRed,dBlue,6);
  crossDifference(multi,6);
  //crossDifference(minPlusMultipication(dominanceSum(red,6),dominanceSum(blue,6),7),7);
  //red[1] = red[3] = red[8] = redCell;
  //printMatrix(red,3);
  //Cell * tmp = dominanceSum(red,3);
  //crossDifference(tmp,4);  
  return 0; 
} 
