//standard includes
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//own includes
#include "linkedlist.h"


int get(list * l, unsigned int index){
  assert(l != NULL);
  node* current = l->head;

  //iterate over list
  for(unsigned int i = 0; i < index; ++i){
    if(current != NULL){
      current = current->next;
    }else{
      return -1;
    }
  }

  //return element
  if(current != NULL){
    return current->data;
  }else{
    return -1;
  }
}

int prepend(list * l, int data){
  assert(l != NULL);
  //allocate memory
  node* new = (node*)malloc(sizeof(struct node));
  if(new == NULL){
    return -1;
  }
  new->data = data;
  new->next = l->head;

  //prepend element
  l->head = new;
  return 0;
}

int append(list * l, int data){
  assert(l != NULL);
  
  //goto end of list
  node* current = l->head;
  if(current != NULL){
    while(current->next != NULL){
      current = current->next;
    }
  }
  
  //allocate memory
  node* new = (node*)malloc(sizeof(struct node));
  if(new == NULL){
    return -1;
  }
  new->data = data;
  new->next = NULL;

  //append element
  if(current != NULL){
    current->next = new;
  }else{
    l->head = new;
  }
  
  return 0;
}

int remove_element(list * l, unsigned int index){
  assert(l != NULL);
  //checks
  if(l->head == NULL){
    return -1;
  }

  //variables
  node* current = l->head;
  node* previous = NULL;

  //goto element
  for(unsigned int i = 0; i < index; ++i){
    if(current->next != NULL){
      previous = current;
      current = current->next;
    }else{
      return -1;
    }
  }

  //point previous to next element
  if(current == l->head){
    //remove head
    l->head = current->next;
    free(current);
  }else{
    //sanity checks
    assert(previous != NULL);
    assert(current != NULL);
    
    //remove element in the middle
    previous->next = current->next;
    free(current);
  }
  return 0;
}

int insert(list * l, unsigned int index, int data){
  assert(l != NULL);
  //basic case
  if(l->head == NULL && index == 0){
    return prepend(l, data);
  }

  //variables
  node* current = l->head;
  node* previous = NULL;

  //goto element (this time i less EQUAL index!)
  for(unsigned int i = 0; i <= index; ++i){
    if(current != NULL){
      previous = current;
      current = current->next;
    }else{
      return -1;
    }
  }

  //allocate memory
  node* new = (node*)malloc(sizeof(struct node));
  if(new == NULL){
    return -1;
  }
  new->data = data;
  
  //insert element
  assert(previous != NULL);
  previous->next = new;
  new->next = current;
  return 0;
}

void print_list(list * l){
  assert(l != NULL);
  //checks
  if(l->head == NULL){
    printf("empty list\n");
    return;
  }

  //variables
  node* current = l->head;

  //iterate over list and print it
  while(current != NULL){
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

void init(list * l){
  assert(l != NULL);
  l->head = NULL;
}

void destroy(list *l){
  assert(l != NULL);
  node* next = l->head;
  node* toFree;
  while (next != NULL) {
    toFree = next;
    next = next->next;
    free(toFree);
  }
  l->head = NULL;
  return;
}


