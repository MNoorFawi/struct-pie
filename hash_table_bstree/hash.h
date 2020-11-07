//#include "bstree.h"

// the hash table that will contain the linked lists of each index inside vals_array
struct hash_table {
  Type type;
  int size;
  tn ** slot_array; // double pointer to point to array
  int filled;
};

typedef struct hash_table ht;


int str_to_int(char * str);
unsigned int hash_func_int(int key, int table_size);
unsigned int hash_func_float(float key, int table_size);
unsigned int hash_func_str(char * key, int table_size);
ht * hash_init(int size, int type);
Tuple int_in(int value);
Tuple float_in(float value);
Tuple str_in(char * value);
int val_search(ht * table, Tuple value);
char * search_by_index(ht * table, int ind);
void insert(ht * table, Tuple value);
void delete_val(ht * table, Tuple value);
void printhash(ht * table, int size);
int filled_indices(ht * table);
int len(ht * table);
int get_indx(ht * table, Tuple value);

// combining the hash functions into one function like macro that accepts multiple types
#define hash_func(x, y)\
_Generic((x), \
  int: hash_func_int, float: hash_func_float, char *: hash_func_str, \
  default: hash_func_int)(x, y)

// make display function with default argument
#define print_hash(...) print_wrapper((func_args) {__VA_ARGS__})

typedef struct {
  ht * table;
  int displayed;
}
func_args;

void print_wrapper(func_args input);