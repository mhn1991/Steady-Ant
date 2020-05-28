#include<stdio.h>
#include<stdlib.h>


#define White 0 
#define Red 1
#define Blue 2
#define Green 3
//#define White 0

typedef struct flag{
  unsigned int val:2;
}Flag;

// 0 means red
// 1 means blue
// 2 means green

typedef struct cell{
  int sc;
  unsigned int isBlue:2;
}Cell;

typedef struct sparse{
  Cell *fc;
  int size;
}Sparse;

typedef struct ant{
  int i;
  int j;
  int blue;
  int red;
}Ant;

// O(n)
void check(Sparse *r,Ant *a){
  int i = a->i;
  int j = a->j;
  int size = r->size;
  //printf("##############CHECK##################\n");
  //printf("i:%d j:%d size:%d\n",i,j,size);
  for(int k = 0 ; k < size; k++){
    // check we are not out of array for red
    if((i + k + 1) < r->size){
      //printf("i:%d k:%d color:%d\n",(i+k+1),k,r->fc[i+k+1].isBlue);
      if( r->fc[i+k+1].isBlue == Red && r->fc[i+k+1].sc >= j){
	a->red +=1;
      }
    }
    
    if((i-k) >= 0){
      if( r->fc[i-k].isBlue == Blue && r->fc[i-k].sc < j){
	a->blue +=1;
      }
    }
  }
  //printf("##############CHECK END##################\n");
}

void setMemory(int *array,int size){
  for(int i=0;i< size;i++){
    array[i] = -1;
  }
}

void ant(Sparse *r){
  printf("############################################################\n");
  Flag flag = {0};
  Ant a = {r->size-1,0,0,0};
  int *changed = malloc(r->size  * sizeof(int));
  setMemory(changed,r->size);
  // r-> size + h - l
  for(int i=0; i < 2 * r->size -1; i++ ){
    // check up 
    a.i -= 1;
    a.red = 0;
    a.blue= 0;
    check(r,&a);
    printf("i:%d j:%d red:%d blue:%d\n",a.i,a.j,a.red,a.blue);
    if(a.red != a.blue){
      flag.val = 1;
      a.i += 1;
    }
    else{
      continue;
    }
    // check right 
    a.j += 1;
    a.red = 0;
    a.blue= 0;
    check(r,&a);
    printf("i:%d j:%d red:%d blue:%d\n",a.i,a.j,a.red,a.blue);
    if(a.red != a.blue){
      a.j -=1;
    }
    else{
      continue;
    }
    changed[a.i] = a.j;
    a.i -= 1;
    a.j += 1;
    i +=2;
    //printf("%d\n",a.i+1);
      //}
    // check we are not on the border of the array
    if(a.i-1 < 0 && a.j+1 == (r->size)){
      break;
    }
    // reset the flag 
    flag.val = 0;
  }

  // cleaning R matrice
  for(int i=0; i < r->size;i++){
    //ag flag = {0};
    if (changed[i] != -1){
      // moving the bad non-zeros to their place marked by ant
      r->fc[i].sc = changed[i];
      r->fc[i].isBlue = Green;
      flag.val = 1;
      continue;
      // set all the colors to White
    }
    
    if (r->fc[i].isBlue != White){
      r->fc[i].isBlue = Green;
    }
    
    //r->fc[i].isBlue = White;
  }
}

void coloring(Sparse *p, Sparse *q,int i,int color){
    p->fc[i].isBlue = color;
    q->fc[i].isBlue = color;
}

void rColoring(Sparse *r,int color){
  // should optimize we move too much for safety
  for(int i= 0 ; i< r->size ;i++){
    if (r->fc[i].isBlue == Green){
      r->fc[i].isBlue = color;
    }
  }
}

void permute(Sparse *p, Sparse *q,Sparse *r,int l,int h){
  for(int i=l; i<=h;i++){
    r->fc[p->fc[i].sc] = q->fc[i];
  }
}

void printR(Sparse *r){
  printf("**********************************\n");                                                                                                                                
  for(int i=0; i< r->size;i++){                                                                                                                                                  
    printf("i:%d j:%d color:%d\n",i,r->fc[i].sc,r->fc[i].isBlue);                                                                                                                
  }                                                                                                                                                                              
  printf("**********************************\n");                                   
}

