#define STACK_SIZE 1000

struct tree_node {
  int indx;
  char * name;
  float ratio;
  struct tree_node * left, * right;
};

typedef struct tree_node tn;

void error(void);
void insert(tn ** root, int indx, char * name, float ratio);
void inorder(tn * root);
int count(tn * root);
tn * search(tn * root, int key);
tn * get_ptr(tn * root, int key, tn ** root_ptr);
tn * delete(tn * root, int key);