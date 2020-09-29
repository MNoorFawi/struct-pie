#define STRLEN 20

struct linked_queue {
  char *data;
  int priority;
  struct linked_queue * next;
};

typedef struct linked_queue pq;

void enqueue(pq ** front, pq ** rear, char *data, int priority);
char *execute(pq ** front, pq ** rear);
void display(pq * front, pq * rear);