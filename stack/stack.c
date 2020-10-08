#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

void create_stack(stack * st, int input_type) {
  // switch based on input type
  switch (input_type) {
  case 2:
    // populate enum
    // str is a an array of strings without malloc
    st -> type = STR;
    break;

  case 1:
    st -> type = FLOAT;
    // memory allocation
    st -> val._float = malloc(sizeof(float) * INIT_SIZE);
    break;

  case 0:
    st -> type = INT;
    st -> val._int = (int * ) malloc(sizeof(int) * INIT_SIZE);
    break;

  default:
    puts("\n Invalid Input");
  }
  // generic actions
  st -> indx = -1;
  st -> size = 0;
  st -> lindx = 0;
  //st -> val = (int * ) malloc(sizeof(int) * INIT_SIZE);
}

// check empty
int is_empty(stack * st) {
  if (st -> size == 0)
    return 1;
  else
    return 0;
}

// push/append int
void push_int(stack * st, int new_val) {
  if (st -> size >= INIT_SIZE)
    st -> val._int = (int * ) realloc(st -> val._int, sizeof(int) * (st -> size + INIT_SIZE));
  st -> indx++;
  st -> val._int[st -> indx] = new_val;
  st -> size++;
}

// push/append float
void push_float(stack * st, float new_val) {
  if (st -> size >= INIT_SIZE)
    st -> val._float = realloc(st -> val._float, sizeof(float) * (st -> size + INIT_SIZE));
  st -> indx++;
  st -> val._float[st -> indx] = new_val;
  st -> size++;
}

// push/append char*
void push_str(stack * st, char * new_val) {
  // in case malloc is needed for string allocation
  //int i, new_size;
  //if (st -> size >= INIT_SIZE){
  //  new_size = st -> size + INIT_SIZE;
  //st -> val._str = (char ** ) realloc(st -> val._str, sizeof(char*) * new_size);
  //for (i = INIT_SIZE; i < new_size; i++)
  //			st ->val._str[i] = malloc(100 * sizeof(char));
  //}
  st -> indx++;
  strcpy(st -> val._str[st -> indx], new_val);
  st -> size++;
}

/* poping functions have an unused argument "input"
just to manipulate return type using _Generic macro */

// pop int
int pop_int(stack * st, int input) {
  if (is_empty(st)) {
    puts("STACK IS EMPTY");
    return -1;
  } else {
    int popped = st -> val._int[st -> indx];
    //printf("Value %i is popped from stack\n", st -> val[st -> indx]);
    st -> indx--;
    st -> size--;
    return popped;
  }
}

// pop left int (FIFO)
int popleft_int(stack * st, int input) {
  if (is_empty(st)) {
    puts("STACK IS EMPTY");
    return -1;
  } else {
    int popped = st -> val._int[st -> lindx];
    //printf("Value %i is popped from stack\n", st -> val[st -> indx]);
    st -> lindx++;
    st -> size--;
    return popped;
  }
}

// pop float
float pop_float(stack * st, float input) {
  if (is_empty(st)) {
    puts("STACK IS EMPTY");
    return -1.;
  } else {
    float popped = st -> val._float[st -> indx];
    //printf("Value %i is popped from stack\n", st -> val[st -> indx]);
    st -> indx--;
    st -> size--;
    return popped;
  }
}

// pop left float (FIFO)
float popleft_float(stack * st, float input) {
  if (is_empty(st)) {
    puts("STACK IS EMPTY");
    return -1.;
  } else {
    float popped = st -> val._float[st -> lindx];
    //printf("Value %i is popped from stack\n", st -> val[st -> indx]);
    st -> lindx++;
    st -> size--;
    return popped;
  }
}

// pop char*
char * pop_str(stack * st, char * input) {
  if (is_empty(st)) {
    puts("STACK IS EMPTY");
    return "-1";
  } else {
    char * popped = st -> val._str[st -> indx];
    //printf("Value %i is popped from stack\n", st -> val[st -> indx]);
    st -> indx--;
    st -> size--;
    return popped;
  }
}

// pop left char* (FIFO)
char * popleft_str(stack * st, char * input) {
  if (is_empty(st)) {
    puts("STACK IS EMPTY");
    return "-1";
  } else {
    char * popped = st -> val._str[st -> lindx];
    //printf("Value %i is popped from stack\n", st -> val[st -> indx]);
    st -> lindx++;
    st -> size--;
    return popped;
  }
}

// print stack
void print_stack(stack * st) {
  printf("[");
  int i;
  // switch to print
  switch (st -> type) {
  case INT:
    for (i = st -> lindx; i <= st -> indx; i++) {
      printf("%i ", st -> val._int[i]);
    }
    break;
  case FLOAT:
    for (i = st -> lindx; i <= st -> indx; i++) {
      printf("%.2f ", st -> val._float[i]);
    }
    break;
  case STR:
    for (i = st -> lindx; i <= st -> indx; i++) {
      printf("%s, ", st -> val._str[i]);
    }
    break;
  }
  printf("]\n");
}

// length
int len(stack * st) {
  return st -> size;
}

/* search for values
input value is void pointer to accept any type 
and cast it inside the function properly */
void search(stack * st, int * arr, void * val) {
  //static int arr[INIT_SIZE]; // to be able to return an array
  int i, iter = 0, value;
  // to cast it to relevant types
  float value1;
  char * value2;
  switch (st -> type) {
  case 0:
    value = * (int * ) val; // cast it back to type from void*
    for (i = st -> lindx; i <= st -> indx; ++i) {
      if (st -> val._int[i] == value) {
        arr[iter] = i - st -> lindx;
        iter++;
      }
    }
    break;
  case 1:
    value1 = * (float * ) val;
    for (i = st -> lindx; i <= st -> indx; ++i) {
      if (st -> val._float[i] == value1) {
        arr[iter] = i - st -> lindx;
        iter++;
      }
    }
    break;
  case 2:
    // a void pointer equal already char pointer (both are pointers)
    value2 = val;
    for (i = st -> lindx; i <= st -> indx; ++i) {
      if (strcmp(st -> val._str[i], value2) == 0) {
        arr[iter] = i - st -> lindx;
        iter++;
      }
    }
    break;
  }
  //return arr;
}

// free memory
void clean(stack * st) {
  switch (st -> type) {
  case 0:
    free(st -> val._int);
    break;
  case 1:
    free(st -> val._float);
    break;
  }
  free(st);
}

void print_if_empty(stack * st) {
  int empty = is_empty(st);
  if (empty)
    puts("\n\tStack is empty\n");
  else
    puts("\n\tStack is not empty now\n");
}

void print_arr(int * arr) {
  int i;
  for (i = 0; i < INIT_SIZE; ++i) {
    if (i > 0 && arr[i] == 0)
      break;
    printf("%i ", arr[i]);
    arr[i] = 0; // reset
  }
  puts("");
}