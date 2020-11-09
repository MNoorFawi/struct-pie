#define STACK_SIZE 100000

typedef struct {
	int indx;
	char *cdata;
	float fdata;
} data;

struct tree_node {
  data * dat;
  struct tree_node * left, * right;
};

typedef struct tree_node tn;

data * populate_dat(int indx, char * cdata, float fdata);
void free_node(tn * node);
void error(void);
void insert(tn ** root, int indx, char * name, float ratio);
void inorder(tn * root);
int count(tn * root);
data * search(tn * root, int key);
tn * get_ptr(tn * root, int key, tn ** root_ptr);
tn * delete(tn * root, int key);