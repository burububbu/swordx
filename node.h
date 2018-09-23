typedef struct node{
	char* word;
	int occurrence;
	struct node* next;
}node;

node *createNode();
node* addWord(node*, char*);
void updateOccurrence(node*);
node* storeString(node*, char*, int);
int countWord(char*);