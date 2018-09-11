#include "node.h"

typedef struct list{
	struct node* first;
	struct node* last;
}list;

list* createList();
void addWord(list*, char*);
node* find(list*, char*);
void updateOccurrence(node*);
