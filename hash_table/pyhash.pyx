from libc.stdlib cimport malloc

cdef extern from "hash.h":
	cdef struct list_slot:
		int value
		void * next

	ctypedef list_slot ls

	cdef struct hash_table:
		int size
		ls ** slot_array

	ctypedef hash_table ht

	ht * hash_init(int size)
	int val_search(ht * table, int value)
	int search_by_index(ht * table, int ind)
	void insert(ht * htable, int value)
	int delete_val(ht * table, int value)
	void print_hash(ht * table, int size)

cdef class HashTable:
	cdef ht * hash
	cdef int size

	def __cinit__(self, int table_size):
		self.size = table_size
		self.hash = hash_init(table_size)

	cpdef int search_value(self, int val):
		return val_search(self.hash, val)

	cpdef void insert_val(self, int val):
		insert(self.hash, val)

	cpdef int val_del(self, int val):
		return delete_val(self.hash, val)

	def display(self):
		print_hash(self.hash, self.size)

	cpdef int search_by_index(self, int ind):
		return search_by_index(self.hash, ind)