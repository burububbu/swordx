#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int size = 0;

list* createList(){
	list * l = malloc(sizeof(list));
	
	l -> first = NULL;
	l -> last = NULL;
	
	printf("lista creata! \n");
	
	return l;
}


void addWord(list* lst, char* str){
	node* app = find(lst, str);
	if(app == NULL){
		node *n = createNode(str);
		//if size = 0,non ha elementi ed il first è uguale al last
		if (size == 0){
			lst -> first  = n;
			lst -> last = n;
			}
		else {
			//lst -> last -> next = n;
			lst -> last = n;	
		}
	}
	else{
		updateOccurrence(app);
	}
	size++;
printf("\nFirst: %s\n",lst -> first -> word);
printf("Last: %s\n",lst -> last -> word);
	
	
	
	
	
	
	
	
	
	
	
	//node *n = createNode(str);
	//printf("\n la size è %i \n", size);
	//if (size == 0){
		//lst -> first = n;
		//lst -> last = n;
		//printf("\n First: %s\n",lst -> first -> word);
		//printf("Last: %s\n",lst -> last -> word); 
		//}
	//else if (size == 1){
		//printf("\n First: %s\n",lst -> first -> word);
		//printf("Last: %s\n",lst -> last -> word);
		//}
	//size++;
	
	
	
	
	
	//if (size == 0){
		//l -> first = n;
		//l -> last = l ->first;
		//}
	//else if (size > 0){
		//node *app = find(l, str);
		//if (app == NULL){
			//printf("\n First: %s\n",l -> first -> word);
			//l -> last -> next = n;
			//l -> last = n;
			//}
		//else {
			//updateOccurrence(app);
		//}
	//} */
	//size++;
	//printf("\n First: %s\n",l -> first -> word);
	//printf("Last: %s\n",l -> last -> word); 
	}
	
node* find(list* l, char* str){
	if (size == 0) return NULL;
	node* n = l -> first;
    while (n -> next != NULL){
        if (strlen(str) == strlen(n -> word)){
            int cmp = strcmp(str, n -> word);
            
            if (cmp == 0){
                return n;
            }
        }
        n = n -> next;
    }
    return NULL;
}

void updateOccurrence(node* n){
	n -> occurrence +=1;
	}



