#include "node.h"

//declaration of the function and creation of the struct Node type
typedef struct list{
	struct node* first;
	struct node* last;
}list;

int size(list*);
list* listCreate();
node* find(list*, char*);
void addElement(list*, char*);
void updateOccurrence(node*);
void storeString(list*, char []);
int countWord(char []);