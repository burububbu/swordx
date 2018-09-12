#include "list.h"

void checkName(list*, char*);
void updateList(list*, char*);
void writeOnFile(list*, char*);
int isDirectory(char*);
int isRegular(char*);
int isLink(char*);
int fileInDirUpdate(list*, char*, int); /*lista, file name, boolean is is a  sub or not*/
char* createPath (char*, char*);
