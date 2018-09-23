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

node* addWord(node* first, char *str)
{	
	node* app = first;
	if (app == NULL){
		return createNode(str);
		}
	else {
		while (app -> next != NULL){
			int cmp = strcmp(str, app -> word);
			if (cmp == 0) {
				updateOccurrence(app);
				return NULL;
				}
			else {
				app = app -> next;
				}  
			}
		if (strcmp(str, app -> word) == 0) {updateOccurrence(app); return NULL;}
		else {	
		app -> next =createNode(str);
		}
		return app;
		}
}

void updateOccurrence(node* n)
{
	n -> occurrence += 1;
}

node* storeString(node* first, char s[], int af, int n)
{
	char* str= calloc(countWord(s),20);
	int i = 0;
	
	while(s[i] != '\0')
	{
		if(af == 0)
		{
			if(isalpha(s[i]) || isdigit(s[i]))
			{
				str[i] = s[i];
				str[i] = tolower(s[i]);
			}
			else
			{
				str = NULL;
				break;
			}
		}
		else
		{
			if(isalpha(s[i]))
			{
				str[i] = s[i];
				str[i] = tolower(s[i]);
			}
			else
			{
				str = NULL;
				break;
			}
		}
			
		i++;
	}
	
	if(str != NULL)
	{	
		if(n == 0)
		{
			printf("*%s*\n",str);
			return addWord(first,str);
		}
		else
		{
			if(strlen(str) == n)
			{
				printf("*%s*\n",str);
				return addWord(first,str);
			}
		}
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

