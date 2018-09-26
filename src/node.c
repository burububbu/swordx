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
		return createNode(str);
	
	while(n -> next != NULL)
	{
		if (strcmp(str, n -> word) == 0)
			return updateOccurrence(n);
		
		n = n -> next;
	}
	/*contorlla ultimo nodo*/
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
 * s[] : stringa letta
 * af : alpha flag
 * num : num min
 * wordsToIgnore : pointer to an array of pointers to words to ignore
 * */
node* storeString(node* first, char s[], int af, int num, char ** wordsToIgnore)
{
	if (wordsToIgnore != NULL) 
		printf("\nIgnoro delle parole in un file\n");
	
	char* str= calloc(strlen(s),sizeof(char)); 
	
	int i = 0;
	
	while(s[i] != '\0')
	{		
		/*if(af == 0)
		{
			if(isalpha(s[i]) || isdigit(s[i]))
				str[i] = tolower(s[i]);
			else if(strlen(str) == 0)
			{
				str = NULL;
				break;
			}
		}
		else
		{
			if(isalpha(s[i]))
				str[i] = tolower(s[i]);
			else if(isdigit(s[i]))
				return NULL;
			else if(strlen(str) == 0)
			{
				str = NULL;
				break;
			}
		}*/
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
		if(num == 0)
		{
			printf("*%s*\n",str);
			return handleIgnored(str, wordsToIgnore);
		}
		else
		{
			if(strlen(str) >= num)
			{
				printf("*%s*\n",str);
				return handleIgnored(str, wordsToIgnore);
			}
		}
	}
	
	return NULL;
}

node* handleIgnored(node* f, char* s, char** wTI)
{
	if ((wTI != NULL) && isIgnored(s, wTI))
		return NULL;
	else
		return addWord(f,s);
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
	
void printIgnore(char** wordsToIgnore)
{
	int i = 0;
	
	while (wordsToIgnore[i] != NULL)
	{
		 printf("\n%s \n", wordsToIgnore[i]);
		 i++;
	}
	
}