#ifndef CORE_H
#define CORE_H

#define White 0
#define Red 1
#define Blue 2
#define Green 3


typedef struct flag{
  unsigned int val:2;
}Flag;

typedef struct cell{
  int sc;
  unsigned int isBlue:2;
  unsigned int type:1;
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

#endif