void multi(Sparse *p,Sparse *q,Sparse *r,int l,int h){
  // 2 columns
  if(h - l == 1){
    printf("2 columns branch\n");
    coloring(p,q,l,Red);
    coloring(p,q,h,Blue);
    permute(p,q,r,l,h);
    printR(r);
    ant(r);
    printR(r);
    return;
  }
  // 3 columns
  if(h - l == 2){
    //printf("3 column branch \n");
    multi(p,q,r,l,h-1);
    printf("3 column branch \n");
    rColoring(r,Red);
    coloring(p,q,h,Blue);
    permute(p,q,r,h,h);
    
    printR(r);
    ant(r);
    printR(r);
    return;
  }
  int m = (l + h)/2;
  multi(p,q,r,l,m);
  //printR(r);
  //return;
  multi(p,q,r,m+1,h);
  //printR(r);
  //return;
  rColoring(r,Red);
  rColoring(r,Blue);
  printR(r);
  ant(r);
  printR(r);
}


void testMulti2(){
  Cell f = {1,White};
  Cell s = {0,White};
  Cell * i = calloc(2,sizeof(Cell));
  i[0] = f;
  i[1] = s;
  Sparse p = {i,2};
  Cell ff = {0,White};
  Cell ss = {1,White};
  Cell * j = calloc(2,sizeof(Cell));
  j[0] = ff;
  j[1] = ss;
  Sparse q = {j,2};
  Cell *k = calloc(2,sizeof(Cell));
  Sparse r = {k,2};
  multi(&p,&q,&r,0,1);
  /*
  printf("**********************************\n");                                                                                                                                  
    for(int i=1; i< r.size;i++){                                                                                                                                                    
      printf("i:%d j:%d color:%d\n",i-1,r.fc[i].sc,r.fc[i].isBlue);                                                                                                                
    }                                                                                                                                                                                
    printf("**********************************\n");
  */
}

void testMulti3(){
  Cell first  = {0,White};                
  Cell second = {2,White};              
  Cell third  = {1,White};              
  Cell * i = calloc(3,sizeof(Cell));
  i[0] = first;
  i[1] = second;
  i[2] = third;
  Sparse p = {i,3};
  Cell f = {2,White};
  Cell s = {0,White};
  Cell t = {1,White};
  Cell *j = calloc(3,sizeof(Cell));
  j[0] = f;
  j[1] = s;
  j[2] = t;
  Sparse q = {j,3};
  Cell *k = calloc(3,sizeof(Cell));
  Sparse r = {k,3};
  multi(&p,&q,&r,0,2);
}

void testMulti5(){
  Cell first  = {0,White};          
  Cell second = {3,White};          
  Cell third  = {1,White};
  Cell forth  = {4,White};
  Cell fifth  = {2,White};
  Cell * i = calloc(5,sizeof(Cell));
  i[0] = first;                    
  i[1] = second;                   
  i[2] = third;
  i[3] = forth;
  i[4] = fifth;
  Sparse p = {i,5};                
  Cell f = {1,White};              
  Cell s = {2,White};              
  Cell t = {0,White};
  Cell ff= {4,White};
  Cell ft= {3,White};
  Cell *j = calloc(5,sizeof(Cell));
  j[0] = f;                        
  j[1] = s;                        
  j[2] = t;
  j[3] = ff;
  j[4] = ft;
  Sparse q = {j,5};                
  Cell *k = calloc(5,sizeof(Cell));
  Sparse r = {k,5};    
  multi(&p,&q,&r,0,4);
  /*
  for(int i=1;i<6;i++){
    printf("i:%d j:%d color:%d\n",i-1,r.fc[i].sc,r.fc[i].isBlue);
  } 
  */                              
}


void testAnt2(){
  Cell first  = {1,1};                                                                                                                                                              
  Cell second = {0,0}; 
  Cell * i = calloc(3,sizeof(Cell));                                                                                                                                               
  Sparse r;                                                                                                                                                                        
  r.size = 3;                                                                                                                                                                       
  i[1] = first;                                                                                                                                                                       i[2] = second;                                                                                                                                                                    
  r.fc = i;  
  ant(&r);                                                                                                                                                                         
  //printf("Red: %d\nBlue:%d\n",a.red,a.blue);   
}

void testCheck(){
  Cell first  = {1,1};
  Cell second = {0,1};
  Cell third  = {2,0};
  Cell * i = calloc(4,sizeof(Cell));
  
  Sparse r;
  r.size = 4;
  i[1] = first; 
  i[2] = second;
  i[3] = third;
  r.fc = i;
  Ant a = {0,2,0,0};
  //check(&r,&a);
  ant(&r);
  //printf("Red: %d\nBlue:%d\n",a.red,a.blue);
}


void main(void){
  //testCheck();
  //testMulti3();
  testMulti2();
  //testMulti5();
  //testAnt2();
}
