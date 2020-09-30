#define INIT_SIZE 10000000

// initialize a stack
struct stck{
    int *val;
    int indx;
	int lindx;
    int size;
};

typedef struct stck stack;
void create_stack(stack *st);
int is_empty(stack *st);
void push(stack *st, int new_val);
int pop(stack *st);
int popleft(stack * st);
void print_stack(stack *st);
int len(stack *st);
void clean(stack *st);