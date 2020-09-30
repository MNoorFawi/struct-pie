cdef extern from "pq.h":
    cdef struct linked_queue:
        char *data
        int priority
        void *next # to link to next struct

    ctypedef linked_queue pq

    void enqueue(pq **front, pq **rear, char *data, int priority)
    char *execute(pq **front, pq **rear)
    void display(pq *front, pq *rear)

cdef class PQ:
    cdef pq *front
    cdef pq *rear

    def __cinit__(self):
        self.front = NULL
        self.rear = NULL


    cpdef void push(self, char *data, int priority):
        enqueue(&self.front, &self.rear, data, priority)

    cpdef str pop(self):
        cdef char *x
        x = execute(&self.front, &self.rear)
        return x.decode()

    cpdef void display(self):
        display(self.front, self.rear)
