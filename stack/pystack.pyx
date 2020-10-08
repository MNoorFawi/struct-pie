from libc.stdlib cimport malloc
DEF INIT_SIZE = 10000000

cdef extern from "stack.h":
    ctypedef enum Type:
        INT,
        FLOAT,
        STR

    cdef union arrays:
        int * _int
        float * _float
        char _str[INIT_SIZE][100]

    cdef struct st:
        Type type
        arrays val
        int indx
        int lindx
        int size

    ctypedef st stack

    void create_stack(stack * st, int input_type)
    int is_empty(stack * st)

    # pushing functions for each type argument
    void push_int(stack * st, int new_val)
    void push_float(stack * st, float new_val)
    void push_str(stack * st, char * new_val)

    # poping functions for each type argument
    int pop_int(stack * st, int input)
    int popleft_int(stack * st, int input)
    float pop_float(stack * st, float input)
    float popleft_float(stack * st, float input)
    char * pop_str(stack * st, char * input)
    char * popleft_str(stack * st, char * input)

    void print_stack(stack * st)
    int len(stack * st)

cdef class Stack:
    cdef stack *st
    cdef int input

    def __cinit__(self, str inp):
        enums = {"int": 0, "float": 1, "str": 2}
        self.input = enums.get(inp)
        if not input:
            print("Invalid Input\nStack will be of INT type by default!")
            self.input = 0

        self.st = <stack*>malloc(sizeof(stack))

        create_stack(self.st, self.input)

    def empty(self):
        if is_empty(self.st) == 1:
            return True
        else:
            return False

    def push(self, new_val):
        if isinstance(new_val, int):
            push_int(self.st, new_val)
        elif isinstance(new_val, float):
            push_float(self.st, new_val)
        else:
            push_str(self.st, new_val.encode())

    def pop(self):
        if self.input == 0:
            return pop_int(self.st, 0)
        elif self.input == 1:
            return round(pop_float(self.st, 1.0), 2)
        else:
            return pop_str(self.st, "2")

    def popleft(self):
        if self.input == 0:
            return popleft_int(self.st, 0)
        elif self.input == 1:
            return round(popleft_float(self.st, 1.0), 2)
        else:
            return popleft_str(self.st, "2")

    cpdef void display(self):
        print_stack(self.st)

    cpdef int length(self):
        return len(self.st)
