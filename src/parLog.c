#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parLog.h"


parLog* createLogNode(char* filename, int cw1, int iw1, parLog* first)
{
	parLog *n = malloc(sizeof(parLog));
	n -> name = strdup(filename);
	n -> cw = cw1;
	n -> iw = iw1;
	n -> next = NULL;
	
	if (first != NULL)
	{
		parLog* app = first;
		while (app -> next != NULL)
			app = app -> next;
		
		app -> next = n;
	}
	
	return n;
}
