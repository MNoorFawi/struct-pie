from cython.operator import dereference
from libc.stdlib cimport malloc

cdef extern from "bstree.h":
	cdef struct tree_node:
		int indx
		char *name
		float ratio
		void *left # to link to next struct
		void *right

	ctypedef tree_node tn

	void error()
	void insert(tn ** root, int indx, char * name, float ratio)
	void inorder(tn * root)
	int count(tn * root)
	tn * search(tn * root, int key)
	tn * delete(tn * root, int key)

cdef class BSTree:
	cdef tn *root

	def __cinit__(self):
		self.root = NULL

	cpdef void insert(self, int indx, char * name, float ratio):
		insert(&self.root, indx, name, ratio)

	cpdef void inorder(self):
		inorder(self.root)

	cpdef void remove(self, int node):
		self.root = delete(self.root, node)

	def search(self, int node):
		cdef tn *temp_tree = search(self.root, node)
		if not temp_tree:
			return "node doesn't exist"
		else:
			temp = dereference(temp_tree)
			return (temp.indx, temp.name, round(temp.ratio, 3))

	cpdef int node_count(self):
		return count(self.root)
