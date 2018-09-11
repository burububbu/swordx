#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "list.h"

void openFile(const char*);

int main(void)
{
	FILE *fd;
	char buf[200];
	char *res;
	list* swordx = listCreate();

	/* apre il file */
	fd=fopen("/home/michele/swordx/test", "r");
	if( fd==NULL ) {
    perror("Errore in apertura del file");
    exit(1);
    }


	/* legge e stampa ogni riga */
	while(1) 
	{
		res = fgets(buf, 2000, fd);
		if( res==NULL )
		  break;
	  
		storeString(swordx,buf);
	}

	 
	 if (fd == NULL){
		exit(-1);
	 }
	 
	 /* write on the file all word and occurrence*/
	 node *po = last-> first;
	  
	 while (po!= NULL) {
		fputs((po -> word), fd);
		int number = (po -> occurrence);
		fprintf(fd, " %d \n", number);
		po = (po -> next);
	  };
	  
	  fflush(fd);
	  fclose(fd);
	}
	
	//write this on the shell
	
	system("/bin/sh -c sort  <./swordnordered.out > sword.out");
	
	if (remove("swordnordered.out") != 0) printf("Unable to delete the file");
}