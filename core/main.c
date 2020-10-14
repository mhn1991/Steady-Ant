#include<stdio.h>
#include<stdlib.h>
#include"core.h"

// get a String return it's size
int getStringSize(char *string){
  int size = 0;
  while(*string != '\0'){
    size+=1;
    string++;
  }
  return size;
}

int getIndex(int i,int j,int n){
  return i*n+j;
}

void printModel(Cell *array,int ss1,int ss2){
  for(int i=0; i<ss2;i++){
    for(int j=0; j< ss1;j++){
      printf("%d",array[getIndex(i,j,ss1)].type);
    }
    printf("\n");
  }
}

void makeBraidGroup(Cell *array,char *s1,char *s2,int ss1,int ss2){
  for(int i=0; i < ss2;i++){
    for(int j=0; j< ss1; j++){
      if(s2[i] == s1[j]){
	array[getIndex(i,j,ss1)].type = 1;
      }
      else{
	array[getIndex(i,j,ss1)].type = 0;
      }
    }
  }
}

int calcLength(Cell *array,int i,int j,int ss1,int ss2){
  int flag=0;
  int length =0;
  int ax=j;
  int l = j;
  //printf("i=%d j=%d l=%d\n",i,j,l);
  for(int k=i; k<ss2;k++){
    if(flag){
      //printf("slm");
      flag =0;
      l=ax;
    }
    //printf("k=%d l=%d ss1=%d\n",k,l,ss1);
    //printf("####################\n");
    while(l<ss1){
      //printf("while k=%d l=%d type=%d\n",k,l,array[getIndex(k,l,ss1)].type);
      if(array[getIndex(k,l,ss1)].type == 1){
	//printf("k=%d l=%d\n",k,l);
	length+=1;
	ax=l;
	break;
      }
      l++;
      flag=1;
    }
    //printf("####################\n");
  }
  return length;
}


int LCS(Cell *array,int ss1,int ss2){
  int LCS = 0;
  for(int i=0; i< ss2; i++){
    for(int j=0; j< ss1; j++){
      if(array[getIndex(i,j,ss1)].type == 1 ){
	int length = calcLength(array,i,j,ss1,ss2);
	printf("length=%d\n",length);
	LCS = (LCS < length) ? length : LCS; 
      }
    }
  }
  return LCS;
}

int main(int argc,char *argv[]){
  if(argc != 3){
    printf("./<name of the programe> string1 string2");
    exit(0);
  }

  char *s1 = argv[1];
  char *s2 = argv[2];
  int ss1 = getStringSize(argv[1]);
  int ss2 = getStringSize(argv[2]);
  printf("%d\n",ss1);
  Cell *Model = calloc(ss1*ss2,sizeof(Cell));
  makeBraidGroup(Model,s1,s2,ss1,ss2);
  printModel(Model,ss1,ss2);
  printf("%d\n",LCS(Model,ss1,ss2));
  //printModel(Model,ss1,ss2);
}
