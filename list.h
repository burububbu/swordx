#include "node.h"

typedef struct list{
	struct node* first;
	struct node* last;
}list;

int size(list*);
list* createList();
node* find(list*, char*);
void addWord(list*, char*);
void updateOccurrence(node*);
void storeString(list*, char[]);
int countWord(char []);