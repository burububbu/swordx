#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "node.h"

node* createNode(char* str)
{
	node* n = malloc(sizeof(node));
	
	n -> word = str;
	n -> occurrence = 1;
	n -> next = NULL;

	return n;
}

node* addWord(node* n, char *str)
{	
	if (n == NULL)
		return createNode(str);
	
	while(n -> next != NULL)
	{
		if (strcmp(str, n -> word) == 0)
			return updateOccurrence(n);
		
		n = n -> next;
	}
	/*coltrols last node*/
	if(strcmp(str, n -> word) == 0)
		return updateOccurrence(n);
	else
		return n -> next = createNode(str);
	
	return NULL;
}

node* updateOccurrence(node* n)
{
	n -> occurrence += 1;
	return n;
}
/*
 * first : first node
 * s[] : string
 * af : alpha flag
 * num : num min
 * wordsToIgnore : pointer to an array of pointers to words to ignore
 * */
node* storeString(node* first, char s[], int af, int num, char ** wordsToIgnore)
{
	char* str= calloc(strlen(s),sizeof(char)); 
	
	int i = 0;
	
	while(s[i] != '\0')
	{
		if(isalpha(s[i]))
			str[i] = tolower(s[i]);
		else if(isdigit(s[i]))
		{
			if(af == 0)
				str[i] = s[i];
			else
				return NULL;
		}
		else if(strlen(str) == 0)
		{
			str = NULL;
			break;
		}

		i++;
	}
	
	if(str != NULL)
	{
		if (strlen(str) >= num)
			{
				if((wordsToIgnore != NULL) && isIgnored(str, wordsToIgnore))
					return NULL;
				else
				{
					printf("*%s*\n",str);
					return addWord(first,str);
				}
			}
			else
				return NULL;
	}
	
	return NULL;
}

int isIgnored(char* str, char** wordsToIgnore)
{
	int i = 0;
	while (wordsToIgnore[i] != NULL)
	{
		if (strcmp(str,wordsToIgnore[i]) == 0) 
			return 1;
		
		i++;
	}
	 
	return 0;
}