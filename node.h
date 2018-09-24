typedef struct node{
	char* word;
	int occurrence;
	struct node* next;
}node;

node *createNode();
node* addWord(node*, char*);
void updateOccurrence(node*);
<<<<<<< HEAD
node* storeString(node*, char*, int);
int countWord(char*);
=======

node* storeString(node*, char*, int, int);
int countWord(char*);
>>>>>>> celozzi
