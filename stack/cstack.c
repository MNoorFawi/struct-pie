#include <stdio.h>
#include <stdlib.h>
#include "cstack.h"

void create_stack(stack * st) {
  st -> indx = -1; // right index
  st -> size = 0;
  st -> lindx = 0; // left index
  st -> val = (int * ) malloc(sizeof(int) * INIT_SIZE);
}

// check empty
int is_empty(stack * st) {
  if (st -> size == 0)
    return 1;
  else
    return 0;
}

// push/append
void push(stack * st, int new_val) {
  if (st -> size >= INIT_SIZE)
    st -> val = (int * ) realloc(st -> val, sizeof(int) * (st -> size + INIT_SIZE));
  st -> indx++;
  st -> val[st -> indx] = new_val;
  st -> size++;
}

// pop (LIFO)
int pop(stack * st) {
  if (is_empty(st)) {
    puts("\n\t STACK IS EMPTY\n");
    return -1;
  } else {
    int popped = st -> val[st -> indx];
    //printf("Value %i is popped from stack\n", st -> val[st -> indx]);
    st -> indx--; // shift the right index to the left
    st -> size--;
    return popped;
  }
}

// pop left (FIFO)
int popleft(stack * st) {
  if (is_empty(st)) {
    puts("\n\t STACK IS EMPTY\n");
    return -1;
  } else {
    int popped = st -> val[st -> lindx];
    //printf("Value %i is popped from stack\n", st -> val[st -> indx]);
    st -> lindx++; // move the left index to the right
    st -> size--;
    return popped;
  }
}

// print stack
void print_stack(stack * st) {
  int i;
  for (i = st -> lindx; i <= st -> indx; i++) { // loop from left indx to right indx
    printf("%i ", st -> val[i]);
  }
  printf("\n");
}

// length
int len(stack * st) {
  return st -> size;
}

// free memory
void clean(stack * st) {
  free(st -> val);
  free(st);
}