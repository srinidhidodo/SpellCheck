#ifndef NODE_H
#define NODE_H
#define MAXLENGTH 38
typedef struct node
{
	char alpha;
	int isLeaf;//0 => no, 1 => yes
	struct node *link[28]; //0-25 alphabets, 26 ',27 -
}node;

int get_Index(char s);
node * initialise_Node(char s);
char * to_upper(char * str);
void insert(node * root, char * str);
int search(node *root, char *str);
void deleteTree(node* n);
node * create_Tree();
void spell_Check(char * s, node * root);
void fixRecursive(char *tw,int ldc[MAXLENGTH][MAXLENGTH],int rowno,char *strsofar,node *root);
int is_alpha(char * s);
void fix(char *tw,node *root);
void insert_file(char * s);
#endif
