#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DATASET_SIZE 109582
#define SIZE 28
#define MAXLENGTH 38
#define LEVENSHTEIN_UB 1

typedef struct Node
{
	char a[30];
	struct Node * next;
}lnode;

lnode *front;

lnode * linsert(lnode * f, char * s)
{
	lnode * t =(lnode *) malloc(sizeof(lnode));
	strcpy((t -> a),s);
	t -> next = f;
	return t;
}

void display(lnode * f)
{
	lnode * t = f;
	while(t != NULL)
	{
		printf("%s\n", t->a);
		t = t -> next;
	}
}


int get_Index(char s)
{
	if(s == '\'')
	{
		return 26;
	}
	if (s=='-')
	{
		return 27;
	}
	return ((int)s - 65);
}

node * initialise_Node(char s)
{
	node * n = (node * )malloc(sizeof(node));
	if(n)
	{
		n->isLeaf = 0;
		n->alpha = s;
		int i;
		for(i = 0; i < SIZE; ++i)
		{
			n-> link[i] = NULL;
		}
	}
	return n;
}

char * to_upper(char * str)
{
	int l = strlen(str);
	char * s = (char *)malloc(sizeof(char)*(l+2));
	int i;
	for(i = 0; i < l; ++i)
	{
		s[i] = toupper(str[i]);
	}
	s[l]='\0';
	return s;
}

void insert(node * root, char * str)
{
	char * s = to_upper(str);
	int len = strlen(s);
	int index;
	int i;
	node * t = root;
	for (i = 0; i < len; i++)
	{
		index = get_Index(s[i]);
		if (!t -> link[index])
		{
			t -> link[index] = initialise_Node(s[i]);
		}
		if(i != len)	
			t = t -> link[index];
	}
	t -> isLeaf = 1;
}

int search(node * root, char * str)
{
	char * s = to_upper(str);
	int len = strlen(s);
	int index;
	int i;
	node * t = root;
	for (i = 0; i < len; ++i)
	{
		index = get_Index(s[i]);
		if (! t -> link[index])
		{
			return 0;
		}
		t = t -> link[index];
	}
	free(s);
	return (t != NULL && t -> isLeaf==1);
}


int min(int a,int b,int c)
{
	int ret=a;
	if (ret>b)
		ret=b;
	if (ret>c)
		ret=c;
	return ret;
}

void fixRecursive(char *tw,int ldc[MAXLENGTH][MAXLENGTH],int rowno,char *strsofar,node *root)
{
	int x=strlen(strsofar);
	strsofar[x]=root->alpha;
	strsofar[x+1]='\0';
	int i;
	int insCost,delCost,repCost; // insert, delete, replace costs
	for (i=1;i<=strlen(tw);i++)
	{
		insCost=ldc[rowno][i-1]+1;
		delCost=ldc[rowno-1][i]+1;
		repCost=ldc[rowno-1][i-1];
		if (tw[i-1]!=root->alpha)
			repCost+=1;
		ldc[rowno][i]=min(insCost,delCost,repCost);
	}
	if (root->isLeaf==1)
	{
		if (ldc[rowno][strlen(tw)]<=LEVENSHTEIN_UB)
		{
			lnode *fr=(lnode *)malloc(sizeof(lnode));
			fr->next=NULL;
			fr = linsert(front, strsofar);
			display(fr);
			 
		 }
	}
	for (i=0;i<28;i++)
	{
		if (root->link[i])
			fixRecursive(tw,ldc,rowno+1,strsofar,root->link[i]);
	}
	strsofar[x]='\0';
}

void fix(char *tw,node *root)
{
	tw=to_upper(tw);
	front=NULL;
	int ldc[MAXLENGTH][MAXLENGTH];
	long i;
	for (i=0;i<MAXLENGTH;i++)
	{
		ldc[0][i]=i;
		ldc[i][0]=i;
	}
	for (i=1;i<MAXLENGTH;i++)
	{
		int j;
		for (j=1;j<MAXLENGTH;j++)
			ldc[i][j]=0;
	}	
	char *strsofar=(char *)malloc(sizeof(char)*MAXLENGTH);
	strsofar[0]='\0';
	if (strlen(tw) > MAXLENGTH)
	{
		printf("Not possible\n");
	}
	else
	{
		int i;
		for (i=0;i<28;i++)
		{
			if (root->link[i])
				fixRecursive(tw,ldc,1,strsofar,root->link[i]);
		}
	}
}

void deleteTree(node* n)
{
    if (n == NULL) return;
 
    /* first delete both subtrees */
    int i;
    for (i = 0; i < 28; ++i)
    {
    	deleteTree(n->link[i]);
    }
    free(n);
} 

node * create_Tree()
{
	node * root = initialise_Node('\0');
	int i;
	FILE * f = NULL;
	f = fopen("english_wordlist1.txt", "r");
	if(!f)
	{
		printf("File open error\nPlease check for english_wordlist.txt\nExiting");
		exit(0);
	}
	char temp[100];
	char ch = getc(f);
	while(ch != EOF)
	{
		i = 0;
		while(ch != '\n')
		{
			temp[i] = ch;
			++i;
			ch = getc(f);
		}
		temp[i-1] = '\0';
		insert(root, temp);
		ch = getc(f);
	}
	fclose(f);
	return root;
}

int is_alpha(char * s)
{
	int i;
	for(i = 0; i < strlen(s); ++i)
	{
		if(!isalpha(s[i]))
		{
			return 0;
		}
	}
	return 1;
}

void spell_Check(char * s, node * root)
{
	FILE * f = NULL;
	f = fopen(s, "r");
	if(!f)
	{
		printf("File open error\nExiting\n");
		exit(0);
	}
	int i = 0;
	char * temp = (char *)malloc(sizeof(char) * MAXLENGTH);
	char ch = getc(f);
	int l = 1;
	int w = 0;
	while(ch != EOF)
	{
		i = 0;
		while(ch != ' ' && ch != '.' && ch != ',' && ch != '\n' && ch != '?' && ch != '!' && ch != ';' && ch != ':' && ch != '(' && ch != ')')
		{
			temp[i] = ch;
			++i;
			ch = getc(f);	
		}
		temp[i] = '\0';
		++w;
		if((i > 1 || (i == 1 && temp[0] == 'a')) && is_alpha(temp))
		{
			if(!search(root, temp))
			{
				printf("\nMisspelt: %s\t\t Line: %d\t Word: %d\n", temp, l, w);
				printf("Word correction suggestions:\n");
				fix(temp, root);
				printf("\nPress any key to see next incorrectly spelled word\n");
				char t;
				scanf("%c", &t);
			}
		}
		if(ch == '\n')
		{
			++l;
			w = 0;
		}

		ch = getc(f);
	}
	
	fclose(f);	
}

void insert_file(char * s)
{
	FILE * f = fopen("english_wordlist1.txt", "a");
	int i;
	if(!f)
	{
		printf("File open error\nPlease check for english_wordlist.txt\nExiting");
		exit(0);
	}
	for(i = 0; i < strlen(s); ++i)
	{
		putc(s[i], f);
	}
	putc('\0', f);
	putc('\n', f);
	fclose(f);
}
