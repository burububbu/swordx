#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "node.h"

//create node
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
	{
		return createNode(str);
	}
	
	node* a = find(n,str);
	
	if(a != NULL)
	{
		updateOccurrence(a);
		return a;
	}
	else
	{
		while(n -> next != NULL)
		{
			n = n -> next;
		}
		
		return n -> next = createNode(str);
	}
}

node* find(node* n, char* str)
{
	while (n != NULL)
	{
		int cmp = strcmp(str, n -> word);
		
		if (cmp == 0) 
		{
			return n;
		}
		
		n = n -> next;
	}
}

void updateOccurrence(node* n)
{
	n -> occurrence += 1;
}

node* storeString(node* first, char s[], int af, int num)
{
	char* str= calloc(countWord(s),20);
	int i = 0;
	
	while(s[i] != '\0')
	{
		if(af == 0)
		{
			if(isalpha(s[i]) || isdigit(s[i]))
			{
				str[i] = tolower(s[i]);
			}
			else if(strlen(str) == 0)
			{
				str = NULL;
				break;
			}
		}
		else
		{
			if(isalpha(s[i]))
			{
				str[i] = tolower(s[i]);
			}
			else if(strlen(str) == 0)
			{
				str = NULL;
				break;
			}
		}
			
		i++;
	}
	
	if(str != NULL)
	{
		if(num == 0)
		{
			printf("*%s*\n",str);
			return addWord(first,str);
		}
		else
		{
			if(strlen(str) >= num)
			{
				printf("*%s*\n",str);
				return addWord(first,str);
			}
		}
	}
	
	return NULL;
}

int countWord(char b[])
{
	int i = 0;
	int counter = 0;
	
	while(i <= strlen(b))
	{
		if(b[i] == ' ' || b[i] == '\0')
			counter++;
		i++;
	}
	
	return counter;
}
