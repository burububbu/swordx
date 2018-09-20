typedef struct node{
	char* word;
	int occurrence;
	struct node* next;
}node;

node *createNode();
