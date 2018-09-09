#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

//create node

node* createNode(char* word1){
	node* n = malloc (sizeof(node));
	
	n -> word = word1;
	n -> occurrence = 1;
	n -> next = NULL;
	
	if(strlen(word1) == strlen(n -> word));
	else
		printf("Failed \n");
	return n;
	} 
