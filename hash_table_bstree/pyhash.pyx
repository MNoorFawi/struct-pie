from libc.stdlib cimport malloc, free
DEF STRLEN = 100

cdef extern from "bstree.h":
	ctypedef enum Type:
		INT,
		FLOAT,
		STR

	cdef union Values:
		int _int
		float _float
		char _str[STRLEN]

	cdef struct tree_node:
		Values value
		void * left
		void * right

	ctypedef tree_node tn
	
	ctypedef struct Tuple:
		Type type
		Values val
		
	int compare(tn * x, tn * y, Type type)
	int compare2(tn * x, Tuple y, Type type, char op)
	void insert_node(tn ** root, tn * _new, Type type)
	void inorder(tn * root, Type type)
	tn * searchtree(tn * root, Tuple value, Type type)
	tn * get_ptr(tn * root, Tuple key, tn ** root_ptr, Type type)
	void deletenode(tn ** root, Tuple key, Type type, int * filled)

cdef extern from "hash.h":
	cdef struct hash_table:
		Type type
		int size
		tn ** slot_array
		int filled

	ctypedef hash_table ht

	ht * hash_init(int size, int type)
	Tuple int_in(int value)
	Tuple float_in(float value)
	Tuple str_in(char * value)
	int val_search(ht * table, Tuple value)
	char *search_by_index(ht * table, int ind)
	void insert(ht * htable, Tuple value)
	void delete_val(ht * table, Tuple value)
	## specifying here the type of the hash table in contrary to in the macro
	void print_hash(...)
	int filled_indices(ht * table)
	int len(ht * table)
	int get_indx(ht * table, Tuple value)

cdef Tuple val_to_tup(val):
	cdef Tuple t
	if isinstance(val, int):
		t = int_in(val)
	elif isinstance(val, float):
		t = float_in(val)
	else:
		t = str_in(val)
	return t

cdef class HashTable:
	cdef ht * hash
	cdef int size
	cdef int filled
	cdef int input

	def __cinit__(self, int table_size, str inp):
		enums = {"int": 0, "float": 1, "str": 2}
		self.input = enums.get(inp)
		if not input:
			print("Invalid Input\nHashTable will be of INT type by default!")
			self.input = 0

		self.size = table_size
		self.hash = hash_init(table_size, self.input)

	def search_value(self, val):
		cdef Tuple t = val_to_tup(val)
		return val_search(self.hash, t)

	def insert_val(self, val):
		cdef Tuple t = val_to_tup(val)
		insert(self.hash, t)

	def val_del(self, val):
		cdef Tuple t = val_to_tup(val)
		delete_val(self.hash, t)

	def display(self, displayed = 0):
		if displayed == 0:
			print_hash(self.hash)
		else:
			print_hash(self.hash, <int>displayed)

	cpdef str search_by_index(self, int ind):
		cdef bytes s = search_by_index(self.hash, ind)
		return s.decode()

	cpdef int length(self):
		return len(self.hash)

	cpdef int occupied(self):
		return filled_indices(self.hash)

	def get_index(self, val):
		cdef Tuple t = val_to_tup(val)
		return get_indx(self.hash, t)