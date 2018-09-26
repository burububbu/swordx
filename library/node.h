typedef struct node{
	char* word;
	int occurrence;
	struct node* next;
}node;

node *createNode();
node* addWord(node*, char*);
node* updateOccurrence(node*);
node* storeString(node*, char*, int, int, char**);
char* alphaControl(int , int);
node* handleIgnored(node*, char*, char**);
int isIgnored(char*, char**);
void printIgnore(char**);
