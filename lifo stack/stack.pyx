from libc.stdlib cimport malloc

cdef extern from "cstack.h":
    cdef struct st:
        int *val
        int indx
        int size

    ctypedef st stack

    void create_stack(stack *st)
    int is_empty(stack *st)
    void push(stack *st, int new_val)
    void pop(stack *st)
    void print_stack(stack *st)
    int len(stack *st)

cdef class Stack:
    cdef stack *st

    def __cinit__(self):
        self.st = <stack*>malloc(sizeof(stack))
        create_stack(self.st)

    cpdef int empty(self):
        return is_empty(self.st)

    cpdef void push(self, int new_val):
        push(self.st, new_val)

    cpdef void pop(self):
        pop(self.st)

    cpdef void display(self):
        print_stack(self.st)

    cpdef int length(self):
        return len(self.st)
