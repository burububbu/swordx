#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

//create node

node* createNode(char* w)
{
	node* n = malloc (sizeof(node));
	
	n -> word = w;
	n -> occurrence = 1;
	n -> next = NULL;
	
	return n;
}