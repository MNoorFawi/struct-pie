#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"
#include "hash.h"

// A simple function to convert char * into int to get an index for it
int str_to_int(char * str) {
  int i = 0, output = 0;
  for (; str[i] != '\0'; ++i)
    // ascii code of character
    output += str[i]; // str[i] - '0'; // gives numeric value of a number in an ascii code
  return output / i; // to decrease the value
}

// hash func family for int, float and char *
unsigned int hash_func_int(int key, int table_size) {
  return key % table_size; // key modulo size
}

unsigned int hash_func_float(float key, int table_size) {
  return (int) key % table_size;
}

unsigned int hash_func_str(char * key, int table_size) {
  return str_to_int(key) % table_size;
}

// user should specify type of hash table
ht * hash_init(int size, int type) {
  ht * table = malloc(sizeof(ht)); // empty table
  switch (type) {
  case 0:
    table -> type = INT;
    break;
  case 1:
    table -> type = FLOAT;
    break;
  case 2:
    table -> type = STR;
    break;
  default:
    puts("\tInvalid Input");
  }
  table -> size = size;
  table -> filled = 0;
  table -> slot_array = (tn ** ) malloc(table -> size * sizeof(tn * )); // pointer to a struct pointer
  /* slot_array will contain the chain of the slots of each index
each slot_array[i] will have linked lists pointing to each other */
  int i;
  for (i = 0; i < table -> size; ++i)
    table -> slot_array[i] = NULL; // empty chain
  return table;
}

/* functions to construct structs to pass into hash table
operation functions to enable multiple inputs for a function */
Tuple int_in(int value) {
  Tuple intt = {
    INT,
    .val._int = value
  };
  return intt;
}

Tuple float_in(float value) {
  Tuple floatt = {
    FLOAT,
    .val._float = value
  };
  return floatt;
}

Tuple str_in(char * value) {
  Tuple strt = {
    STR
  };
  strcpy(strt.val._str, value);
  return strt;
}

// insert new value into the table
void insert(ht * table, Tuple value) {
  tn * temp = malloc(sizeof(tn)); // construct a slot
  int index;
  switch (value.type) { // depends on type of input
  case INT:
    index = hash_func(value.val._int, table -> size); // create index for given value
    temp -> value._int = value.val._int; // insert the value in the slot
    break;
  case FLOAT:
    index = hash_func(value.val._float, table -> size);
    temp -> value._float = value.val._float;
    break;
  case STR:
    index = hash_func(value.val._str, table -> size);
    strcpy(temp -> value._str, value.val._str);
    break;
  }

  if (table -> slot_array[index] == NULL) // an empty index is filled
    table -> filled++;
  insert_node(&table->slot_array[index], temp, table -> type);
  /* the index now contains the new value struct
  which is pointing to its neighbor in the index chain */
}

int val_search(ht * table, Tuple value) {
  tn * slot;
  int index;
  switch (value.type) {
  case INT:
    index = hash_func(value.val._int, table -> size); // find index of that value
    break;
  case FLOAT:
    index = hash_func(value.val._float, table -> size);
    break;
  case STR:
    index = hash_func(value.val._str, table -> size);
    break;
  }
  slot = searchtree(table -> slot_array[index], value, table->type); // the chain containing the value
  return !(slot == NULL); // 1 (true) if found 0 (false) if not
}

/* search by index to find (FIRST) value in the index chain
returning a char * to make it easy to return any type (for now) */
char * search_by_index(ht * table, int ind) {
  tn * slot;
  static char res[STRLEN];
  int index = hash_func(ind, table -> size);
  slot = table -> slot_array[index];
  if (slot) { // not NULL
    switch (table -> type) {
    case INT:
      sprintf(res, "%d", slot -> value._int); // found
      return res;
    case FLOAT:
      sprintf(res, "%f", slot -> value._float);
      return res;
    case STR:
      sprintf(res, "%s", slot -> value._str);
      return res;
    }

  } else
    return "-1"; // not found
}

// delete value i.e. empty the index in the table
void delete_val(ht * table, Tuple value) {
  int index;
  switch (table -> type) {
  case INT:
    index = hash_func(value.val._int, table -> size); // get index of given value
	break;

  case FLOAT:
    index = hash_func(value.val._float, table -> size);
	break;

  case STR:
    index = hash_func(value.val._str, table -> size);
	break;
  }
  deletenode(&table -> slot_array[index], value, table -> type, &table->filled);
}

void printhash(ht * table, int size) {
  int i;
  for (i = 0; i < size; ++i) {
    printf("\nindex(%d): ", i);
    tn * val = table -> slot_array[i];
    pinorder(val, table->type);
  }
  puts("");
}

void print_wrapper(func_args input) {
  int displayed = input.displayed ? input.displayed : input.table -> size;
  printhash(input.table, displayed);
}

int filled_indices(ht * table) {
  return table -> filled;
}

int len(ht * table) {
  return table -> size;
}

int get_indx(ht * table, Tuple value) {
  int index;
  if (val_search(table, value)) {
    switch (table -> type) {
    case INT:
      index = hash_func(value.val._int, table -> size);
      return index;
    case FLOAT:
      index = hash_func(value.val._float, table -> size);
      return index;
    case STR:
      index = hash_func(value.val._str, table -> size);
      return index;
    }
  } else {
    return -1;
  }
}