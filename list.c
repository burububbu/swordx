#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>//contiene isalpha() e isdigit() che permettono di controllare se una stringa contiene caratteri alfanumerici
#include "list.h"

//function implementation
int size(list* l)
{
	node* n = l -> first;
    int size = 1;
    while (n -> next != NULL) 
    {
    	size++;
        n = n -> next;
    }
    return size;
}

list* createList()
{
	list* l = malloc(sizeof(list));
	
	node* n = createNode();
	l -> first = n;
	
	if(size(l) == 1)
		l -> last = n;

	return l;
}

node* find(list* list, char* str)
{
	node* n = list -> first;
    while (n -> next != NULL) 
    {
        int cmp = strcmp(str, n -> word);
            
		if (cmp == 0) 
		{
			return n;
		}
        
        n = n -> next;
    }
    return NULL;
}

void addWord(list* list, char *str)
{
	node *n = list -> first;
	node* app = find(list, str);
	
    if(app == NULL)
    {
    	while (n -> next != NULL) 
    	{
    		n  = n -> next;
        }
		n -> word = str;
		n -> occurrence += 1;
		n -> next = createNode();
		list -> last = n;
	}
	else
	{
		updateOccurrence(app);
		list -> last = app;
	}

	printf("First: %s\n",list -> first -> word);
	printf("Last: %s\n",list -> last -> word);
}

void updateOccurrence(node* n)
{
	n -> occurrence += 1;
}

void storeString(list* l, char s[])
{
	char* str= calloc(countWord(s),20);
	int i = 0;
	
	while(s[i] != '\0')
	{
		if(isalpha(s[i]) || isdigit(s[i]))
			str[i] = s[i];
		else
		{
			str = NULL;
			break;
		}
			
		i++;
	}
	
	if(str != NULL)
	{
		printf("*%s*\n",str);
		addWord(l,str);
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