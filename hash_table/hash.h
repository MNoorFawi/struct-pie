// each linked list slot
struct list_slot {
  int value;
  struct list_slot * next;
};

typedef struct list_slot ls;

// the hash table that will contain the linked lists of each index inside vals_array
struct hash_table {
  int size;
  ls ** slot_array; // double pointer to point to array
  int filled;
};

typedef struct hash_table ht;

unsigned int hash_func(int key, int table_size);
ht * hash_init(int size);
int val_search(ht * table, int value);
int search_by_index(ht * table, int ind);
void insert(ht * htable, int value);
int delete_val(ht * table, int value);
void print_hash(ht * table, int size);
int filled_indices(ht * table);
int len(ht * table);