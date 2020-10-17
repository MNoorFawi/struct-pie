#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// A simple function to convert char * into int to get an index for it
int str_to_int(char * str) {
  int i = 0, output = 0;
  for (; str[i] != '\0'; ++i)
    output = output * 10 + str[i] - '0';
  return abs(output);
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
  table -> slot_array = (ls ** ) malloc(table -> size * sizeof(ls * )); // pointer to a struct pointer
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
  ls * temp = malloc(sizeof(ls)); // construct a slot
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
  temp -> next = table -> slot_array[index]; // the slot will point to the current index slot
  table -> slot_array[index] = temp;
  /* the index now contains the new value struct
  which is pointing to its neighbor in the index chain */
}

int val_search(ht * table, Tuple value) {
  ls * slot;
  int index;
  switch (value.type) {
	  case INT:
		index = hash_func(value.val._int, table -> size); // find index of that value
		slot = table -> slot_array[index]; // the chain containing the value
		while (slot && slot -> value._int != value.val._int) // search all the slots until found
		  slot = slot -> next;
		break;
	  case FLOAT:
		index = hash_func(value.val._float, table -> size);
		slot = table -> slot_array[index];
		while (slot && slot -> value._float != value.val._float)
		  slot = slot -> next;
		break;
	  case STR:
		index = hash_func(value.val._str, table -> size);
		slot = table -> slot_array[index];
		while (slot && strcmp(slot -> value._str, value.val._str) != 0)
		  slot = slot -> next;
		break;
  }
  return !(slot == NULL); // 1 (true) if found 0 (false) if not
}

/* search by index to find (FIRST) value in the index chain
returning a char * to make it easy to return any type (for now) */
char * search_by_index(ht * table, int ind) {
  ls * slot;
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
int delete_val(ht * table, Tuple value) {
  ls * current_slot, * next_slot;
  int index;
  switch (table -> type) {
	  case INT:
		index = hash_func(value.val._int, table -> size); // get index of given value
		current_slot = table -> slot_array[index]; // index's slot

		if (current_slot && current_slot -> value._int == value.val._int) { // if found in current slot
		  if (!current_slot -> next) // filled index will become empty
			table -> filled--;
		  table -> slot_array[index] = current_slot -> next; // replace current slot in the index with its next
		  free(current_slot); // delete current slot
		  return 1; // deleted (true)
		}
		while (current_slot) { // search the chain
		  next_slot = current_slot -> next; // go right to the next slot
		  if (next_slot && next_slot -> value._int == value.val._int) { // next slot is not NULL and value found
			current_slot -> next = next_slot -> next; // point to its next
			free(next_slot); // delete
			return 1; // (true)
		  } else {
			current_slot = next_slot; // go to the next one (not found yet)
		  }
		}
		return 0; // not found (false) to be deleted

	  case FLOAT:
		index = hash_func(value.val._float, table -> size);
		current_slot = table -> slot_array[index];

		if (current_slot && current_slot -> value._float == value.val._float) {
		  if (!current_slot -> next)
			table -> filled--;
		  table -> slot_array[index] = current_slot -> next;
		  free(current_slot);
		  return 1;
		}
		while (current_slot) {
		  next_slot = current_slot -> next;
		  if (next_slot && next_slot -> value._float == value.val._float) {
			current_slot -> next = next_slot -> next;
			free(next_slot);
			return 1;
		  } else {
			current_slot = next_slot;
		  }
		}
		return 0;

	  case STR:
		index = hash_func(value.val._str, table -> size);
		current_slot = table -> slot_array[index];

		if (current_slot && strcmp(current_slot -> value._str, value.val._str) == 0) {
		  if (!current_slot -> next)
			table -> filled--;
		  table -> slot_array[index] = current_slot -> next;
		  free(current_slot);
		  return 1;
		}
		while (current_slot) {
		  next_slot = current_slot -> next;
		  if (next_slot && strcmp(next_slot -> value._str, value.val._str) == 0) {
			current_slot -> next = next_slot -> next;
			free(next_slot);
			return 1;
		  } else {
			current_slot = next_slot;
		  }
		}
		return 0;
  }
}

void print_hash(ht * table, int size) {
  int i;
  for (i = 0; i < table -> size; ++i) {
    printf("\nindex(%d): ", i);
    ls * val = table -> slot_array[i];
    switch (table -> type) {
		case INT:
		  while (val) {
			printf(" %d ", val -> value._int);
			val = val -> next;
		  }
		  break;
		case FLOAT:
		  while (val) {
			printf(" %.2f ", val -> value._float);
			val = val -> next;
		  }
		  break;
		case STR:
		  while (val) {
			printf(" %s ", val -> value._str);
			val = val -> next;
		  }
		  break;
    }
  }
  puts("");
}

int filled_indices(ht * table) {
  return table -> filled;
}

int len(ht * table) {
  return table -> size;
}