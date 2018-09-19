#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

//create node

node* createNode()
{
	node* n = malloc(sizeof(node));
	
	n -> word = NULL;
	n -> occurrence = 0;
	n -> next = NULL;
	
	return n;
}
