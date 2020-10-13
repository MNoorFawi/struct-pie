#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

unsigned int hash_func(int key, int table_size) {
  return key % table_size; // key modulo size
}

ht * hash_init(int size) {
  ht * table = malloc(sizeof(ht)); // empty table
  table -> size = size;
  table -> slot_array = (ls ** ) malloc(table -> size * sizeof(ls * )); // pointer to a struct pointer
  /* slot_array will contain the chain of the slots of each index
each slot_array[i] will have linked lists pointing to each other */
  int i;
  for (i = 0; i < table -> size; ++i)
    table -> slot_array[i] = NULL; // empty chain
  return table;
}

int val_search(ht * table, int value) {
  ls * slot;
  int index = hash_func(value, table -> size); // find index of that value
  slot = table -> slot_array[index]; // the chain containing the value
  while (slot && slot -> value != value) // search all the slots until found
    slot = slot -> next;
  return !(slot == NULL); // 1 (true) if found 0 (false) if not
}

// search by index to find (FIRST) value in the index chain
int search_by_index(ht * table, int ind) {
  ls * slot;
  int index = hash_func(ind, table -> size);
  slot = table -> slot_array[index];
  if (slot) { // not NULL
    return slot -> value; // found
  } else
    return -1; // not found
}

// insert new value into the table
void insert(ht * table, int value) {
  int index = hash_func(value, table -> size); // create index for given value
  ls * temp = malloc(sizeof(ls)); // construct a slot
  temp -> value = value; // insert the value in the slot
  temp -> next = table -> slot_array[index]; // the slot will point to the current index slot
  table -> slot_array[index] = temp; // the given value is inserted into the slot and it is pointing to its chain
}

// delete value i.e. empty the index in the table
int delete_val(ht * table, int value) {
  ls * current_slot, * next_slot;
  int index = hash_func(value, table -> size); // get index of given value
  current_slot = table -> slot_array[index]; // index's slot

  if (current_slot && current_slot -> value == value) { // if found in current slot
    table -> slot_array[index] = current_slot -> next; // replace current slot in the index with its next
    free(current_slot); // delete current slot
    return 1; // deleted (true)
  }
  while (current_slot) { // search the chain
    next_slot = current_slot -> next; // go right to the next slot
    if (next_slot && next_slot -> value == value) { // next slot is not NULL and value found
      current_slot -> next = next_slot -> next; // point to its next
      free(next_slot); // delete
      return 1; // (true)
    } else {
      current_slot = next_slot; // go to the next one (not found yet)
    }
  }
  return 0; // not found (false) to be deleted
}

void print_hash(ht * table, int size) {
  int i;
  for (i = 0; i < table -> size; ++i) {
    printf("\nindex(%d): ", i);
    ls * val = table -> slot_array[i];
    while (val) {
      printf(" %d ", val -> value);
      val = val -> next;
    }
  }
  puts("");
}
