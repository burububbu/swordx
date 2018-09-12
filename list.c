#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>//contiene isalpha() e isdigit() che permettono di controllare se una stringa contiene caratteri alfanumerici
#include "list.h"

list* createList()
{
	list* list = malloc(sizeof(list));
	list -> first = NULL;
	list -> last = NULL;
	
	return list;
}

void addWord(list* l, char* c)
{
	node* app = find(l,c);
	
	if(app == NULL)
	{
		node* n = createNode(c);
		
		if((l -> first) == NULL)
		{
			l -> first = n;
			l -> last = n;
		}
		else
		{
			l -> last = n;
		}
		
		printf("\nFirst: %s\n",l -> first -> word);
		printf("\nLast: %s\n",l -> last -> word);
	}
	else
	{
		updateOccurrence(app);
	}
}

node* find(list* l, char* str)
{
	node* n = l -> first;
	
	if(n == NULL)
		return NULL;
	
	while(n -> next != NULL)
	{
		int cmp = strcmp(str,n -> word);
		
		if(cmp == 0)
			return n;
		
		n = n -> next;
	}
	
	return NULL;
}

void updateOccurrence(node* n)
{
	n -> occurrence += 1;
}

void storeString(list* l, char buf[])
{
	int i = 0;
	int j = 0;
	
	while(i < countWord(buf))
	{
		int k = 0;
		char* str= calloc(countWord(buf),20);
		
		while(buf[j] != ' ')
		{
			if(isalpha(buf[j]) || isdigit(str[j]))
					str[k] = buf[j];
				
			j++;
			k++;
		}
		
		j += 1;
		
		if(strlen(buf) >= 1 && buf[1] != '\0')
		{
			printf("*%s*\n",str);
			addWord(l,str);
		}
		i++;
	}
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