#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "node.h"

#define MAXLENGTH 38

int main()
{
	printf("main\n");
	node * root = create_Tree();
	char fname[30];
	char * word = (char *)malloc(sizeof(char)*MAXLENGTH);
	int i;
	char k[3];
	do
	{
		printf("\n1. Check a file for spelling errors.\n2. Word lookup.\n3. Add a word to dictionary.\n4. Exit.\nEnter your choice: ");
		scanf("%d",&i);
		if (i==1)
		{
			printf("Enter the name of the file you wish to run spell check on : ");
			scanf("%s", fname);
			spell_Check(fname, root);
		}
		else if (i==2)
		{
			printf("Enter the word you wish to look up : ");
			scanf("%s",word);
			if (search(root,word))
			{
				printf("The word is correctly spelled.\n");
			}
			else
			{
				printf("The word is misspelt.\n");
				printf("Word correction suggestions:\n");
				fix(word, root);
				printf("Would you like to add your word to the dictionary? Type y/n: ");
				scanf("%s", k);
				if (k[0] == 'y')
				{
					insert(root,word);
					printf("Word added\n");
				}
					
			}
		}
		
		else if (i==3)
		{
			printf("Enter the word to be added\n");
			char str[100];
			scanf("%s",str);
			if(search(root,str) == 0)
			{
				insert(root,str);
				insert_file(str);
				printf("Word added\n");
			}
			else
				printf("Already exists in dictionary\n");
		}
		
		if (i > 4 || i < 1)
			printf("Invalid choice. Enter again.\n");
	}while (i != 4);
	deleteTree(root);
	return 0;
}
