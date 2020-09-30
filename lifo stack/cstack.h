#define INIT_SIZE 100

// initialize a stack (LIFO)
struct stck{
    int *val;
    int indx;
    int size;
};

typedef struct stck stack;
void create_stack(stack *st);
int is_empty(stack *st);
void push(stack *st, int new_val);
void pop(stack *st);
void print_stack(stack *st);
int len(stack *st);