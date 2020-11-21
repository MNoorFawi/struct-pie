from libc.stdlib cimport malloc, free
DEF STRLEN = 100

cdef extern from "hash.h":
    ctypedef enum Type:
        INT,
        FLOAT,
        STR

    cdef union Values:
        int _int
        float _float
        char _str[100]

    cdef struct list_slot:
        Values value
        void * next

    ctypedef list_slot ls

    cdef struct hash_table:
        Type type
        int size
        ls ** slot_array
        int filled

    ctypedef hash_table ht

    ctypedef struct Tuple:
        Type type
        Values val

    ht * hash_init(int size, int type)
    Tuple int_in(int value)
    Tuple float_in(float value)
    Tuple str_in(char * value)
    int val_search(ht * table, Tuple value)
    char *search_by_index(ht * table, int ind)
    void insert(ht * htable, Tuple value)
    int delete_val(ht * table, Tuple value)
	## specifying here the type of the hash table in contrary to in the macro
    void print_hash(...)
    int filled_indices(ht * table)
    int len(ht * table)
    int search_indx(ht * table, char ** arr, int ind)
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
        return delete_val(self.hash, t)

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

    cpdef list search_index(self, int indx):
        cdef char **arr = <char **>malloc(STRLEN * sizeof(char *))
        cdef int l = search_indx(self.hash, arr, indx)
        cdef int c
        try:
            return [i.decode() for i in arr[:l]]
        finally:
            for c in range(l):
                free(arr[c])
            free(arr)

    def get_index(self, val):
        cdef Tuple t = val_to_tup(val)
        return get_indx(self.hash, t)
