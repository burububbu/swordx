#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

List* createList()
{
	List* list = malloc(sizeof(List));
	list -> first = NULL;
	list -> last = NULL;
	
	return list;
}

void addWord(List* l, char* c)
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

node* find(List* l, char* str)
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